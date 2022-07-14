// Enums
enum Note {Bf2, Bn2, Cn3, Cs3, Dn3, Ef3, En3, Fn3, Fs3, Gn3, Af3, An3, Bf3, Bn3, Cn4, Cs4, Dn4, Ef4, En4, Fn4, Fs4, Gn4, Af4, An4, Bf4, Bn4, Cn5, Cs5, Dn5, Ef5, En5, Fn5, Fs5, Gn5, Af5, An5, Bf5, Bn5, numNotes};

// Constants
const int buzzerPin = 10;
const double BASE = 1.05946;
const int BASE_UPTIME = 150; 
const int BASE_DELAY = 50;
const int NUM_NOTES = 41;

// Type defs
typedef unsigned long ulong;

// Adopted some code from this tutorial: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/using-millis-for-timing
// Using delay() would be so much more convenient!
ulong prevTime;
ulong Time;
int noteCode = 1; // 1 means a note is playing while 2 means the buzzer is waiting.
int i = 0; // Progression throughout the song


// Classes
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

struct Button {
  int m_pin;
  int m_state;
  int m_pState;
  int m_toggled;
  Button(int, int, int, int);
  void update(int&, int&, int&);
};

Button::Button(int pin, int state, int prevState, int toggled): m_pin(pin), m_state(state), m_pState(prevState), m_toggled(toggled) {
  // Nothing needs to happen here.
}

void Button::update(int &m_pState, int &m_state, int &m_toggled) {
  // Press button TOGGLES m_pState.
  m_state = digitalRead(m_pin);
  if(m_state == HIGH) {
    m_toggled = 1;
  }
  if(m_state == LOW && m_toggled == 1) {
    m_toggled = 2;
    if(m_pState == LOW)
      m_pState = HIGH;
    else
      m_pState = LOW;
  }
  /*
  if(m_toggled == 2 && m_pState == HIGH) {
    m_toggled = 0;
    m_pState = LOW;
  }
  */
}

// Defining Buttons
Button playBtn = Button(4, LOW, LOW, 0);
Button pauseBtn = Button(2, LOW, LOW, 0);

// Delay functions
int oldDelay(ulong Time, ulong &prevTime, int interval) {
  if(Time - prevTime >= interval) {
    prevTime = Time;
    return 1;
  }
}

int newDelay(ulong Time, ulong &prevTime, int interval) {
  if(noteCode != 3) {
    ulong timeDiff = Time - prevTime;
    
    //Serial.println("Time difference: ");
    //Serial.println(timeDiff);
    if(timeDiff >= interval) {
      prevTime = Time;
      //Serial.println("Pr Time: ");
      //Serial.println(prevTime);
      i++;
      return 1;
    } else {
      return 2;
    }
  }
}

// Frequency of notes
int* generateFrequencies() {
  static int frequencies[numNotes] {};
  // A4 is the starting note.
  for(int i = 0; i < numNotes; i++) {
    frequencies[i] = static_cast<int>(440 * pow(BASE, i - An4));
  }
  // For the last note of the song
  frequencies[numNotes] = 1;
  return frequencies;
}
int* frequencies = generateFrequencies();

// Play Note Function
void SongNote::playNote(Note m_pitch, int m_upTime, int m_delayTime, int pin) {
 
  if(noteCode == 1) {
    tone(pin, frequencies[m_pitch], m_upTime);
    noteCode = 2;
  }
}

// Specify the song
// First 10 notes: SongNote megalovania[NUM_NOTES] = {SongNote(Dn3, BASE_UPTIME, 50), SongNote(Dn3, BASE_UPTIME, 200), SongNote(Dn4, BASE_UPTIME, 400), SongNote(An3, BASE_UPTIME, 550), SongNote(Af3, BASE_UPTIME, 400), SongNote(Gn3, BASE_UPTIME, 400), SongNote(Fn3, BASE_UPTIME, 400), SongNote(Dn3, BASE_UPTIME, 200), SongNote(Fn3, BASE_UPTIME, 200), SongNote(Gn3, BASE_UPTIME, 200), SongNote(numNotes, 1, 2000)};
SongNote megalovania[NUM_NOTES] = {SongNote(Dn3, BASE_UPTIME, 50), SongNote(Dn3, BASE_UPTIME, 200), SongNote(Dn4, BASE_UPTIME, 400), SongNote(An3, BASE_UPTIME, 550), SongNote(Af3, BASE_UPTIME, 400), SongNote(Gn3, BASE_UPTIME, 400), SongNote(Fn3, BASE_UPTIME, 400), SongNote(Dn3, BASE_UPTIME, 200), SongNote(Fn3, BASE_UPTIME, 200), SongNote(Gn3, BASE_UPTIME, 200), 
                                  SongNote(Cn3, BASE_UPTIME, 200), SongNote(Cn3, BASE_UPTIME, 200), SongNote(Dn4, BASE_UPTIME, 400), SongNote(An3, BASE_UPTIME, 550), SongNote(Af3, BASE_UPTIME, 400), SongNote(Gn3, BASE_UPTIME, 400), SongNote(Fn3, BASE_UPTIME, 400), SongNote(Dn3, BASE_UPTIME, 200), SongNote(Fn3, BASE_UPTIME, 200), SongNote(Gn3, BASE_UPTIME, 200), 
                                  SongNote(Bn2, BASE_UPTIME, 200), SongNote(Bn2, BASE_UPTIME, 200), SongNote(Dn4, BASE_UPTIME, 400), SongNote(An3, BASE_UPTIME, 550), SongNote(Af3, BASE_UPTIME, 400), SongNote(Gn3, BASE_UPTIME, 400), SongNote(Fn3, BASE_UPTIME, 400), SongNote(Dn3, BASE_UPTIME, 200), SongNote(Fn3, BASE_UPTIME, 200), SongNote(Gn3, BASE_UPTIME, 200),
                                  SongNote(Bf2, BASE_UPTIME, 200), SongNote(Bf2, BASE_UPTIME, 200), SongNote(Dn4, BASE_UPTIME, 400), SongNote(An3, BASE_UPTIME, 550), SongNote(Af3, BASE_UPTIME, 400), SongNote(Gn3, BASE_UPTIME, 400), SongNote(Fn3, BASE_UPTIME, 400), SongNote(Dn3, BASE_UPTIME, 200), SongNote(Fn3, BASE_UPTIME, 200), SongNote(Gn3, BASE_UPTIME, 200), SongNote(numNotes, 1, 2000)};

void setup() {
  Time = 0;
  prevTime = 0;
  Serial.begin(9600);
  
  pinMode(buzzerPin, OUTPUT);
  pinMode(playBtn.m_pin, INPUT);
  pinMode(pauseBtn.m_pin, INPUT);
}

void loop() {
  Time = millis();
  SongNote sn = megalovania[i];

  playBtn.update(playBtn.m_pState, playBtn.m_state, playBtn.m_toggled);
  pauseBtn.update(pauseBtn.m_pState, pauseBtn.m_state, pauseBtn.m_toggled);
  
  if(pauseBtn.m_pState == LOW) {
    sn.playNote(sn.m_pitch, sn.m_upTime, sn.m_delayTime, buzzerPin);
    noteCode = newDelay(Time, prevTime, sn.m_delayTime);
  }
  
  if(playBtn.m_pState == HIGH) {
    pauseBtn.m_pState = LOW; // Force-unstick the pause botton.
    playBtn.m_pState = LOW;
  }

  if (i == NUM_NOTES) {
    megalovania[0].m_delayTime = 150 + 50;
    i = 0;
  }
}
