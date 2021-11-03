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
int stepsCounter = 0;
int waveLengthState3 = 20;                            //in steps, 1 step = 50 milliseconds
unsigned long buzzDuration = 100;                      //in milliseconds
int buzzTone = NOTE_AS4;                              
int waveLengthSoundState4 = 10;                       //in steps
int waveLengthLightState4 = 20;                       //in steps
unsigned long lastDebounceTime = 0;                    //in milliseconds
unsigned long debounceDelay = 50;                      //this is the value of a step in milliseconds

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
    stepsCounter = 0;
    lastDebounceTime = millis();
  }
  if(startedCycle) {
    if(millis() - lastDebounceTime > debounceDelay){
      lastDebounceTime = millis();
      stepsCounter++;
      if(stepsCounter <= 200) {}                       //we do nothing, we wait for the 10 seconds to pass so we can move to state 2
      else if (stepsCounter == 201){                   //we change to state 2
        setColors(LOW, HIGH, LOW, HIGH, LOW);
      }
      else if(stepsCounter <= 260) {}                   //we do nothing, we wait for the state 2 to end
      else if(stepsCounter <= 460) {                    //if we are in state 3
        if(stepsCounter == 261) {
          setColors(HIGH, LOW, LOW, LOW, HIGH);         //if we begin state 3 we change the colors
        }
        if(stepsCounter % waveLengthState3 == 1) {      //after a certain number of steps when we didnt make a sound, we make one
           tone(buzzerPin, buzzTone, buzzDuration);
        }
      }
      else {                                            //if we are in state 4
        if(stepsCounter % waveLengthLightState4 <= 1) {//one half of wave we have light, the other half we don't
          setColors(HIGH, LOW, LOW, LOW, LOW);
        }
        if(stepsCounter % waveLengthLightState4 >= waveLengthLightState4 / 2 + 1) setColors(HIGH, LOW, LOW, LOW, HIGH);

        if(stepsCounter % waveLengthSoundState4 == 1) { //we do the same sound as the one from step 3, but the sound is more frequent
          tone(buzzerPin, buzzTone, buzzDuration);
        }
      }
    }
  }
  digitalWrite(carRedPin, carRedState);
  digitalWrite(carYellowPin, carYellowState);
  digitalWrite(carGreenPin, carGreenState);
  digitalWrite(pedRedPin, pedRedState);
  digitalWrite(pedGreenPin, pedGreenState);
  if(stepsCounter == 560) {                            //here we stop the cycle, meaning we return to state 1
    startedCycle = 0;
    setColors(LOW, LOW, HIGH, HIGH, LOW);
  }
}

void setColors(bool carRed, bool carYellow, bool carGreen, bool pedRed, bool pedGreen) {
  carRedState = carRed;
  carYellowState = carYellow;
  carGreenState = carGreen;
  pedRedState = pedRed;
  pedGreenState = pedGreen;
}
