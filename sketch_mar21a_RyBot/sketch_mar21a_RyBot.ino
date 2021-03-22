const int paintBrushSwitch = 7;
const int eyesLEDS = 8;
const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;
int wait = 250;
int ledState = HIGH;
int switchState;
int lastSwitchState = LOW;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//Set up Morse Code look up table (My first jagged arrays!)
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

//messages (RyBot for EYE_LEDS and buzzer and uncle for HAND_LED and buzzer)
int const* RyBot[19] = { r, y, b, o, t, space, space, space, s, c, o, t, l, a, n, d, space, space, space }; //Eye leds gpio pin 07

int noElementsInCharacter;
int timerUnitMultiplier;


void sendMessageRyBot() {

  int characterInMessage = 0; //array counting starts at zero
  int noCharactersInMessage = 19;  //Set for RyBot message array (this has 10 characters)
  for (characterInMessage; characterInMessage < noCharactersInMessage; // array element are numbered from zero
      characterInMessage++) {

    int noElementsInCharacter = RyBot[characterInMessage][0];
    if (RyBot[characterInMessage] == space) {
      /* Turn LED Off by setting the GPIO pin low  */
      digitalWrite(eyesLEDS, LOW);
      delay(space[1] * 100);
    } else {
      int i = 1; //first di or dah is at array[1] position
      for (i; i <= noElementsInCharacter; i++) {
        timerUnitMultiplier = RyBot[characterInMessage][i];
        /* Turn LED On by setting the GPIO pin high*/
        digitalWrite(eyesLEDS, HIGH);
        delay((timerUnitMultiplier * 100));
        /* Turn LED Off by setting the GPIO pin low */
        digitalWrite(eyesLEDS, LOW);
        delay(100);
      }
    }
    delay(300); //new character delay
  }

}


void setup() {
  // put your setup code here, to run once:
  pinMode(paintBrushSwitch, INPUT_PULLUP);
  pinMode(eyesLEDS, OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
}

void loop() {

//my circuit uses positive logic
sendMessageRyBot();
  
  // put your main code here, to run repeatedly:
  // read the state of the switch into a local variable:
  int reading = digitalRead(paintBrushSwitch);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastSwitchState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != switchState) {
      switchState = reading;
      ledState = reading;
       
       // only toggle the LED if the new button state is HIGH      
       //if (switchState == HIGH) {
        //ledState = !ledState;
      //}
    }
  }

  while((ledState)==LOW){
  digitalWrite(blueLED,LOW);
  digitalWrite(redLED,HIGH);
  delay(wait);
  digitalWrite(redLED,LOW);
  digitalWrite(greenLED,HIGH);
  delay(wait);
  digitalWrite(greenLED,LOW);
  digitalWrite(blueLED,HIGH);
  delay(wait);
  wait = wait - 10;
  if(wait < 0) {
    wait = 250;
    break;}

      // save the reading. Next time through the loop, it'll be the lastswitchState:
  lastSwitchState = reading;
  }}
