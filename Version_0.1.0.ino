//Project Week 3 Code
//Written by RB2521
//For any queries or further information, please visit the github repository at 
//or email me at rb2521@bath.ac.uk and I will reply as quickly as possible!

//The following code is for use in the University of Bath, Dept. EEE, Year 1 project week 3: Mechatronics escpae room
//Please see the read.me file on the git hub repo for a full list of components needed to run this code
//This code is in mind for the Arduino Nano ESP32. Bigger boards will have more 

const int shakeSensIndicatorLED = 12; //Indicator pin for once a shake has been detected at D12 pin
const int shakeSensInterruptPin = 11; //Shake sensor interrupt pin at D11
const int buzzer = 10; //Buzzer connected at D10

volatile bool interruptFlag = false; //Interrupt flag to detect when a shake happens


void setup() {
  Serial.begin(9600);
  pinMode(shakeSensIndicatorLED, OUTPUT);
  pinMode(shakeSensInterruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(shakeSensInterruptPin), handleInterrupt, RISING);
  digitalWrite(shakeSensIndicatorLED, LOW); //Writes the Indicator LED to LOW ie. OFF at the start of the code
}

void loop() {
  if (interruptFlag) {
    interruptFlag = false;
    digitalWrite(shakeSensIndicatorLED, HIGH);
    tone(buzzer, 100, 10);
    noTone(buzzer);

    
  }

}

void handleInterrupt() {
  interruptFlag = true;
}

