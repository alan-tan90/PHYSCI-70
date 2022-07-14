enum Note {Cn3, Cs3, Dn3, Ef3, En3, Fn3, Fs3, Gn3, Af3, An3, Bf3, Bn3, Cn4, Cs4, Dn4, Ef4, En4, Fn4, Fs4, Gn4, Af4, An4};
int buzzerPin = 10;
const double BASE = 1.05946;

int* generateFrequencies() {
  static int frequencies[22] {};
  // A4 is the starting note
  for(int i = 0; i < 22; i++) {
    frequencies[i] = static_cast<int>(440 * pow(BASE, i - 21));
  }
  return frequencies;
}
int* frequencies = generateFrequencies();

void setup() {
  Serial.begin(9600);
  // Test
  for(int i = 0; i < 22; i++) {
    Serial.println(frequencies[i]);
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
    tone(buzzerPin, frequencies[An4], 500);
    delay(1000);
    tone(buzzerPin, 1000, 500);
    delay(1000);
}

