enum Note {Cn3, Cs3, Dn3, Ef3, En3, Fn3, Fs3, Gn3, Af3, An3, Bf3, Bn3, Cn4, Cs4, Dn4, Ef4, En4, Fn4, Fs4, Gn4, Af4, An4, Bf4, Bn4, Cn5, Cs5, Dn5, Ef5, En5, Fn5, Fs5, Gn5, Af5, An5, Bf5, Bn5, numNotes};
int buzzerPin = 10;
const double BASE = 1.05946;
const int BASE_UPTIME = 250; // Quarter of a second
const int BASE_DELAY = 50;
typedef unsigned long ulong;
// Adopted some code from this tutorial: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/using-millis-for-timing
// Using delay() would be so much more convenient!
ulong prevTime;
ulong Time;
int noteCode = 1; // 1 means a note is playing while 2 means the buzzer is waiting.
int i = 0; // Progression throughout the song

class SongNote {
public:
  Note m_pitch; // frequencies[pitch]
  int m_upTime; // How long this pitch is going to play
  int m_delayTime; // Before the next note
  SongNote(Note, int, int);
  void playNote(Note, int, int, int);
};

SongNote::SongNote(Note pitch, int upTime, int delayTime): m_pitch(pitch), m_upTime(upTime), m_delayTime(delayTime) {
  // Nothing needs to happen here.
}

int Delay(ulong Time, ulong prevTime, int interval) {
  // Code parameter: 1 for playing note, 2 for delaying 'till next note is queued
  
  
  Serial.println("Interval: ");
  Serial.println(interval);
  
  if(Time - prevTime >= interval) {
    prevTime = Time;
    return noteCode = 1;
  } else {
    return 2;
  }
}

int newDelay(ulong Time, ulong &prevTime, int interval) {
  // Debug
  ulong timeDiff = Time - prevTime;
  
  Serial.println("Time difference: ");
  Serial.println(timeDiff);
  if(timeDiff >= interval) {
    prevTime = Time;
    Serial.println("Pr Time: ");
  Serial.println(prevTime);
    i++;
    return 1;
  } else {
    return 2;
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
    tone(pin, frequencies[m_pitch], m_upTime);
    noteCode = 2;
  }
}


SongNote megalovania[4] = {SongNote(Dn3, 500, 800), SongNote(Dn3, 500, 800), SongNote(Dn4, 500, 800), SongNote(An3, 500, 1000)};
void setup() {
  Time = 0;
  prevTime = 0;
  Serial.begin(9600);
  
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  Time = millis();
  SongNote sn = megalovania[i];
  sn.playNote(sn.m_pitch, sn.m_upTime, sn.m_delayTime, buzzerPin);
  noteCode = newDelay(Time, prevTime, sn.m_delayTime);
  
  
  
  if (i == 4) {
    newDelay(Time, prevTime, 4000);
    i = 0;
  }
}

