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
unsigned long debounceDelay = 1000;    // the debounce time; increase if the output flickers

void setup() {
  // put your setup code here, to run once:
  pinMode(paintBrushSwitch, INPUT_PULLUP);
  pinMode(eyesLEDS, OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(blueLED,OUTPUT);
}

void loop() {
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
  if(wait < 0) wait = 250; 
  }

      // save the reading. Next time through the loop, it'll be the lastswitchState:
  lastSwitchState = reading;
}
