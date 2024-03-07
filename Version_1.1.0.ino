//Project Week 3 Code
//Written by RB2521
//For any queries or further information, please visit the github repository at 
//or email me at rb2521@bath.ac.uk and I will reply as quickly as possible!

//The following code is for use in the University of Bath, Dept. EEE, Year 1 project week 3: Mechatronics escpae room
//Please see the read.me file on the git hub repo for a full list of components needed to run this code
//This code is in mind for the Arduino Nano ESP32. Bigger boards will have more 

const int shakeSensInterruptPin = 11; //Shake sensor interrupt pin at D11
const int buzzer = 10; //Buzzer connected at D10

volatile bool interruptFlag = false; //Interrupt flag to detect when a shake happens
unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 1000;

//Simons Says style game variables
const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL];
int player_sequence[MAX_LEVEL];
int level = 1;
int velocity = 500;



void setup() {
  Serial.begin(9600);
  pinMode(shakeSensInterruptPin, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(shakeSensInterruptPin), handleInterrupt, RISING);

  pinMode(A7, INPUT);
  pinMode(A6, INPUT);
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);
  pinMode(A0, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void loop() {
  if (interruptFlag && level == 1) {
    interruptFlag = false;
    generate_sequence();
  }
  if (digitalRead(A0) == LOW || level != 1) {
        show_sequence();
        get_sequence();
  }
}

void show_sequence() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  for (int i = 0; i < level; i++) {
    digitalWrite(sequence[i], HIGH);
    delay(velocity);
    digitalWrite(sequence[i], LOW);
    delay(200);
  }
}

void get_sequence(){
  int seqFlag = 0;

  for (int i = 0; i < level; i++) {
    seqFlag = 0;
    while (seqFlag == 0) {
      if (digitalRead(A7) == LOW) {
        digitalWrite(2, HIGH);
        player_sequence[i] = 2;
        seqFlag = 1;
        delay(200);
        if (player_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(2, LOW);
      }
      if (digitalRead(A6) == LOW) {
        digitalWrite(4, HIGH);
        player_sequence[i] = 4;
        seqFlag = 1;
        delay(200);
        if (player_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(4, LOW);
      }
      if (digitalRead(A5) == LOW) {
        digitalWrite(3, HIGH);
        player_sequence[i] = 3;
        seqFlag = 1;
        delay(200);
        if (player_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(3, LOW);
      }
      if (digitalRead(A4) == LOW) {
        digitalWrite(5, HIGH);
        player_sequence[i] = 5;
        seqFlag = 1;
        delay(200);
        if (player_sequence[i] != sequence[i]) {
          wrong_sequence();
          return;
        }
        digitalWrite(5, LOW);
      }
    }
  }
  right_sequence();
}

void generate_sequence() {
  randomSeed(millis()); //"True" randomness

  for (int i = 0; i < MAX_LEVEL; i++) {
    sequence[i] = random(2, 6);
  }
}

void wrong_sequence() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    delay(250);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);

  }
  level = 1;
  velocity = 500;
}

void right_sequence() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(250);

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  delay(500);

  if (level < MAX_LEVEL) {
    level++;
    velocity -= 50;
  }
}



void handleInterrupt() {
  interruptFlag = true;
}



