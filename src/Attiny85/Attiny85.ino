//Step 1. Program an Arduino with the ArduinoISP program: File >> Examples >> 11.ArduinoISP >> ArduinoISP
//Step 2. Connect the ISP Arduino to the J3 header (the J3 pinout matches the Attiny pinout, note the white circle adjacent to pin 1):
//  https://hackster.imgix.net/uploads/cover_image/file/50546/Programming%20ATtiny85%20with%20Arduino%20Uno_bb.png?auto=compress%2Cformat&w=900&h=675&fit=min
//Step 3. Acquire Attiny core through steps here: https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829
//Step 4. Enable Arduino IDE to retain EEPROM values between reflashing
//  File >> Preferences >> (Note "preferences" location at bottom of window)
//  Navigate to "preferences" folder
//  From there, navigate to /packages/attiny/hardware/avr/1.0.2/
//  AT C:\Program Files (x86)\Arduino\hardware\arduino\avr\boards.txt
//  WAS: ATtinyX5.menu.clock.internal8.bootloader.high_fuses=0xdf
//  IS:  ATtinyX5.menu.clock.internal8.bootloader.high_fuses=0xd7
//  ( Core settings ref https://forum.arduino.cc/index.php?topic=393434.0 )
//  ( EEPROM fuse ref https://forum.arduino.cc/index.php?topic=278083.0 )
//Step 5. Restart Arduino IDE
//Step 6. Burn bootloader, Attiny85, 8 MHz, Internal
//  FYI, this may require either an FTDI or another Arduino to act as an intermediate programmer, ref. IDE >> File >> Examples >> 11.ArduinoISP
//  https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829
//Step 7. Set BURN_EEPROM to 1 and upload program
//Step 8. Set BURN_EEPROM to 0 and upload program
#define BURN_EEPROM 0

// ---- Libraries ----
// -- LEDs --
#include <Adafruit_NeoPixel.h> //LEDs
#ifdef __AVR__
  #include <avr/power.h>
#endif

// -- Top Level IO --
const byte PIN_LED=1;//D1 is physical pin 6
const byte LED_COUNT=11;
neoPixelType STRIP_TYPE=NEO_GRBW + NEO_KHZ800;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN_LED, STRIP_TYPE);

// -- EEPROM Sound --
const word EEPROM_ADDRESS_SHORT_CHARACTER=0;
const byte SHORT_SOUND_CHARACTER_COUNT=6;//ref. "Tune" character list
const byte SHORT_SOUND_COUNT=7;
const byte SOUND_PRESS_COUNT_ROOT=8;//~2 seconds of 1/8 tick counts
const byte SOUND_PRESS_COUNT_CHAPTER=1;//1/8 second press is enough to go to next chapter
const word EEPROM_ADDRESS_AUDIO_FLAG=EEPROM_ADDRESS_SHORT_CHARACTER+SHORT_SOUND_CHARACTER_COUNT*SHORT_SOUND_COUNT;
const word AUDIO_FLAG_CHARACTER_COUNT=34;
const word EEPROM_ADDRESS_AUDIO_SONG=EEPROM_ADDRESS_AUDIO_FLAG+AUDIO_FLAG_CHARACTER_COUNT;//76
const word AUDIO_SONG_CHARACTER_COUNT=176;
const word EEPROM_TUNE_LENGTH=EEPROM_ADDRESS_AUDIO_SONG+AUDIO_SONG_CHARACTER_COUNT-EEPROM_ADDRESS_SHORT_CHARACTER; //number of characters in EEPROM for sound, 252

// -- EEPROM LED Backgrounds --
const byte BACKGROUND_COUNT=4;
const word EEPROM_BASE_ADDRESS_BACKGROUND=EEPROM_ADDRESS_AUDIO_SONG+AUDIO_SONG_CHARACTER_COUNT;
const word EEPROM_ADDRESS_BACKGROUND_FLAG=    EEPROM_BASE_ADDRESS_BACKGROUND+0*LED_COUNT*sizeof(uint32_t);
const word EEPROM_ADDRESS_BACKGROUND_RAINBOW= EEPROM_BASE_ADDRESS_BACKGROUND+1*LED_COUNT*sizeof(uint32_t);
const word EEPROM_ADDRESS_BACKGROUND_TIMER=   EEPROM_BASE_ADDRESS_BACKGROUND+2*LED_COUNT*sizeof(uint32_t);
const word EEPROM_ADDRESS_BACKGROUND_BOOK=    EEPROM_BASE_ADDRESS_BACKGROUND+3*LED_COUNT*sizeof(uint32_t);//and sound
const word EEPROM_ADDRESS_BACKGROUND_BLACK=512;//invalid value, EEROM only has bytes 0-511
const word BACKGROUND_UNUSED_BYTES=sizeof(uint32_t)*4;//4 colors unused at end of last book

// -- EEPROM Game Backgrounds --
const byte FRAME_COUNT_ACID=24;
const byte FRAME_COUNT_FLAPPY=12;
const word EEPROM_ADDRESS_GAME_RAIN=EEPROM_BASE_ADDRESS_BACKGROUND+sizeof(uint32_t)*BACKGROUND_COUNT*LED_COUNT-BACKGROUND_UNUSED_BYTES;
const word EEPROM_ADDRESS_GAME_FLAPPY=EEPROM_ADDRESS_GAME_RAIN+FRAME_COUNT_ACID*sizeof(word);
const word EEPROM_ADDRESS_UNUSED_BEGIN=EEPROM_ADDRESS_GAME_FLAPPY+FRAME_COUNT_FLAPPY*sizeof(word);//beginning of unallocated space in EEPROM

#if BURN_EEPROM==0

// ---- State Machines ----
unsigned long start_button_ms=0xAFFFFFFF;//in chapter state machine, this is the start time of the button press, in the book-selection state machine, this is the end time of the button press
byte book_index=0;//TODO default to 0
const byte BOOK_COUNT=7; // there are 7 books: 0.home, 1.timer/battery, 2.song, 3.monotones, 4.acid rain game, 5.flappy bird game, 6.USA flag
const byte NO_STATE_CHANGE=0;
const byte GO_TO_NEXT_CHAPTER=1;
const byte GO_TO_ROOT=2;//jump out of current book and select new book

// -- Button --
const byte PIN_BUTTON=3; //D3 is physical pin 2 https://cdn.sparkfun.com/r/600-600/assets/f/8/f/d/9/52713d5b757b7fc0658b4567.png
const byte LONG_PRESS_SMS=9; //1=0.001seconds, 9=0.512 seconds, etc.  Pressing button for < this value interacts with or changes chapters, SMS = Shifted value and expressed in MilliSeconds
//holding button longer than this changes the book selection
const byte TIMEOUT_SMS=3; //0=0.255 seconds, 3=2.048 seconds, 4=4.096 sec, etc.  If no user input is received within this time frame, the state machine times out and moves on to the next state (like entering the selected book)
const byte DEBOUNCE_MS=50; //disregard button transitions that occur within this interval of another button transition
const byte BLINK_LED_SMS=8; //0=0.002 sec (500 Hz), 6=0.128 sec (7.8 Hz)

// -- Home --
const byte HUE_DELAY_MS=10;//milliseconds between each successive (slightly different) color display
uint32_t home_hue=strip.Color(255,0,0);
byte home_brightness=255;//20;//TODO default max 255

// -- Sound --
//FYI: pin D4 used for waveform output, physical pin 3
bool is_sound_enabled=false;//flag to track the status of whether sound is enabled or not
byte sound_press_count=0;//number of 1/8 sec ticks encountered while button was down
byte sound_state=NO_STATE_CHANGE;//use different state machine for button presses during audio playback due to chalenges with millis() (counts 4x speed), slow clock speed (1/8 sec interrupts), etc
const byte PIN_AMPLIFIER=0; //D0 is physical pin 5

// -- Acid Rain Game --
byte MAX_LIVES_GAME=9;
unsigned long const COLUMN_DELTA_GAME=0b01000100100001100110001001011010;//every two bits is a number 0-2, representing which column relative to the current rain column, that will have rain next
//used as a "sudo-random number generator"

// -- Hidden Chapters --
word MIN_BATTERY_MILLIVOLTS=3000;//2.9 V minimum trips battery warning
byte PIN_CHARGING=2; //D2 is physical pin 7, detect when plugged into USB
byte LOW_POWER_LED_BRIGHTNESS=3;//brightness between 0 (min) and 255 (max) to display indicator that battery is dying or charging
byte battery_memory;
byte charge_state=0x40;// charge_state>=0x80 is charging (MSB=1), else NOT charging

void setup() {
  reset_battery_memory();
  strip.begin();
  strip.setBrightness(home_brightness);
  strip.show();//clear LEDs
  pinMode(PIN_CHARGING,INPUT_PULLUP);//detect when external charge circuit is activated, LOW is charging, HIGH is fully charged, floating is charging
  pinMode(PIN_BUTTON,INPUT_PULLUP);//user button input, HIGH is button_down, LOW is button_up
  pinMode(PIN_AMPLIFIER,OUTPUT);//external amplifier enable pin, HIGH is enabled, LOW is disabled
  enable_amplifier(false);
}

//top level state machine to display book selection
void loop() {
  display_book(book_index);
  while(is_button_down()) start_button_ms=millis();
  while(!is_button_down())
  {
    display_book(book_index);//display 2 second count down animation to book being selected
    if((millis()-start_button_ms)>2048) run_chapter(book_index);//run chapter (upon chapter exit, the button will be down for >0.5 sec)
  }
  if((millis()-start_button_ms)>DEBOUNCE_MS) book_index=(book_index+1)%BOOK_COUNT;//select next book
  start_button_ms=millis()-1;
}

//due to internal pull-up, button is HIGH when unpressed, LOW when pressed
bool is_button_down(){ return !digitalRead(PIN_BUTTON); }

//root menu display: 1-7 LEDs ON white and one LED set to one of seven colors
void display_book(byte book_index)
{
  uint8_t white=((start_button_ms-millis())>>TIMEOUT_SMS);//over the span of 2.048 seconds (0.255<<3), transition from 0xFF white to 0x00 white
  uint32_t book_color=EEPROMReadLong(EEPROM_ADDRESS_BACKGROUND_BOOK+sizeof(uint32_t)*book_index);
  for(byte iter=0;iter<LED_COUNT;iter++)
  {
    if(iter<BOOK_COUNT)
    {
      if(iter<=book_index) strip.setPixelColor(BOOK_COUNT-1-iter,strip.Color(0,0,0,white));
      else strip.setPixelColor(BOOK_COUNT-1-iter,strip.Color(0,0,0,0));//black
    }else{
      strip.setPixelColor(iter,book_color);//display solid color bar at bottom to reinforce user understanding of chapter selection
    }
  }
  strip.show();
}

//execute one chapter
//returns when the button has been (and still is) held down for an extended period of time
void run_chapter(byte book_index)
{
  start_button_ms=0;
  sound_state=NO_STATE_CHANGE;
  sound_press_count=0;
  switch(book_index)
  {
    default:
    case 0: book_home(); break;
    case 1: book_time_and_battery(); break;//TODO: combine bottom four LEDs of time to show battery, with top 7 LEDs to show time counter
    case 2: chapter_video(false); break;//rainbow tune
    case 3: book_sound(); break;//theme sounds
    case 4: book_game(true); break;//acid rain
    case 5: book_game(false); break;//flappy bird
    case 6: chapter_video(true); break;//flag
  }
  stop_sound();
}

//interpret what the user wants to do by reading the button state
byte get_next_chapter_state()
{
  book_battery_state();
  unsigned long time_held_ms=millis()-start_button_ms;
  if(is_button_down())
  {
    if(start_button_ms==0) start_button_ms=millis();
    else if(time_held_ms>>LONG_PRESS_SMS) return GO_TO_ROOT;
  }else{
    if(start_button_ms!=0 and time_held_ms>DEBOUNCE_MS)
    {
      start_button_ms=0;
      return GO_TO_NEXT_CHAPTER;
    }
  }
  return NO_STATE_CHANGE;
}
#endif
