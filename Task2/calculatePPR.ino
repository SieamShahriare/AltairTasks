const int encoderPinA = 2;
const int encoderPinB = 3;

volatile long pulseCount = 0;
int rotationCount = 0;
const int targetRotations = 10;
bool counting = false;
bool testComplete = false;
int lastStateA = 0;

unsigned long lastTime = 0;
const interval = 100;

void setup() {
  Serial.begin(9600);
  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  
  lastStateA = digitalRead(encoderPinA);
  
  Serial.println("Rotate encoder 10 times completely, then press Enter");
  Serial.println("Starting pulse count: 0");
  counting = true;
}

void loop() {
  int currentStateA = digitalRead(encoderPinA);
  
  if (currentStateA != lastStateA) {
    if (digitalRead(encoderPinB) != currentStateA) {
      pulseCount++;
    } else {
      pulseCount--;
    }
    lastStateA = currentStateA;
  }
  
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= interval && counting) {
    Serial.print("Current pulse count: ");
    Serial.println(pulseCount);
    lastTime = currentTime;
  }
  
  if (Serial.available()) {
    Serial.read();
    if (!testComplete && counting) {
      displayResults();
      testComplete = true;
      counting = false;
    } else if (testComplete) {
      resetTest();
    }
  }
}

void displayResults() {
  long totalPulses = abs(pulseCount);
  
  float calculatedPPR = (float)totalPulses / targetRotations;
  
  Serial.print("Target Rotations: ");
  Serial.println(targetRotations);
  Serial.print("Total Pulses Counted: ");
  Serial.println(totalPulses);
  Serial.print("Calculated PPR: ");
  Serial.println(calculatedPPR, 2);
  Serial.print("PPR (rounded): ");
  Serial.println(round(calculatedPPR));
  Serial.println("Press Enter to test again");
}

void resetTest() {
  pulseCount = 0;
  rotationCount = 0;
  testComplete = false;
  counting = true;
  lastStateA = digitalRead(encoderPinA);
  Serial.println("\nTest reset");
}
