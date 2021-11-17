const int dataPin = 12; // DS
const int latchPin = 11; // STCP
const int clockPin = 10; // SHCP

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};
const int displayCount = 4;

int digitArray[16] = {
//A B C D E F G DP 
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};

int vectorToDisplay[displayCount];      //initialised with 0 values by default

volatile bool state;                             //is 0 when we are in default state (when we navigate between displays and 1 when we are in the state when we modify the digit on a selected position
int currentPosition = 0;                //what display we are on (with the dot) at a given moment
bool dotStatus;                         //it is 0 when the dot on "currentPosition" is turned off and it is 1 when the dot is turned on (in first state it is allways on, and in the second state alternates between 0 and 1)

unsigned long timeBetweenDigits = 5;    //the time in milliseconds between showing one digit to another
unsigned long lastDigitTime = 0;

int currentDisplay;

unsigned long buttonTime = 250;
unsigned long lastButtonTime = 0;

int xValue = 0;
int yValue = 0;

unsigned long blinkTime = 500;
unsigned long lastBlinkTime = 0;

unsigned long joyStickTime = 100;
unsigned long lastJoyStickTime = 0;

int minThreshold = 400;
int maxThreshold = 600;
volatile bool joyMoved = 0;

bool invertedXAxis = 1;                       // true / false -> this is made for commodity, so you dont have to turn around the joystick  around
bool invertedYAxis = 1;

void setup() {
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(pinSW), buttonPressed, RISING);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
  Serial.begin(9600);
}

void loop() {
  readJoyStick();
  dotLogic();
  showVector();
}

void goDown() {
  if (vectorToDisplay[currentPosition] == 0) vectorToDisplay[currentPosition] = 9;                //minim value is 0, but we put 9 below 0 to have a full cicle
  else vectorToDisplay[currentPosition]--;
}

void goUp() {
  if (vectorToDisplay[currentPosition] == 9) vectorToDisplay[currentPosition] = 0;                //maxim value is 9, but we put 0 above 9, same reason
  else vectorToDisplay[currentPosition]++;
}

void goLeft() {
  if (currentPosition == 0) currentPosition = displayCount - 1;                                   //when we get to the leftmost position, moving left again will place us in the rightmost position to make a full cicle
  else currentPosition--;
}

void goRight() {
  if (currentPosition == displayCount - 1) currentPosition = 0;                                   //when we get to the rightmost position, moving right again will place us in the lefttmost, same reason
  else currentPosition++;
}

int digitWithDot(int initialDigit) {                                                              //same binary, but we change from 0 to 1 the least significant bit, so the number has a dot when we show it
  return initialDigit + 1;
}

void showVector() {
  if (lastDigitTime + timeBetweenDigits <= millis()) {
    lastDigitTime = millis();
    showDigit(currentDisplay);                                                                                                //the current digit means the current display because we show one digit on one display at a given time
    if (currentDisplay == currentPosition && dotStatus) writeReg(digitWithDot(digitArray[vectorToDisplay[currentDisplay]]));
    else writeReg(digitArray[vectorToDisplay[currentDisplay]]);
    if (currentDisplay == displayCount - 1) currentDisplay = 0;
    else currentDisplay++;
  }
}

void buttonPressed() {
  if (lastButtonTime + buttonTime <= millis()) {
    lastButtonTime = millis();
    state = !state;
    joyMoved = 0;
  }
}

void dotLogic() {
  if (state) dotStatus = 1;
  else {
    if (lastBlinkTime + blinkTime <= millis()) {
      lastBlinkTime = millis();
      dotStatus = !dotStatus;
    }
  }
}


void  readJoyStick() {
  if (!state) {
    xValue = analogRead(pinX);
    if (lastJoyStickTime + joyStickTime <= millis()) {
      if (xValue <= minThreshold && !joyMoved) {
        if (!invertedXAxis) goLeft();
        else goRight();
        joyMoved = 1;
        lastJoyStickTime = millis();
      }
      if (xValue >= maxThreshold && !joyMoved) {
        if (!invertedXAxis) goRight();
        else goLeft();
        joyMoved = 1;
        lastJoyStickTime = millis();
      }
      if (xValue >= minThreshold && xValue <= maxThreshold) {
        joyMoved = 0;
        lastJoyStickTime = millis();
      }
    }
  }
  else {
    yValue = analogRead(pinY);
    if (lastJoyStickTime + joyStickTime <= millis()) {
      if (yValue <= minThreshold && !joyMoved) {
        if (!invertedYAxis) goDown();
        else goUp();
        joyMoved = 1;
        lastJoyStickTime = millis();
      }
      else if (yValue >= maxThreshold && !joyMoved) {
        if (!invertedYAxis) goUp();
        else goDown();
        joyMoved = 1;
        lastJoyStickTime = millis();
      }
      if (yValue >= minThreshold && yValue <= maxThreshold) {
        joyMoved = 0;
        lastJoyStickTime = millis();
      }
    }
  }
}

void showDigit(int displayNumber) {
  for(int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  digitalWrite(displayDigits[displayNumber], LOW);
}

void writeReg(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, digit);
  digitalWrite(latchPin, HIGH);
}