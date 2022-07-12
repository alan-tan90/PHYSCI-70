const int A1A = 3;  // define pin 3 for A-1A (PWM Speed)
const int A1B = 4;  // define pin 4 for A-1B (direction)
const int analog_pin = A3;
const int tx_pin = 1;
int read_high;
int read_low;
int diff;
long result; // For tx rx

void setup() {
  pinMode(A1A, OUTPUT); // specify these pins as outputs
  pinMode(A1B, OUTPUT);
  pinMode(tx_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  motorA(LOW, 150);  // turn motor CW at full speed
  result = tx_rx();
  Serial.println(result);
  delay(2000);      // delay for 2 seconds
  motorA(HIGH, 100);  // turn motor CCW at quarter speed
  result = tx_rx();
  Serial.println(result);
  delay(4000);      // delay for 4 seconds 
}

/*
  This is a custom function to drive Motor A
  inputs: direction (HIGH/LOW), speed (0-255)
  outputs: motor control
 */
void motorA(byte d, int s) {
  if(d == 1){
    analogWrite(A1A, 255-s); 
    digitalWrite(A1B, HIGH); 
  } else if (d == 0){
    analogWrite(A1A, s); 
    digitalWrite(A1B, LOW);
  }
}
long tx_rx() {         // Function to execute rx_tx algorithm and return a value
                      // that depends on coupling of two electrodes.
                      // Value returned is a long integer.
  int read_high;
  int read_low;
  int diff;
  long int sum;
  int N_samples = 100;    // Number of samples to take.  Larger number slows it down, but reduces scatter.

  sum = 0;

  for (int i = 0; i < N_samples; i++){
   digitalWrite(tx_pin,HIGH);              // Step the voltage high on conductor 1.
   read_high = analogRead(analog_pin);     // Measure response of conductor 2.
   delayMicroseconds(100);                 // Delay to reach steady state.
   digitalWrite(tx_pin,LOW);               // Step the voltage to zero on conductor 1.
   read_low = analogRead(analog_pin);      // Measure response of conductor 2.
   diff = read_high - read_low;            // desired answer is the difference between high and low.
   sum += diff;                            // Sums up N_samples of these measurements.
 }
  return sum;
}            
