const int buzzerPin = 5;
const int secondRedPin = 6;
const int firstRedPin = 7;
const int secondYellowPin = 8;
const int firstYellowPin = 9;
const int secondGreenPin = 10;
const int firstGreenPin = 11;
const int secondBluePin = 12;
const int firstBluePin = 13;
const int antennaPin = A0;

const int numberOfLeds = 8;
int leds[numberOfLeds] = {
  secondRedPin, firstRedPin, secondYellowPin, firstYellowPin, secondGreenPin, firstGreenPin, secondBluePin, firstBluePin
};


const int numberOfLevels = 8;           //(at lvl 0 will be 1 led open, lvl 2 -> 2 leds, at lvl 2 -> 3 leds ... at lvl 7 -> 8 leds)
bool levelMatrix[numberOfLevels][numberOfLeds] = {
  {0, 0, 0, 0, 0, 0, 0, 1}, // 0
  {0, 0, 0, 0, 0, 0, 1, 1}, // 1
  {0, 0, 0, 0, 0, 1, 1, 1}, // 2
  {0, 0, 0, 0, 1, 1, 1, 1}, // 3
  {0, 0, 0, 1, 1, 1, 1, 1}, // 4
  {0, 0, 1, 1, 1, 1, 1, 1}, // 5
  {0, 1, 1, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 1, 1, 1, 1, 1}, // 7
};

int maxEmfValue = 0;
int emfValue = 0;
int minEmfBound = 0;
int maxEmfBound = 10;
int currentLevel = 0;
int buzzerPitch = 0;
int minPitchBound = 850;
int maxPitchBound = 950;
int noSoundBellow = 2;
unsigned long checkInterval = 100;
unsigned long lastCheckTime = 0;

void setup() {
  for (int i = 0; i < numberOfLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(antennaPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  emfValue = analogRead(antennaPin);
  if (emfValue > maxEmfValue) maxEmfValue = emfValue;
  if (millis() >= lastCheckTime + checkInterval) {
    lastCheckTime = millis();
    maxEmfValue = constrain(maxEmfValue, minEmfBound, maxEmfBound);
    currentLevel = map(maxEmfValue, minEmfBound, maxEmfBound, 0, numberOfLevels - 1);
    buzzerPitch = map(currentLevel, 0, numberOfLevels - 1, minPitchBound, maxPitchBound);
    displayLevel(currentLevel);
    maxEmfValue = 0;
  }
}
void displayLevel(int level) {
  for (int i = 0; i < numberOfLeds; i++) {
    digitalWrite(leds[i], levelMatrix[level][i]);
  }
  if (level >= noSoundBellow) tone(buzzerPin, buzzerPitch, checkInterval);
}
