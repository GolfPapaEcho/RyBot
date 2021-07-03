// SeveralThingsAtTheSameTime.ino

// An expansion of the BlinkWithoutDelay concept to illustrate how a script
//  can appear to do several things at the same time

// this sketch does the following
//    it blinks the onboard LED (as in the blinkWithoutDelay sketch)
//    it blinks two external LEDs (LedA and LedB) that are connected to pins 12 and 11.
//    it turns another Led (buttonLed connected to pin 10) on or off whenever a button
//       connected to pin 7 is pressed
//    it sweeps a servo (connected to pin 5) back and forth at different speeds


//  One leg of each LED should be connected to the relevant pin and the other leg should be connected to a
//   resistor of 470 ohms or more and the other end of the resistor to the Arduino GND. 
//   If the LED doesn't light its probably connected the wrong way round.

//  On my Uno and Mega the "button" is just a piece of wire inserted into pin 7. 
//   Touching the end of the wire with a moist finger is sufficient to cause the switching action
//   Of course a proper press-on-release-off button switch could also be used!

//  The Arduino is not capable of supplying enough 5v power to operate a servo
//    The servo should have it's own power supply and the power supply Ground should
//      be connected to the Arduino Ground.

// The sketch is written to illustrate a few different programming features.
//    The use of many functions with short pieces of code. 
//       Short pieces of code are much easier to follow and debug
//    The use of variables to record the state of something (e.g. onBoardLedState) as a means to
//       enable the different functions to determine what to do.
//    The use of millis() to manage the timing of activities
//    The definition of all numbers used by the program at the top of the sketch where 
//       they can easily be found if they need to be changed


//========================================

// ----------LIBRARIES--------------



// --------CONSTANTS (won't change)---------------

const int onBoardLedPin =  13;      // the pin numbers for the LEDs
const int led_RED_Pin = 12;
const int led_GREEN_Pin = 11;
const int led_BLUE_Pin = 10;
const int buttonLed_Pin = 9;
const int eyesLEDS = 8;
const int buttonPin = 7; // the pin number for the button


const int onBoardLedInterval = 500; // number of millisecs between blinks
const int led_RED_Interval = 500;
const int led_GREEN_Interval = 750;
const int led_BLUE_Interval = 100;

const int blinkDuration = 500; // number of millisecs that Led's are on - all three leds use this

const int buttonInterval = 300; // number of millisecs between button readings

//Set up Morse Code look up table 
//First int in each Morse character array is the number of elements in the array starting counting at zero.
const int a[3] = { 2, 1, 3 };
const int b[5] = { 4, 3, 1, 1, 1 };
const int c[5] = { 4, 3, 1, 3, 1 };
const int d[4] = { 3, 3, 1, 1 };
const int e[2] = { 1, 1 };
const int f[5] = { 4, 1, 1, 3, 1 };
const int g[4] = { 3, 3, 3, 1 };
const int h[5] = { 4, 1, 1, 1, 1 };
const int i[3] = { 2, 1, 1 };
const int j[5] = { 4, 1, 3, 3, 3 };
const int k[4] = { 3, 3, 1, 3 };
const int l[5] = { 4, 1, 3, 1, 1 };
const int m[3] = { 2, 3, 3 };
const int n[3] = { 2, 3, 1 };
const int o[4] = { 3, 3, 3, 3 };
const int p[5] = { 4, 1, 3, 3, 1 };
const int q[5] = { 4, 3, 3, 1, 3 };
const int r[4] = { 3, 1, 3, 1 };
const int s[4] = { 3, 1, 1, 1 };
const int t[2] = { 1, 3 };
const int u[4] = { 3, 1, 1, 3 };
const int v[5] = { 4, 1, 1, 1, 3 };
const int w[4] = { 3, 1, 3, 3 };
const int x[5] = { 4, 3, 1, 1, 3 };
const int y[5] = { 4, 3, 1, 3, 3 };
const int z[5] = { 4, 3, 3, 1, 1 };
const int space[2] = { 1, 4 };
const int one[6] = { 5, 1, 3, 3, 3, 3 };
const int two[6] = { 5, 1, 1, 3, 3, 3 };
const int three[6] = { 5, 1, 1, 1, 3, 3 };
const int four[6] = { 5, 1, 1, 1, 1, 3 };
const int five[6] = { 5, 1, 1, 1, 1, 1 };
const int six[6] = { 5, 3, 1, 1, 1, 1 };
const int seven[6] = { 5, 3, 3, 1, 1, 1 };
const int eight[6] = { 5, 3, 3, 3, 1, 1 };
const int nine[6] = { 5, 3, 3, 3, 3, 1 };
const int zero[6] = { 5, 3, 3, 3, 3, 3 };

//messages (RyBot for EYE_LEDS and buzzer)
#define MESSAGE_LENGTH 19
#define MAX_CHAR_LEN 5
int const* RyBot[MESSAGE_LENGTH] = { r, y, b, o, t, space, space, space, s, c, o, t, l, a, n, d, space, space, space }; //Eye leds gpio pin 07

int noElementsInCharacter;
int timerUnitMultiplier;


//------------ VARIABLES (will change)---------------------

byte onBoardLedState = LOW;             // used to record whether the LEDs are on or off
byte led_RED_State = LOW;           //   LOW = off
byte led_GREEN_State = LOW;
byte led_BLUE_State = LOW;
byte buttonLed_State = LOW;


unsigned long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
unsigned long previousOnBoardLedMillis = 0;   // will store last time the LED was updated
unsigned long previousLed_RED_Millis = 0;
unsigned long previousLed_GREEN_Millis = 0;
unsigned long previousLed_BLUE_Millis = 0;

unsigned long previousButtonMillis = 0; // time when button press last checked

// For message play back
unsigned short msgTiming[MESSAGE_LENGTH][2*MAX_CHAR_LEN];    // to get filled with the on off timing
unsigned int msgCurrentChar = 0;  // which char in the message we are up to
unsigned long msgStartMillis = 0; // ms start time (for getting offset)
bool msgPlaying = true;          // should we be playing the message?
unsigned long msgDitMillis = 333; // Number of ms to represent a dit (dot) - the base of the morse time
bool isMorseLedOn = false;  // the state of the morse LED


void buildMessageRyBot() {  
    //r[4] = { 3, 1, 3, 1 };
    //message[0] = 0
    //on  = 0     = now
    //now = now + R[1]
    //off = 1     = now
    //now = now + 1
    //on  = 2 waiting for a di = now
    //now = now + R[2]
    //off = 5 = now
    //on  = 6 = now = now + 1
    //off = 7 = now = now + R[3]
    //if i > noElementsInCharacter
    //message[characterInMessage][i] = 0;
    //how it works
    //

  int characterInMessage = 0; //array counting starts at zero
  unsigned short now = 1;
  for (characterInMessage; characterInMessage < MESSAGE_LENGTH; // array element are numbered from zero
      characterInMessage++) {

    int noElementsInCharacter = RyBot[characterInMessage][0];
    if (RyBot[characterInMessage] == space) {
      /* Turn LED Off by setting the GPIO pin low  */
      
      for(int i = 0; i < 2*MAX_CHAR_LEN; i++){
        msgTiming[characterInMessage][i] = 0;
      }
      now = now + space[1];
    } else {
      for (int i = 1; i <= MAX_CHAR_LEN; i++) {
        int on = 0;
        int off = 0;
        if (i <= noElementsInCharacter) {
          on = now;
          now = now + RyBot[characterInMessage][i];
          off = now;
          now = now + 1; // Adding the space between dots and dashes
        }

       msgTiming[characterInMessage][2*(i-1)] = on;
       msgTiming[characterInMessage][2*(i-1)+1] = off;
      }
    }
    now = now + 3; //new character delay
  }

}

void debug_print_message(void) {
    Serial.print("c,i,onTime,offTime\n");
    for(int c = msgCurrentChar; c < MESSAGE_LENGTH; c++) {
        for(int i = 0; i < MAX_CHAR_LEN; i++) {
            unsigned short onTime = msgTiming[msgCurrentChar][i*2];
            unsigned short offTime = msgTiming[msgCurrentChar][i*2+1];
            Serial.print(c);
            Serial.print(i);
            Serial.print(onTime);
            Serial.print(offTime);
            Serial.println("\n");
        }
    }
}

//========================================

void setup() {

  
      // set the Led pins as output:
  pinMode(onBoardLedPin, OUTPUT);
  pinMode(led_RED_Pin, OUTPUT);
  pinMode(led_GREEN_Pin, OUTPUT);
  pinMode(led_BLUE_Pin, OUTPUT);
  pinMode(buttonLed_Pin, OUTPUT);
  
      // set the button pin as input with a pullup resistor to ensure it defaults to HIGH
  pinMode(buttonPin, INPUT_PULLUP);

  // Build the message
  buildMessageRyBot();
  debug_print_message();
 
 
}

//========================================

void loop() {

      // Notice that none of the action happens in loop() apart from reading millis()
      //   it just calls the functions that have the action code

  currentMillis = millis();   // capture the latest value of millis()
                              //   this is equivalent to noting the time from a clock
                              //   use the same time for all LED flashes to keep them synchronized
  
 readButton();               // call the functions that do the work
  //my circuit uses positive logic

  updateMorseMessage();
  updateOnBoardLedState();

  updateLed_RED_State();
  updateLed_GREEN_State();
  updateLed_BLUE_State();
  switchLeds();
 

}

//========================================

void updateOnBoardLedState() {
  if (onBoardLedState == LOW) {
          // if the Led is off, we must wait for the interval to expire before turning it on
    if (currentMillis - previousOnBoardLedMillis >= onBoardLedInterval) {
          // time is up, so change the state to HIGH
       onBoardLedState = HIGH;
          // and save the time when we made the change
       previousOnBoardLedMillis += onBoardLedInterval;
          // NOTE: The previous line could alternatively be
          //              previousOnBoardLedMillis = currentMillis
          //        which is the style used in the BlinkWithoutDelay example sketch
          //        Adding on the interval is a better way to ensure that succesive periods are identical

    }
  }
  else {  // i.e. if onBoardLedState is HIGH
  
          // if the Led is on, we must wait for the duration to expire before turning it off
    if (currentMillis - previousOnBoardLedMillis >= blinkDuration) {
          // time is up, so change the state to LOW
       onBoardLedState = LOW;
          // and save the time when we made the change
       previousOnBoardLedMillis += blinkDuration;
    } 
  }
}

//========================================

void updateLed_RED_State() {

  if (led_RED_State == LOW) {
    if (currentMillis - previousLed_RED_Millis >= led_RED_Interval) {
       led_RED_State = HIGH;
       previousLed_RED_Millis += led_RED_Interval;
    }
  }
  else {
    if (currentMillis - previousLed_RED_Millis >= blinkDuration) {
       led_RED_State = LOW;
       previousLed_RED_Millis += blinkDuration;
    } 
  }    
}

//========================================

void updateLed_GREEN_State() {

  if (led_GREEN_State == LOW) {
    if (currentMillis - previousLed_GREEN_Millis >= led_GREEN_Interval) {
       led_GREEN_State = HIGH;
       previousLed_GREEN_Millis += led_GREEN_Interval;
    }
  }
  else {
    if (currentMillis - previousLed_GREEN_Millis >= blinkDuration) {
       led_GREEN_State = LOW;
       previousLed_GREEN_Millis += blinkDuration;
    }
  }    
}

//========================================

void updateLed_BLUE_State() {

  if (led_BLUE_State == LOW) {
    if (currentMillis - previousLed_BLUE_Millis >= led_BLUE_Interval) {
       led_BLUE_State = HIGH;
       previousLed_BLUE_Millis += led_BLUE_Interval;
    }
  }
  else {
    if (currentMillis - previousLed_BLUE_Millis >= blinkDuration) {
       led_BLUE_State = LOW;
       previousLed_BLUE_Millis += blinkDuration;
    } 
  }    
}


//========================================

void switchLeds() {
      // this is the code that actually switches the LEDs on and off

  digitalWrite(onBoardLedPin, onBoardLedState);
  digitalWrite(led_RED_Pin, led_RED_State);
  digitalWrite(led_GREEN_Pin, led_GREEN_State);
  digitalWrite(led_BLUE_Pin, led_BLUE_State);
  digitalWrite(buttonLed_Pin, buttonLed_State);
}

//========================================

void readButton() {

      // this only reads the button state after the button interval has elapsed
      //  this avoids multiple flashes if the button bounces
      // every time the button is pressed it changes buttonLed_State causing the Led to go on or off
      // Notice that there is no need to synchronize this use of millis() with the flashing Leds
  
  if (millis() - previousButtonMillis >= buttonInterval) {

    if (digitalRead(buttonPin) == LOW) {
      buttonLed_State = ! buttonLed_State; // this changes it to LOW if it was HIGH 
                                           //   and to HIGH if it was LOW
      previousButtonMillis += buttonInterval;
    }
  }

}
//========================================  

// For message play back
// unsigned short msgTiming[][];    // to get filled with the on off timing
// unsigned int msgCurrentChar = 0;  // which char in the message we are up to
// unsigned long msgStartMillis = 0; // ms start time (for getting offset)
// bool msgPlaying = true;          // should we be playing the message?
// unsigned long msgDitMillis = 100; // Number of ms to represent a dit (dot) - the base of the morse time


void updateMorseMessage() {
    if(!msgPlaying) {
        // turn off morse LED
        digitalWrite(eyesLEDS, LOW);
        // then return
        return;

    }
    if(msgStartMillis > currentMillis){
        return;
    }
    unsigned long now = currentMillis - msgStartMillis; // now in ms since last char started
    //if(currentMillis){}
    //if(now/1000 <  1){
    //  digitalWrite(eyesLEDS, HIGH);
    //  return;
    //}
    //if(now/1000 < 2){
    //  digitalWrite(eyesLEDS, LOW);
    //  return;
    //}
    // see where we should be in the on-off cycle
    for(int c = msgCurrentChar; c < MESSAGE_LENGTH; c++) {
        for(int i = 0; i < MAX_CHAR_LEN; i++) {
            unsigned short onTime = msgTiming[msgCurrentChar][i*2];
            unsigned short offTime = msgTiming[msgCurrentChar][i*2+1];
            if(now > onTime*msgDitMillis) {
                isMorseLedOn = true;
            } else {
                msgCurrentChar = c;
                digitalWrite(eyesLEDS, isMorseLedOn);// setMorseLed(isMorseLedOn)
                return;
            }
            if(now > offTime*msgDitMillis) {
                isMorseLedOn = false;
            } else {
                msgCurrentChar = c;
                digitalWrite(eyesLEDS, isMorseLedOn);// setMorseLed(isMorseLedOn)
                return;
            }
        }
    }

    // if we completed the loop without returning then it means
    // that we now was never less than the current message time
    // so we have finished the message

    isMorseLedOn = false;
    unsigned long restart_delay_ms = 2000; // start again in two seconds
    msgStartMillis = currentMillis  + restart_delay_ms;
    msgCurrentChar = 0; // reset to start of message.
    digitalWrite(eyesLEDS, isMorseLedOn);// setMorseLed(isMorseLedOn) // not implented yet






}




//========================================END
