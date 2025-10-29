#include "motor.h"

Motor::Motor(int pin1, int pin2)
{
    pin1 = directionPin1;
    pin2 = directionPin2;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
}

void Motor::forward(int speed)
{
    analogWrite(pin1, speed);
    analogWrite(pin2, 0);
}

void Motor::backward(int speed)
{
    analogWrite(pin1, 0);
    analogWrite(pin2, speed);
}

void Motor::stop()
{
    analogWrite(pin1, 0);
    analogWrite(pin2, 0);
}