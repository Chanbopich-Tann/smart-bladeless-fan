#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978


// For 1st Arduino Interaction (FAN)
const int MOTOR=9;  //Motor on Digital Pin 9
const int POT=1;    //POT on Analog Pin A1
int val = 0;

// For 2nd Arduino Interaction (RGB LED)
const int BUTTON2 = 2;
const int GLED = 10;
const int BLED = 11;
const int RLED = 12;
boolean lastButton2 = LOW;
int ledMode = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 80;

// For 3rd Arduino Interaction (Music)
const int BUTTON3 = 3;
const int SPEAKER = 13;
boolean lastButton3 = LOW;
boolean isPlaying = false;
unsigned long lastMelodyTime = 0;

/// Note Array for "Jingle Bells"
int notes[] = {
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, 
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, 
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, 
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, 
  NOTE_E4, NOTE_D4, NOTE_G4, 
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, 
  NOTE_E4, NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, 
  NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, 
  NOTE_E4, NOTE_E4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_C4
};

// The Duration of each note (in ms) for "Jingle Bells"
int times[] = {
  250, 250, 500, 250, 250, 500,
  250, 250, 250, 250, 500,
  250, 250, 250, 250, 250, 250,
  250, 250, 250, 250, 250, 250,
  250, 250, 750,
  250, 250, 500, 250, 250, 500,
  250, 250, 250, 250, 500,
  250, 250, 250, 250, 250, 250,
  250, 250, 250, 250, 250, 250, 750
};


// LED Mode Selection
void setMode(int mode) {
  //RED
  if (mode == 1) {
    digitalWrite(RLED, HIGH);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
  //GREEN
  else if (mode == 2) {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, HIGH);
    digitalWrite(BLED, LOW);
  }
  //BLUE
  else if (mode == 3) {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, HIGH);
  }
  //PURPLE (RED+BLUE)
  else if (mode == 4) {
    analogWrite(RLED, 127);
    analogWrite(GLED, 0);
    analogWrite(BLED, 127);
  }
  //TEAL (BLUE+GREEN)
  else if (mode == 5) {
    analogWrite(RLED, 0);
    analogWrite(GLED, 127);
    analogWrite(BLED, 127);
  }
  //ORANGE (GREEN+RED)
  else if (mode == 6) {
    analogWrite(RLED, 127);
    analogWrite(GLED, 127);
    analogWrite(BLED, 0);
  }
  //WHITE (GREEN+RED+BLUE)
  else if (mode == 7) {
    analogWrite(RLED, 170);
    analogWrite(GLED, 170);
    analogWrite(BLED, 170);
  }
  //OFF (mode = 0)
  else {
    digitalWrite(RLED, LOW);
    digitalWrite(GLED, LOW);
    digitalWrite(BLED, LOW);
  }
}


void setup() {
  // For 1st Arduino Interaction (FAN)
  pinMode (MOTOR, OUTPUT);
  
  // For 2nd Arduino Interaction (RGB LED)
  pinMode(BUTTON2, INPUT);  // Set button as input
  pinMode(BLED, OUTPUT);    // Set Blue LED as Output
  pinMode(GLED, OUTPUT);    // Set Green LED as Output
  pinMode(RLED, OUTPUT);    // Set Red LED as Output

  // For 3rd Arduino Interaction (Music)
  pinMode(BUTTON3, INPUT);
  lastButton3 = LOW;

  // Check if the button is pressed during setup and start playing the melody
  boolean currentButton3 = digitalRead(BUTTON3);
  if (currentButton3 == HIGH && lastButton3 == LOW) {
    // Button is pressed
    // Start playing the melody
    for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
      tone(SPEAKER, notes[i], times[i]);
      delay(times[i]);
    }
  }
  lastButton3 = currentButton3;
}


void loop() {
  unsigned long melodyStartTime = 0;  // Declare melodyStartTime
  int melodyIndex = 0;                // Declare melodyIndex
  
  // For 1st Arduino Interaction (FAN)
  val = analogRead(POT);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(MOTOR, val);


  // For 2nd Arduino Interaction (RGB LED)
  boolean currentButton2 = debounceButton(BUTTON2, lastButton2);
  if (lastButton2 == LOW && currentButton2 == HIGH) {
    if (millis() - lastDebounceTime > debounceDelay) {
      lastDebounceTime = millis();
      ledMode = (ledMode + 1) % 8;
      setMode(ledMode);
    }
  }
  lastButton2 = currentButton2;

  // For 3rd Arduino Interaction (Music)
  boolean currentButton3 = digitalRead(BUTTON3);
  if (currentButton3 == HIGH && lastButton3 == LOW) {
    // Reset button is pressed, play the melody again
    for (int i = 0; i < sizeof(notes) / sizeof(notes[0]); i++) {
      tone(SPEAKER, notes[i], times[i]);
      delay(times[i]);
    }
  }

  lastButton3 = currentButton3;
}

boolean debounceButton(int buttonPin, boolean last) {
  boolean current = digitalRead(buttonPin);
  if (last != current) {
    delay(5);
    current = digitalRead(buttonPin);
  }
  return current;
}
