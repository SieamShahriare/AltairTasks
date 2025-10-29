#include "motor.h"

Motor leftMotor(5, 6);
Motor rightMotor(9, 10);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Moving Forward");
  leftMotor.forward(200);
  rightMotor.forward(200);
  delay(2000);
  
  Serial.println("Stopping");
  leftMotor.stop();
  rightMotor.stop();
  delay(1000);
  
  Serial.println("Moving Backward");
  leftMotor.backward(150);
  rightMotor.backward(150);
  delay(2000);
  
  Serial.println("Stopping");
  leftMotor.stop();
  rightMotor.stop();
  delay(1000);
}