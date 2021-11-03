#include "pitches.h"

const int buttonPin = 2;
const int buzzerPin = 3;
const int carRedPin = 5;
const int carYellowPin = 6;
const int carGreenPin = 7;
const int pedRedPin = 10;
const int pedGreenPin =11;

bool buttonState = LOW;
bool carRedState = LOW;
bool carYellowState = LOW;
bool carGreenState = HIGH;
bool pedRedState = HIGH;
bool pedGreenState = LOW;

bool startedCycle = 0;
int soundDelayState3 = 1000;
unsigned long buzzDuration = 100;
int buzzTone = NOTE_AS4;
int soundDelayState4 = 250;
int lightDelayState4 = 500;
unsigned long lastBuzz = -buzzDuration;
unsigned long lastLight = -lightDelayState4;
unsigned long callTime = 0;
unsigned long firstStateDuration = 10000;
unsigned long secondStateDuration = 3000;
unsigned long thirdStateDuration = 10000;
unsigned long fourthStateDuration = 5000;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(carRedPin, OUTPUT);
  pinMode(carYellowPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  pinMode(pedRedPin, OUTPUT);
  pinMode(pedGreenPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  if(!buttonState && !startedCycle) {
    startedCycle = 1;
    initialise();
    callTime = millis();
  }
  
  if(startedCycle) {
    if(millis() <= callTime + firstStateDuration) {}
    else if(millis() <= callTime + firstStateDuration + secondStateDuration) {
      setColors(LOW, HIGH, LOW, HIGH, LOW);
    }
    else if(millis() <= callTime + firstStateDuration + secondStateDuration + thirdStateDuration) {
      setColors(HIGH, LOW, LOW, LOW, HIGH);
      if(millis() >= lastBuzz + soundDelayState3){
        lastBuzz = millis();
        tone(buzzerPin, buzzTone, buzzDuration);
      }
    }
    else if(millis() <= callTime + firstStateDuration + secondStateDuration + thirdStateDuration + fourthStateDuration) {
      if(millis() >= lastLight + lightDelayState4){
        lastLight = millis();
        pedGreenState = !pedGreenState;
      }
      if(millis() >= lastBuzz + soundDelayState4){
        lastBuzz = millis();
        tone(buzzerPin, buzzTone, buzzDuration);
      }
    }
    else {
      startedCycle = 0;
      setColors(LOW, LOW, HIGH, HIGH, LOW);
    }
  }
  
  digitalWrite(carRedPin, carRedState);
  digitalWrite(carYellowPin, carYellowState);
  digitalWrite(carGreenPin, carGreenState);
  digitalWrite(pedRedPin, pedRedState);
  digitalWrite(pedGreenPin, pedGreenState);
}

void setColors(bool carRed, bool carYellow, bool carGreen, bool pedRed, bool pedGreen) {
  carRedState = carRed;
  carYellowState = carYellow;
  carGreenState = carGreen;
  pedRedState = pedRed;
  pedGreenState = pedGreen;
}

void initialise() {
  lastBuzz = 0;
  lastLight = 0;
}
