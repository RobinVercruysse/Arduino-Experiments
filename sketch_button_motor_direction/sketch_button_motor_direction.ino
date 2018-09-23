const int buttonPin = 2;    // the number of the pushbutton pin
const int motorSpeedPin = 3;
const int brakePin = 9;    // the number of the Brake Channel A pin
const int motorDirectionPin = 12;   // the number of the Motor Channel A pin
const int ledPin = 13;      // the number of the LED pin

int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  //Setup Channel A motor pins
  pinMode(brakePin, OUTPUT);
  pinMode(motorDirectionPin, OUTPUT);

  //Setup button input
  pinMode(buttonPin, INPUT);

  //Setup LED output
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        brake();
        delay(1000);
        startMotor(ledState, 255);
      }
    }
  }

  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

void brake() {
  digitalWrite(brakePin, HIGH);
}

void startMotor(boolean forwards, int speed) {
  digitalWrite(motorDirectionPin, forwards ? HIGH : LOW);
  analogWrite(motorSpeedPin, speed);
}
