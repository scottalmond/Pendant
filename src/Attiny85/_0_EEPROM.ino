
#include <EEPROM.h> //EEPROM

#if BURN_EEPROM!=0
const byte DEBUG_BRIGHTNESS=20;//how bright to display the verification stage
const byte PIN_DEBUG=3;//input button to change state of debugger, illuminate the debugger LED when done flashing EEPROM

const PROGMEM char Tune[EEPROM_TUNE_LENGTH]="A(^^)\0"
                                            "C(^^)\0"
                                            "G(^^)\0"
                                            "A(CG)\0" //6
                                            "A(C^)\0"
                                            "C(G^)\0"
                                            "A(G^)\0"
                                            "4,CCD6,b2,C4,DEEF6,e2,d4,cDcb12,C\0"//34 characters
                                            "C(-1:C)Fe2,dE4,F(-1:D)2,eF4,A(-1:G)g2,f(-1:F)eF(-1:E)G4,f(-1:D)e(-1:C)"//176 char 
                                            "2,d(-2:B)Edc4,b(-2:G)Gc(-1:C)Fe2,dE4,F(-1:D)2,eF4,A(-1:G)g"
                                            "2,A(-1:F)gA(-1:E)Cb(-1:G)gB(-1:B)D4,c(-1:C)g8,C\0";

const uint32_t BACKGROUND[BACKGROUND_COUNT][LED_COUNT]={{
  strip.Color(  1,  2,  3,255),//flag https://www.legion.org/flag/questions-answers/91472/what-are-exact-shades-colors-blue-and-red
  strip.Color(  0, 40,104,  0),
  strip.Color(  0,  0,  0,255),
  strip.Color(191, 10, 48,  0),
  strip.Color(191, 10, 48,  0),
  strip.Color(191, 10, 48,  0),
  strip.Color(  0,  0,  0,255),
  strip.Color(  0, 40,104,  0),
  strip.Color(  0, 40,104,  0),
  strip.Color(  0, 40,104,  0),
  strip.Color(  0, 40,104,  0)
},{
  strip.Color(255,  0,  0,  0),
  strip.Color(201, 54,  0,  0),
  strip.Color(146,109,  0,  0),
  strip.Color( 92,163,  0,  0),
  strip.Color( 37,218,  0,  0),
  strip.Color(  0,237, 18,  0),
  strip.Color(  0,183, 72,  0),
  strip.Color(  0,183, 72,  0),//steeple chase, reordered rainbow_11: bottom 4 (inc hue) are opposite order of first 7 (reverse hue)
  strip.Color(  0,237, 18,  0),
  strip.Color( 37,218,  0,  0),
  strip.Color( 92,163,  0,  0)
},{
  strip.Color(255,  0,  0,  0),//timer and game lives, rainbow_11
  strip.Color(255,140,  0,  0),
  strip.Color(230,255,  0,  0),
  strip.Color( 96,255,  0,  0),
  strip.Color(  0,255, 45,  0),
  strip.Color(  0,255,185,  0),
  strip.Color(  0,185,255,  0),
  strip.Color(  0, 45,255,  0),
  strip.Color( 96,  0,255,  0),
  strip.Color(230,  0,255,  0),
  strip.Color(255,  0,140,  0)
},{
  strip.Color(  0,  0,  0,255),//books white+rainbow_6
  strip.Color(255,  0,  0,  0),
  strip.Color(255,255,  0,  0),
  strip.Color(  0,255,  0,  0),
  strip.Color(  0,255,255,  0),
  strip.Color(  0,  0,255,  0),
  strip.Color(255,  0,255,  0),
  strip.Color(  0,  0,  0,  0),//unused
  strip.Color(  0,  0,  0,  0),
  strip.Color(  0,  0,  0,  0),
  strip.Color(  0,  0,  0,  0)
}};
//(4 bytes/led)*(11 leds/background)*(4 backgrounds) = 176 bytes.  176 bytes - (4 bytes/led)*(4 leds) = 160 bytes for led backgrounds

//acid game --> (2 bytes/frame)*(8 frames/level)*(3 levels) = 48 bytes
//flappy game-> (2 bytes/frame)*(4 frames/level)*(3 levels) = 24 bytes
//252+160+48+24= 484<512 by 28 bytes

const word frames_acid[FRAME_COUNT_ACID]={//MSB 5 bits of list index 0-7 are frame delays for level 0, list index 8-15 are frame delays for level 1, list index 16-23 are frame delays for level 2
  //LSB 11 bits for list index 0-7 are which LEDs are illuminated for left column acid rain, list index 8-15 is lightening in the center, list index 16-23 is right clumn rain
  0b0000000000000000,//acid rain frame 0 [0 sec, OFF], left rain and level 0 timing
  0b0100000000010000,//[0.5 sec, LED 4]
  0b0100000000010000,//[0.5 sec, LED 4]
  0b0100000000100000,//[0.5  sec, LED 5]
  0b0100000000100000,//[0.5  sec, LED 5]
  0b0100000001000000,//[0.5 sec, LED 6]
  0b0100000001000000,//[0.5 sec, LED 6]
  0b1000000010000000,//frame 7 [1 sec, LED 7]
  0b0000000000000000,//frame 8 [0 sec, OFF], begin middle (lightening) rain and level 1 timing
  0b0011000000001000,//[0.38 sec, LED 3]
  0b0011000000000000,//[0.38 sec, OFF]
  0b0011000000001000,//[0.38 sec, LED 3]
  0b0011000000000000,//[0.38 sec, OFF]
  0b0011000000001000,//[0.38 sec, LED 3]
  0b0011000000000000,//[0.38 sec, OFF]
  0b0110000100000000,//frame 15 [0.77 sec, LED 8]
  0b0000000000000000,//frame 16 [0 sec, OFF], right rain and level 2 timing
  0b0010000000000001,//[0.25 sec, LED 0]
  0b0010000000000001,//[0.25 sec, LED 0]
  0b0010000000000010,//[0.25 sec, LED 1]
  0b0010000000000010,//[0.25 sec, LED 1]
  0b0010000000000100,//[0.25 sec, LED 2]
  0b0010000000000100,//[0.25 sec, LED 2]
  0b0100001000000000//frame 23 [0.5 sec, LED 9]
};
/*const word frames_flappy[FRAME_COUNT_FLAPPY]={
  0b0100000000000000, //frame 1 [0.5 sec, OFF] bottom clear
  0b0100000000000111, //[0.5 sec, led 0, 1, 2]
  0b0100000000001000, //[0.5 sec, led 3]
  0b0100000001110000, //frame 3 [0.5 sec, led 4, 5, 6]
  0b0011010000000000, //frame 4 [0.38 sec, led 10] middle clear
  0b0011001000000001, //[0.38 sec, led 9, led 0]
  0b0011000100000000, //[0.38 sec, led 8]
  0b0011000010010000, //frame 7 [0.38 sec, led 4,7]
  0b0010010000000000, //frame 8 [0.25 sec, led 10] top clear
  0b0010001000000110, //[0.25 sec, led 1,2,9]
  0b0010000100001000, //[0.25 sec, led 3,8]
  0b0010000011100000  //frame 11 [0.25 sec, led 5,6,7]
};*/
const word frames_flappy[FRAME_COUNT_FLAPPY]={//reworked with positive logic: hitting a '1' with the paddle is life++ (WAS life--), also increase make 0.38 sec min frame time to slow animation
  0b0101010000000000, //frame 1 [0.62 sec, OFF] bottom life++ --> led 10
  0b0101001000000000, //[0.62 sec, led 0, 1, 2] --> led 9
  0b0101000100000000, //[0.62 sec, led 3] --> led 8
  0b0101000010000000, //frame 3 [0.62 sec, led 4, 5, 6] --> led 7
  0b0100000000000000, //frame 4 [0.5 sec, led 10] middle life++ --> OFF
  0b0100000000000110, //[0.5 sec, led 9, led 0] --> led 1,2
  0b0100000000001000, //[0.5 sec, led 8] --> led 3
  0b0100000001100000, //frame 7 [0.5 sec, led 4,7] --> led 5,6
  0b0011000000000000, //frame 8 [0.38 sec, led 10] top life++ --> OFF
  0b0011000000000001, //[0.38 sec, led 1,2,9] --> led 0
  0b0011000000000000, //[0.38 sec, led 3,8] --> OFF
  0b0011000000010000  //frame 11 [0.38 sec, led 5,6,7] --> led 4
};


void setup(){
  const byte PIN_IND=2;//tied to Arduino indicator LED on pin 13
  pinMode(PIN_IND,OUTPUT);
  digitalWrite(PIN_IND,LOW);
  delay(500);
  digitalWrite(PIN_IND,HIGH);
  delay(500);
  digitalWrite(PIN_IND,LOW);
  delay(500);
  strip.begin();
  strip.setBrightness(DEBUG_BRIGHTNESS);
  strip.show();//clear LEDs
  pinMode(PIN_DEBUG,INPUT_PULLUP);

  #if BURN_EEPROM==1
  //write songs
  word eeprom_address=EEPROM_ADDRESS_SHORT_CHARACTER;
  for(word index=0;index<EEPROM_TUNE_LENGTH;index++)
  {
    EEPROM.update(eeprom_address,pgm_read_byte(&(Tune[index])));
    eeprom_address+=sizeof(byte);
  }

  //write backgrounds
  for(word background=0;background<BACKGROUND_COUNT;background++)
  {
    for(word pixel=0;pixel<LED_COUNT;pixel++)
    {
      EEPROMWriteLong(eeprom_address,BACKGROUND[background][pixel]);
      eeprom_address+=sizeof(uint32_t);
    }
  }

  //skip back over unused bytes
  eeprom_address=EEPROM_ADDRESS_GAME_RAIN;

  //write game frames
  for(byte index=0;index<FRAME_COUNT_ACID;index++)
  {
    EEPROMWriteWord(eeprom_address,frames_acid[index]);
    eeprom_address+=sizeof(word);
  }
  for(byte index=0;index<FRAME_COUNT_FLAPPY;index++)
  {
    EEPROMWriteWord(eeprom_address,frames_flappy[index]);
    eeprom_address+=sizeof(word);
  }
  #endif
  
  digitalWrite(PIN_IND,HIGH);
  
  //verification
  //song characters
  word eeprom_start_address=0;
  word eeprom_address_count=4;
  for(word address=eeprom_start_address;address<(eeprom_start_address+eeprom_address_count);address++)
  {
    byte val=EEPROM.read(address);
    debug_eeprom(address,strip.Color(0,0,255),strip.Color(255,0,0));//address: blue=1, red=0
    while(digitalRead(PIN_DEBUG));
    while(!digitalRead(PIN_DEBUG));
    debug_eeprom(val,strip.Color(0,255,0),strip.Color(255,0,0));//value: green=1,red=0
    while(digitalRead(PIN_DEBUG));
    while(!digitalRead(PIN_DEBUG));
  }

  //colored backgrounds
  for(byte background=0;background<BACKGROUND_COUNT;background++)
  {
    set_background(EEPROM_BASE_ADDRESS_BACKGROUND+background*LED_COUNT*sizeof(uint32_t),0);
    strip.show();
    while(digitalRead(PIN_DEBUG));
    while(!digitalRead(PIN_DEBUG));
  }

  set_background(EEPROM_ADDRESS_BACKGROUND_BLACK,0);
  strip.setPixelColor(0,strip.Color(0,0,0,255));
  strip.show();
  exit(0);
}

void debug_eeprom(word value,uint32_t vis,uint32_t no_vis)
{
  for(byte iter=0;iter<LED_COUNT;iter++)
  {//LSB at 0
    if(value&0x01) strip.setPixelColor(iter,vis);
    else strip.setPixelColor(iter,no_vis);
    value>>=1;
  }
  if(vis!=no_vis) strip.show();
}

void loop(){ exit(0); }

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void EEPROMWriteLong(word address, long value)
{
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte four = value;
  byte three = value >> 8;
  byte two = value >> 16;
  byte one = value >> 24;
  
  //Write the 4 bytes into the eeprom memory.
  EEPROM.update(address, four);
  EEPROM.update(address + 1, three);
  EEPROM.update(address + 2, two);
  EEPROM.update(address + 3, one);
}

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void EEPROMWriteWord(word address, word value)
{
  //Decomposition from a long to 2 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte four = value;
  byte three = value >> 8;
  
  //Write the 2 bytes into the eeprom memory.
  EEPROM.update(address, four);
  EEPROM.update(address + 1, three);
}
#endif

long EEPROMReadLong(word address)
{
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  
  //Return the recomposed long by using bitshift.
  return (four) + (three << 8) + (two << 16) + (one << 24);
}

word EEPROMReadWord(word address)
{
  //Read the 2 bytes from the eeprom memory.
  word four = EEPROM.read(address);
  word three = EEPROM.read(address + 1);
  
  //Return the recomposed long by using bitshift.
  return four + (three << 8);
}

void set_background(word eeprom_address,uint32_t fill_color)
{
  for(byte led=0;led<LED_COUNT;led++)
  {
    if(eeprom_address==EEPROM_ADDRESS_BACKGROUND_BLACK)
      strip.setPixelColor(led,fill_color);
    else{
      strip.setPixelColor(led,EEPROMReadLong(eeprom_address));
      eeprom_address+=sizeof(uint32_t);
    }
  }
}
