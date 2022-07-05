// Define constants, mainly for the pins.
const int buttonPin = 2;
int buttonState = 0;
int ledStates;
const int led8 = 13;
const int led7 = 12;
const int led6 = 11;
const int led5 = 10;
const int led4 = 9;
const int led3 = 8;
const int led2 = 7;
const int led1 = 6;
const int led0 = 5;
const int ledm1 = 4;
const int ledm2 = 3;
const int DELAY = 200;
const int LAST_STATE = 10;

// Define the pins and buttons, and reset which light should light up first.
void setup() {
  Serial.begin(9600);
  // I forgot these three when filming the demonstration. There was no significant difference.
  pinMode(ledm2, OUTPUT);
  pinMode(ledm1, OUTPUT);
  pinMode(led0, OUTPUT);
  // I did not forget these ones.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(buttonPin, INPUT);
  ledStates = 0;
}

// This was called many times.
// This function takes in an LED to turn off, and the next LED to turn on. It prints a bunch of debug text, and increments the ledStates variable,
// giving permission for the next light to be passed through this function.
int configLights(int ledoff, int ledon) {
  Serial.print("State ");
  Serial.print(ledStates);
  Serial.print("\n");
  digitalWrite(ledoff, LOW);
  digitalWrite(ledon, HIGH);
  delay(DELAY);
  
  
  Serial.print("LED ");
  Serial.print(ledon);
  Serial.print(" on\n");
  Serial.print("LED ");
  Serial.print(ledoff);
  Serial.print(" off\n");
  
  return ++ledStates;
}
// The function only runs if the button is held. I needed a lot of if statements because the lights would all light up on their own, otherwise.
void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    if(!ledStates)
      ledStates = configLights(ledm2, led8);
    if(ledStates == 1)
      ledStates = configLights(led8, led7);
    if(ledStates == 2)
      ledStates = configLights(led7, led6);
    if(ledStates == 3)
      ledStates = configLights(led6, led5);
    if(ledStates == 4)
      ledStates = configLights(led5, led4);  
    if(ledStates == 5)
      ledStates = configLights(led4, led3);
    if(ledStates == 6)
      ledStates = configLights(led3, led2); 
    if(ledStates == 7)
      ledStates = configLights(led2, led1);
    if(ledStates == 8)
      ledStates = configLights(led1, led0);
    if(ledStates == 9)
      ledStates = configLights(led0, ledm1);
    if(ledStates == 10)
      ledStates = configLights(ledm1, ledm2);
    if(ledStates > LAST_STATE) {
      ledStates = 0;
      delay(2*DELAY);
    }
  } else {
    // turn LEDs off:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    digitalWrite(led7, LOW);
    digitalWrite(led8, LOW);
    // I missed these three.
    digitalWrite(led0, LOW);
    digitalWrite(ledm1, LOW);
    digitalWrite(ledm2, LOW);
    ledStates = 0;
  }
}
