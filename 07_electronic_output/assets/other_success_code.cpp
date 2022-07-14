enum Note {Cn3, Cs3, Dn3, Ef3, En3, Fn3, Fs3, Gn3, Af3, An3, Bf3, Bn3, Cn4, Cs4, Dn4, Ef4, En4, Fn4, Fs4, Gn4, Af4, An4, Bf4, Bn4, Cn5, Cs5, Dn5, Ef5, En5, Fn5, Fs5, Gn5, Af5, An5, Bf5, Bn5, numNotes};
int buzzerPin = 10;
const double BASE = 1.05946;
const int BASE_UPTIME = 250; // Quarter of a second
const int BASE_DELAY = 50;
typedef unsigned long ulong;
// Adopted some code from this tutorial: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/using-millis-for-timing
// Using delay() would be so much more convenient!
ulong prevTime = 0;
ulong interval = 1000;
ulong Time;
int noteCode = 2; // 1 means a note is playing while 2 means the buzzer is waiting.

class SongNote {
public:
  Note m_pitch; // frequencies[pitch]
  int m_upTime; // How long this pitch is going to play
  int m_delayTime; // Before the next note
  SongNote(Note, int, int);
  void playNote(Note, int, int, int);
};

SongNote::SongNote(Note pitch, int upTime, int delayTime): m_pitch(pitch), m_upTime(upTime=BASE_UPTIME), m_delayTime(delayTime=BASE_DELAY) {
  // Nothing needs to happen here.
}

int Delay(ulong Time, ulong prevTime, int interval) {
  // Code parameter: 1 for playing note, 2 for delaying 'till next note is queued
  // Interval can be upTime OR delayTime.
  if(Time - prevTime >= interval) {
    prevTime = Time;
    return noteCode = 2; // OK to stop playing
  } else if(Time - prevTime >= interval) {
    prevTime = Time;
    return noteCode = 1; // OK to play note
  }
}

int* generateFrequencies() {
  static int frequencies[numNotes] {};
  // A4 is the starting note
  for(int i = 0; i < numNotes; i++) {
    frequencies[i] = static_cast<int>(440 * pow(BASE, i - 21));
  }
  return frequencies;
}
int* frequencies = generateFrequencies();

void SongNote::playNote(Note m_pitch, int m_upTime, int m_delayTime, int pin) {
  Serial.println("playNote note code: ");
  Serial.println(noteCode);
  if(noteCode == 1) {
    // Debug
    Serial.println("Frequency passed in: ");
    Serial.println(m_pitch);
    tone(pin, frequencies[m_pitch], m_upTime);
  }
  // Delay func
  noteCode = Delay(Time, prevTime, m_upTime + m_delayTime);
}

void playMegalovania(int pin) {
  
}

void setup() {
  Time = 0;
  Serial.begin(9600);
  // Test
  for(int i = 0; i < 22; i++) {
    Serial.println(frequencies[i]);
  }
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
    Time = millis();
    Serial.println(noteCode);
    SongNote songnote1[2] = {SongNote(Bn4, 3000, 100), SongNote(Bf4, 200, 1000)};
    for(SongNote sn : songnote1) {
      noteCode = 1;
      sn.playNote(sn.m_pitch, sn.m_upTime, sn.m_delayTime, buzzerPin);
    }
    // Test
    //delay(5000);
}

