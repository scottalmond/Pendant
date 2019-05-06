//Based on "Tiny Synth" code from: http://www.technoblogy.com/show?Q7H

#if BURN_EEPROM==0
const int Scale[] = { 
0,13717,14532,15397,16312,17282,0,18310,19398,20552,21774,23069,24440,25894,0};

const int Silence = 0;
//const int Error = 0;  // Error LED on PB0

// Note buffer
volatile unsigned int Acc[] = {Silence, Silence, Silence, Silence};
volatile unsigned int Freqs[] = {0, 0, 0, 0 };

//Globals persist throughout tune
unsigned int NextTick = 0;
int TunePtr = 0;
int Octave = 0, LastIndex = 0, Duration = 4;

// Global tick counter
volatile unsigned int GlobalTicks = 0;

bool is_boost=false;//flag to double digital volume of sound ouput to speaker

// Ticks timer
unsigned int Ticks() {
  unsigned long t;
  uint8_t oldSREG = SREG;
  cli();
  t = GlobalTicks;
  SREG = oldSREG;
  return t;
}

// Watchdog interrupt counts ticks (1/8 sec)
ISR(WDT_vect) {
  WDTCR |= 1<<WDIE;
  GlobalTicks++;
  if(is_button_down())
  {
    sound_press_count++;
    if(sound_press_count>=SOUND_PRESS_COUNT_ROOT)
    {
      sound_press_count=0;
      sound_state=GO_TO_ROOT;
    }
  }else{
    if(sound_press_count>=SOUND_PRESS_COUNT_CHAPTER)
    {
      sound_press_count=0;
      sound_state=GO_TO_NEXT_CHAPTER;
    }else if(sound_press_count>0) sound_press_count=0;//debounce
  }
}

// Generate triangle waves on 4 channels
ISR(TIMER0_COMPA_vect) {
  int8_t Mask, Temp, Sum=0;
  for (int c=0; c<4; c++) {
    Acc[c] = Acc[c] + Freqs[c];
    Temp = Acc[c] >> 8;
    Mask = Temp >> 15;
    Sum = Sum + ((char)(Temp ^ Mask) >> 1);
  }
  if(is_boost) Sum=Sum*2;
  OCR1B = Sum;
}

// Setup
void begin_sound() {
  // Enable 64 MHz PLL and use as source for Timer1
  PLLCSR = 1<<PCKE | 1<<PLLE;     

  // Set up Timer/Counter1 for PWM output
  TIMSK = 0;                     // Timer interrupts OFF
  TCCR1 = 1<<CS10;               // 1:1 prescale
  GTCCR = 1<<PWM1B | 2<<COM1B0;  // PWM B, clear on match

  OCR1B = 128;
  pinMode(4, OUTPUT);            // Enable PWM output pin

  // Set up Timer/Counter0 for 20kHz interrupt to output samples.
  TCCR0A = 3<<WGM00;             // Fast PWM
  TCCR0B = 1<<WGM02 | 2<<CS00;   // 1/8 prescale
  OCR0A = 49;                    // Divide by 400
  TIMSK = 1<<OCIE0A;             // Enable compare match, disable overflow
 
  // Set up Watchdog timer for 8 Hz interrupt for ticks timer.
  WDTCR = 1<<WDIE | 3<<WDP0;     // 8 Hz interrupt
  enable_amplifier(true);
  is_sound_enabled=true;
}

void stop_sound(){//emperically derived by observing the settings on the registers between when sound was played and when it was not
  enable_amplifier(false);
  WDTCR=0x00;
  PLLCSR=0x03;
  TIMSK=0x02;
  TCCR1=0x03;
  GTCCR=0x40;
  TCCR0B=0x03;
  OCR0A=0x00;
  is_sound_enabled=false;
  for(byte voice=0;voice<4;voice++)
  {
    Acc[voice]=Silence;
    Freqs[voice]=0;
  }
}

//dedicated amplifier chip has an !IS_SHUTDOWN pin to minimize power usage when not in use
//  note: this chip !SHUTDOWN pin naturally drifts to GND if not specifically driven
void enable_amplifier(bool is_enabled){ digitalWrite(PIN_AMPLIFIER,is_enabled); }

//disable timing interrupts from sound to allow other operations like setting LED state which requries precise timing
void pause_sound(bool is_pause){ TIMSK=is_pause?0x02:0x10; }

//re-initialize registers to orignal settings
void restart_sound(byte eeprom_address_start,bool boost_input)
{
  //Globals persist throughout tune
  NextTick = 0;
  TunePtr = eeprom_address_start;
  Octave = 0;
  LastIndex = 0;
  Duration = 4;
  
  // Global tick counter
  GlobalTicks = 0;
  is_boost=boost_input;
}

// Main loop - Parse Ample tune notation
//return true on end of song
bool playTone() {
  int8_t Sign = 0, Number = 0, Chan = 0, SaveIndex = 0, SaveOctave = 0;
  char Symbol;
  boolean More = 1, ReadNote = 0, Bra = 0, SetOctave = 0;
  do {
    //do { // Skip formatting characters
      //Symbol = pgm_read_byte(&Tune[TunePtr++]);
      Symbol = EEPROM.read(TunePtr++);
    //} while ((Symbol == ' ') || (Symbol == '|'));
    int CapSymbol = Symbol & 0x5F;
    if (Symbol == '(') { Bra = 1; SaveIndex = LastIndex; SaveOctave = Octave; }
    else if (ReadNote && !Bra) More = 0;
    else if (Symbol == ')') { Bra = 0; LastIndex = SaveIndex; Octave = SaveOctave; }
    else if (Symbol == 0){ return true; }          // End of string - stop
    else if (Symbol == ',') { Duration = Number; Number = 0; Sign = 0; }
    else if (Symbol == ':') {
      SetOctave = 1; Octave = Number;
      if (Sign == -1) Octave = -Octave;
      Number = 0; Sign = 0;
    }
    else if ((Symbol >= '0') && (Symbol <= '9')) Number = Number*10 + Symbol - '0';
    //else if (Symbol == '<') Octave--;
    //else if (Symbol == '>') Octave++;
    else if (Symbol == '-') Sign = -1;
    //else if (Symbol == '+') Sign = 1;
    else if (Symbol == '/') ReadNote = 1;
    else if (Symbol == '^') { Acc[Chan] = Silence; Freqs[Chan++] = 0; ReadNote = 1; }
    else if ((CapSymbol >= 'A') && (CapSymbol <= 'G')) {
      boolean Lowercase = (Symbol & 0x20);
      int Index = (((CapSymbol - 'A' + 5) % 7) << 1) + 1 + Sign;
      if (!SetOctave) {
        if (LastIndex && (Index < LastIndex) && !Lowercase) Octave++;
        if (LastIndex && (Index > LastIndex) && Lowercase) Octave--;
      } else SetOctave = 0;
      Freqs[Chan++] = Scale[Index] >> (4 - Octave);
      LastIndex = Index;
      ReadNote = 1; Sign = 0;
    }// else digitalWrite(Error, 1);  // Illegal character
  } while (More);
  TunePtr--;
  NextTick = NextTick + Duration;
  while (Ticks() < NextTick);
  return false;
}
#endif
