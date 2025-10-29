#ifndef MOTOR_H
#define MOTOR_H

class Motor {
  private:
    int pin1;
    int pin2;
    
  public:
    Motor(int directionPin1, int directionPin2);
    
    void forward(int speed);
    void backward(int speed);
    void stop();
};

#endif