
#if BURN_EEPROM==0

//cycle between chapters:
//0. solid white
//1. rainbow cycle color
//2. cycle brightness
//3. hold solid color
//  next chapter is 1: rainbow cycle
void book_home()
{
  byte next_state;
  set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,strip.Color(0,0,0,255));
  strip.show();
  while(true)
  {
    while(!(next_state=get_next_chapter_state()));
    if(next_state==GO_TO_ROOT) return;
    while(!(next_state=get_next_chapter_state())){ delay(HUE_DELAY_MS); set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,home_hue=next_wheel_color(home_hue)); strip.show(); }
    if(next_state==GO_TO_ROOT) return;
    while(!(next_state=get_next_chapter_state()))
    {
      if(home_brightness==255) home_brightness=254;//evens go down
      else if(home_brightness==10) home_brightness=11;//odds go up
      else if(home_brightness&0x01) home_brightness+=2;//odds go up
      else home_brightness-=2;//evens go down
      strip.setBrightness(home_brightness);
      set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,home_hue);
      strip.show();
      delay(HUE_DELAY_MS);
    }
  }
}

word Vrail_leo() { 
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif 

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH 
  uint8_t high = ADCH; // unlocks both

  word result = (high<<8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000   
                         
  return result;
 
}

//only one chapter: count up one minute in binary
//every minute, increment color every minute from red (0) to purple (9), then return to red (0)
//pressing button restarts count-up timer
void book_time_and_battery()
{
  byte next_state=GO_TO_NEXT_CHAPTER;
  unsigned long chapter_start_ms;
  byte battery_blink_index=7;
  do{
    if(next_state==GO_TO_NEXT_CHAPTER) chapter_start_ms=millis();
    word seconds_all=(millis()-chapter_start_ms)/500;
    byte minutes=(seconds_all/120)%10;//behavior when timer goes beyond 10 minutes is undefined (length of EEPROM list)
    byte seconds=seconds_all%120;
    bool is_blink=seconds&0x01;
    uint32_t color=EEPROMReadLong(EEPROM_ADDRESS_BACKGROUND_TIMER+minutes*sizeof(uint32_t));
    if(is_blink)
    {//only measure voltage once when the led is not dimmed - avoids adjacent leds flickering if voltage is midway between them
      battery_blink_index=7;
      word battery_mv=Vrail_leo();
      //using discharge profile at 0.5C (200 mA on 400 mAh battery) for reference: https://learn.adafruit.com/li-ion-and-lipoly-batteries/voltages
      if(battery_mv>3600) battery_blink_index++; //3660, 3616 https://www.richtek.com/~/media/Richtek/Design%20Support/Technical%20Documentation/AN024/EN/Version1/image001.gif?file=preview.png
      if(battery_mv>3700) battery_blink_index++; //3750, 3646
      if(battery_mv>3820) battery_blink_index++; //3870, 3789
    }
    for(byte led=0;led<LED_COUNT;led++)
    {
      if(led<7)//60 seconds counting in half-seconds takes up 7 leds
      {
        strip.setPixelColor(6-led,seconds&0x01?color:0);//reverse order of leds to LSB is on LED 6
        seconds>>=1;
      }else{
        //red for led 7,yellow for 8&9, green for 10
        byte red=led<10?252:0;
        byte green=led>7?252:0;
        strip.setPixelColor(led,strip.Color(red,green,0)>>((!is_blink && led==battery_blink_index)?2:0));
      }
    }
    strip.show();
  }while((next_state=get_next_chapter_state())!=GO_TO_ROOT);
}

//7 chapters: one for each color/tone
//red, green, blue are chapters 0-2, pairs of colors/tones are chapters 3-5, all three colors (white)/tones is chapter 7
//pressing button again repeats chapters
void book_sound()
{
  begin_sound();
  byte chapter=6;
  byte eeprom_address_start=0;
  sound_state=GO_TO_NEXT_CHAPTER;
  while(sound_state!=GO_TO_ROOT)
  {
    if(sound_state==GO_TO_NEXT_CHAPTER)
    {
      sound_state=NO_STATE_CHANGE;
      if(chapter==6)
      {
        chapter=0;
        eeprom_address_start=0;
      }else{
        eeprom_address_start+=SHORT_SOUND_CHARACTER_COUNT;
        chapter++;
      }
      word background_color_address=EEPROM_ADDRESS_BACKGROUND_BOOK+sizeof(uint32_t)*((chapter*2+1)%7);
      uint32_t background_color=EEPROMReadLong(background_color_address);
      set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,background_color);
      pause_sound(true);
      strip.show();
      pause_sound(false);
    }
    restart_sound(eeprom_address_start,chapter<3);
    while(!playTone());
  }
}

//Display pulsating rainbow pattern
//return button state at end of chapter
byte chapter_rainbow()
{
  uint32_t pixels[LED_COUNT];
  bool clear_flag=true;
  byte next_state;
  while((next_state=get_next_chapter_state())==NO_STATE_CHANGE)
  {
    for(byte iter=0;iter<LED_COUNT;iter++)
    {
      //if(clear_flag) pixels[iter]=read_eeprom_color(EEPROM_OFFSET_ADDRESS_BACKGROUND+sizeof(uint32_t)*(BACKGROUND_INDEX_STEEPLE_CHASE+BACKGROUND_COUNT*iter));
      if(clear_flag) pixels[iter]=EEPROMReadLong(EEPROM_ADDRESS_BACKGROUND_RAINBOW+sizeof(uint32_t)*iter);
      else pixels[iter]=next_wheel_color(pixels[iter]);
      strip.setPixelColor(iter,pixels[iter]);
    }
    clear_flag=false;
    //if(pixels[10]==pixels[3]) strip.setPixelColor(0,0xFFFFFFFF);
    strip.show();
    delay(5);
  }
  return next_state;
}

//helper method for rainbow animations to increment 
uint32_t next_wheel_color(uint32_t color_in)
{
  uint8_t r=color_in>>16;
  uint8_t g=color_in>>8;
  uint8_t b=color_in;
  if(r==0)
    if(g==0){ r++; b--; }
    else{ g--; b++; }
  else{
    if(g==0){
      if(b==0){ r--; g++; }
      else{ r++; b--; }
    }else{ r--; g++; }
  }
  return strip.Color(r,g,b);//3670
}

//use same code for two chapters
//is_flag chapter displays a static flag pattern and plays national anthem
//!is_flag chapter displays static rainbow pattern and plays a song
//audio is silenced at end of play waiting for user input to either restart audio (short press) or go to next chapter (long press)
void chapter_video(bool is_flag){
  set_background(is_flag?EEPROM_ADDRESS_BACKGROUND_FLAG:EEPROM_ADDRESS_BACKGROUND_TIMER,0);//TODO: revise 10 timer colors so that (255,0,255) is 11th color
  strip.show();
  while(true)
  {
    begin_sound();
    restart_sound(is_flag?EEPROM_ADDRESS_AUDIO_FLAG:EEPROM_ADDRESS_AUDIO_SONG,is_flag);
    while(!playTone()) if(sound_state==GO_TO_ROOT) return;
    stop_sound();
    while(!is_button_down());
  }
}

//if there are any flags (is_charging, or is_battery_exhausted) that need to be process, halt everything else and address those
void book_battery_state()
{
  chapter_battery_exhausted();
  chapter_battery_charging();
}

//secret chapter to jump to when battery level gets too low
//only executes chapter if battery is exhausted
void chapter_battery_exhausted()
{
  if(is_battery_exhausted())
  {
    stop_sound();
    strip.setBrightness(LOW_POWER_LED_BRIGHTNESS);//low brightness to save power
    set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,0);
    strip.setPixelColor(0,strip.Color(255,0,0));
    strip.show();
    while(!is_charging());//lock execution TODO: make clearer by brightening red LED when button pressed, then dim after release
  }
}

//secret chapter to jump to when battery charging is detected
//unplug charging and restart pendant to clear
//precon: this method is only called when the sound is disabled
void chapter_battery_charging()
{
  if(is_charging())
  {
    //bool need_to_restart_sound=is_sound_enabled;//store sound state at beginning of charging cycle to re-enable it later
    //stop_sound();
    reset_battery_memory();
    strip.setBrightness(LOW_POWER_LED_BRIGHTNESS);//low brightness to save power
    set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,0);
    while(is_charging()||get_next_chapter_state()==NO_STATE_CHANGE)
    {//display chaging status until user presses the button at full charge
      strip.setPixelColor(0,strip.Color(is_charging()?255:0,255,0));
      strip.show();
      delay(100);//reduce polling to 10 hz
    }
    //if(need_to_restart_sound) begin_sound();
    strip.setBrightness(home_brightness);
    /*strip.setPixelColor(0,strip.Color(255,255,0));//yellow indicator on LED 0
    strip.show();
    while(is_charging());
    strip.setPixelColor(0,strip.Color(0,255,0));//green when fully charged
    strip.show();
    exit(0);*///halt all execution (hold green LED only) until user cycles power, TODO: maybe use any button press as release from charging lock
  }
}

//MSB at 1 indicates battery undervoltage, remaining bits are counter from 0 to 128 (resets to 64 at 128) of the number of times the measured voltage was >MINIMUM
//if >MINIMUM, increase counter +1; if <MINIMUM, decrement counter -1; if decremented so much that counter goes negative (MSB = 1) then flag undervoltage condition
bool is_battery_exhausted()
{
  if(battery_memory&0x80) return true;//if counter overflowed negative, flag under voltage
  if(battery_memory&0x40) reset_battery_memory();//positive counter overflow: battery is above minium
  if(Vrail_leo()>MIN_BATTERY_MILLIVOLTS) battery_memory++; else battery_memory--;
  return false;
  //return Vrail_leo()<MIN_BATTERY_MILLIVOLTS;//subject to jitter on measurement, can flag <3V when powered on 3.3V rail
}

bool reset_battery_memory(){ battery_memory=64; }

bool is_charging()
{//note: power cycling while still connected to programmer may trigger detection of "charging state" due to independent control of programmer pins
  if(digitalRead(PIN_CHARGING)) charge_state--; else charge_state++;//if HIGH, then NOT charging or fully charged, if LOW then charging
  if(charge_state==0xFF) charge_state=0xC0;//prevent wrap over
  if(charge_state==0x00) charge_state=0x40;
  return charge_state>>7;//query MSB
  //return !digitalRead(PIN_CHARGING);
}

//one of two games:
//Acid Rain
//  blue rain drops fall down in left and right columns, blue lightening flashes in center
//  positioning the player paddle at the bottom below the rain increases the player score
//  represented by the paddle color (rainbow: red with 0 lives, purple with 8 lives)
//  there are also red rain drops and lightening that subtract player lives
//  tapping the button cycles the paddle round-robbin style from left to middle to right, back to left
//Flappy Bird
//  stalagmites and stalactites move from right to left across field of view
//  they always have a gap between them that the player, on the left side of the screen, must navigate through
//  player can tap button to increase hgith of player paddle
//  after a delay, the paddle will fall back down, so user must tap button rapidly to keep paddle in the air, if that is what is needed to clear the obstacle gap
void book_game(bool is_acid_rain)
{
  byte current_frame_game=0;//which frame tha rain animation is on
  byte is_good_index_game=0;//for level 0, every other rain is good, for level 2, every 4th is good, keep track of this here
  bool is_good_obstacle=true;
  byte column_index_2x_game=0;//max 30, then wraps to 0
  byte button_state;
  byte lives_game=0;
  byte paddle_position=7;//magic number 7 is: LED 7 through 9 are valid paddle positions at bottom left of display, pressing button increments paddle position round-robin style
  unsigned long last_frame_ms=millis();//time that the last frame transitioned;
  unsigned long last_gravity_ms=0x8FFFFFFF;//last time the flappy paddle moved down due to gravity
  const unsigned long GRAVITY_DURATION_MS=700;//number of milliseconds to wait until updating gravity in flappy game (decrease paddle position)
  const byte animation_frame_count=(is_acid_rain?FRAME_COUNT_ACID:FRAME_COUNT_FLAPPY)/3;//always have three levels and three different types of obstacle configurations
  const word eeprom_base_address=is_acid_rain?EEPROM_ADDRESS_GAME_RAIN:EEPROM_ADDRESS_GAME_FLAPPY;
  const byte total_frame_count=animation_frame_count*3;
  while(lives_game<MAX_LIVES_GAME)
  {
    if((button_state=get_next_chapter_state())==GO_TO_ROOT) return;
    if(button_state==GO_TO_NEXT_CHAPTER)
    {
      if(is_acid_rain) paddle_position++;
      else{
        paddle_position--;
        last_gravity_ms=millis();
      }
    }
    if((last_gravity_ms+GRAVITY_DURATION_MS)<millis())
    {
      paddle_position++;
      last_gravity_ms=millis();
    }
    if(paddle_position==10) paddle_position=7;
    if(paddle_position==3)  paddle_position=4;
    if(paddle_position==8&&!is_acid_rain) paddle_position=7;
    byte level_game=lives_game/3;//increment level every 3 lives gained: increase speed of rain and decrese number of good rain
    //word time_pre_shift=EEPROMReadWord(EEPROM_ADDRESS_GAME_RAIN+(current_frame_game%FRAME_COUNT_ACID+FRAME_COUNT_ACID*level_game)*sizeof(word));
    //if(!is_acid_rain) time_pre_shift=EEPROMReadWord(EEPROM_ADDRESS_GAME_FLAPPY+(current_frame_game%FRAME_COUNT_FLAPPY+FRAME_COUNT_FLAPPY*level_game)*sizeof(word));
    word time_pre_shift=EEPROMReadWord(eeprom_base_address+(current_frame_game%animation_frame_count+animation_frame_count*level_game)*sizeof(word));
    unsigned long frame_duration_ms=(time_pre_shift>>11)<<6;
    bool is_frame_update=(last_frame_ms+frame_duration_ms)<millis();//if curent counter has passed the time the frame is supposed to update, then update state machine
    word paddle_frame=0x0001<<paddle_position;
    word game_frame=EEPROMReadWord(eeprom_base_address+current_frame_game*sizeof(word));
    if(is_frame_update)
    {
      last_frame_ms=last_frame_ms+frame_duration_ms;
      current_frame_game++;
      if(current_frame_game%animation_frame_count==0)//precon: every rain animation is 8 frames long, therefore when the animation is done, it ends on the start of the next frame (except frame 24 which is --> 0)
      {
        //if on last frame of animation (when rain overlaps paddle), check for intersection of rain with paddle
        if(paddle_frame&game_frame)//intersection between paddle and rain detected
        {
          if(is_good_obstacle) lives_game++;
          else if(lives_game>0) lives_game--;//don't decrement if in base case: 0 lives (otherwise ends up with 0xFF lives because unsigned byte)
        }else if(!is_acid_rain){
          if(lives_game>0) lives_game--;//remove lives on miss
        }
        current_frame_game+=animation_frame_count*(0x03&(COLUMN_DELTA_GAME>>column_index_2x_game));//get the "0 to 3" pseudorandom number and then add to current frame to determine the next column that will have rain
        column_index_2x_game=(column_index_2x_game+2)%32;//increment two places deeper into the "0 to 3" pseudorandom-number generator list
        current_frame_game=current_frame_game%total_frame_count;
        is_good_index_game=(is_good_index_game+1)%(2+level_game);//if on second bad acid rain (value 1) and on level 0, then incrementing acid counter to 2, then %2, resets acid counter to 0
        //but if on level 2, there would be two more bad acid rains left before going back to 0
      }
    }
    //also render LEDs and paddle
    set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,0);
    uint32_t paddle_color=EEPROMReadLong(EEPROM_ADDRESS_BACKGROUND_TIMER+lives_game*sizeof(uint32_t));//paddle color determine by number of lives
    set_background_bool(paddle_frame,paddle_color);//display paddle
    set_background_bool(game_frame,is_good_obstacle?strip.Color(0,0,255,0):strip.Color(255,0,0,0));//display rain (either good or bad) over paddle (if they're intersecting)
    //is_good_obstacle=is_good_index_game==0&&is_acid_rain;
    is_good_obstacle=(is_good_index_game==0&&is_acid_rain)||!is_acid_rain;
    strip.show();
  }
  while(true)
  {//winning any game dumps to an animation loop.  Short press changes animation loop.  Long press exits to root menu
    if(chapter_rainbow()==GO_TO_ROOT) return;
    if(chapter_meteor()==GO_TO_ROOT) return;
    if(chapter_popcorn()==GO_TO_ROOT) return;
  }
}

//given a list of 1's and 0's fill in the 1's with the specified color
void set_background_bool(word bool_list,uint32_t color)
{
  for(byte led=0;led<LED_COUNT;led++)
  {
    if(bool_list&0x01) strip.setPixelColor(led,color);
    bool_list=bool_list>>1;
  }
}

//effect inspired by https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
//bright white head, yellow body, sporadic decaying red tail
//return button state at end of chapter
byte chapter_meteor()
{
  uint32_t pixels[LED_COUNT];//may boot up to weird values that make state machine (blue) misbehave on first pass before meteor appears
  byte decay[LED_COUNT];//similar boot-up issue
  set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,0);
  //unsigned long start_ms=millis();
  bool is_init=true;
  byte next_state;
  while((next_state=get_next_chapter_state())==NO_STATE_CHANGE)
  {
    byte animation_frames=44;
    //byte led_meteor=(animation_frames-LED_COUNT+(start_ms-millis())/128)%animation_frames;
    byte led_meteor=((~millis())/128)%animation_frames;
    for(byte led=0;led<LED_COUNT;led++)
    {
      byte white=255-(millis()%128)*2;
      byte red=pixels[led]>>16;
      byte green=pixels[led]>>8;
      byte blue=pixels[led];
      if((led+1==led_meteor) || is_init)
      {
        red=254;
        green=254;
        blue=255;
        white=255-white;
        //decay[led]=12+random(3);
        decay[led]=9+random(8);//9-30
      }else if(led!=led_meteor) white=0;
      byte coin=random(decay[led]);
      if(blue>0) blue-=3;
      if(green>0) green-=1;//coin>6 and 
      //if(coin>8 and red>0) red-=2;//[0.333-0.466]
      if(coin>3 and red>0) red-=1;//[0.666-0.95]
      pixels[led]=strip.Color(red,green,blue,white);
      //strip.setPixelColor(led,pixels[led+4]);
      byte led_shifted=(led+4)%LED_COUNT;
      if(led<7)
        strip.setPixelColor(led,pixels[led_shifted]);//7536
      else
        strip.setPixelColor(LED_COUNT-led+6,pixels[led_shifted]);//11-7+6=10, 11-10+6=7
    }
    strip.show();
    is_init=false;
  }
  return next_state;
}

//is 7386 with word, 7418 storing uint32
byte chapter_popcorn()
{
  byte next_state;
  byte led_state[LED_COUNT]={0,0,0,0,0,0,0,0,0,0,0};
  uint32_t base_color[LED_COUNT];//pointer to index of rainbow EEPROM pattern
  byte rand_led=0;
  byte states_between_led=50;//how many states an LED much pass through before the next led in sequence begins transitioning
  word prev_color_index=0;
  while((next_state=get_next_chapter_state())==NO_STATE_CHANGE)
  {
    for(byte led=0;led<LED_COUNT;led++)
    {
      bool is_random=random(255)<4;
      bool is_standby_state=led_state[led]==0;
      if(is_standby_state&&is_random)
      {
        led_state[led]=1;//kick-on led state machine
        prev_color_index+=random(24);
        prev_color_index=prev_color_index%(256*3);
        uint32_t this_color=EEPROMReadLong(EEPROM_ADDRESS_BACKGROUND_RAINBOW);
        for(word iter=0;iter<prev_color_index;iter++) this_color=next_wheel_color(this_color);//cycle through colors and assign
        base_color[led]=this_color;
      }
      strip.setPixelColor(led,get_popcorn_color(led_state[led],base_color[led]));
      if(!is_standby_state) led_state[led]++;
    }
    strip.show();
    delay(3);//program becomes unstable if this is removed... why?
  }
  return next_state;
}

uint32_t get_popcorn_color(byte state,uint32_t base_color)
{
  if(state==0) return strip.Color(0,0,0,0);
  if(state<2) return strip.Color(255,255,255,255);//bright white
  byte white=(33-state)<<8;
  byte red=base_color>>16;
  byte green=base_color>>8;
  byte blue=base_color;
  if(state<33) return strip.Color(red,green,blue,white);//white mixed with color
  if(state<127) return base_color;//pure color
  word ratio=255-state;
  return strip.Color(((word)red*ratio)/128,((word)green*ratio)/128,((word)blue*ratio)/128);
}
#endif
