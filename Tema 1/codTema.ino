const int redPotPin = A0;
const int greenPotPin = A1;
const int bluePotPin = A2;

const int redLedPin = 11;
const int greenLedPin = 10;
const int blueLedPin = 9;

int redPotValue = 0;
int greenPotValue = 0;
int bluePotValue = 0;

int redLedValue = 0;
int greenLedValue = 0;
int blueLedValue = 0;

void setup() {
  pinMode(redPotPin, INPUT);
  pinMode(greenPotPin, INPUT);
  pinMode(bluePotPin, INPUT);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(bluePotPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  readPins();
  convert();
  setColor();
}
void readPins() {
  redPotValue = analogRead(redPotPin);
  greenPotValue = analogRead(greenPotPin);
  bluePotValue = analogRead(bluePotPin);
  Serial.println(redPotValue);
  Serial.println(greenPotValue);
  Serial.println(bluePotValue);
}
void convert() {
  redLedValue = map(redPotValue, 0, 1023, 0, 255);
  greenLedValue = map(greenPotValue, 0, 1023, 0, 255);
  blueLedValue = map(bluePotValue, 0, 1023, 0, 255);
}
void setColor() {
  analogWrite(redLedPin, redLedValue);
  analogWrite(greenLedPin, greenLedValue);
  analogWrite(blueLedPin, blueLedValue);
}
