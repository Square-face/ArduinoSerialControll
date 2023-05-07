#include <Servo.h>

struct Motor {
  int pwm;
  int direction;
  int targetSpeed;
  int currentSpeed;
};

struct Stepper {
  int direction;
  int step;
  int enable;
  bool enabled;
  int targetPos;
  int currentPos;
};

struct ServoStruct {
  int signal;
  Servo controller;
  int targetPos;
  float currentPos;
  float dpi;
};


const int MOTOR_COUNT = 2;
const int STEPPER_COUNT = 1;
const int SERVO_COUNT = 4;

Motor motors[MOTOR_COUNT] = {
  {A3, A2, 0, 0},
  {2, 3, 0, 0}
};

Stepper steppers[STEPPER_COUNT] = {
  {4, 5, 12, false, 0, 0}
};

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
ServoStruct servos[SERVO_COUNT] = {
  {13, servo1, 0, 0.0, 0.0001},
  {11, servo2, 0, 0.0, 0.0001},
  {10, servo3, 0, 0.0, 0.01},
  {9, servo4, 0, 0.0, 0.1}
};



void setMotorPins() {
  Serial.println("Setting motor pins...");
  for (int i = 0; i < MOTOR_COUNT; i++) {
    Serial.print("Setting motor (");
    Serial.print(i+1);
    Serial.print("): ");

    Motor motor = motors[i];

    pinMode(motor.pwm, OUTPUT);
    pinMode(motor.direction, OUTPUT);

    Serial.print("Done! (");
    Serial.print(motor.pwm);
    Serial.print(", ");
    Serial.print(motor.direction);
    Serial.println(")");
  }
  Serial.println("Motors set.");
}

void setStepperPins() {
  Serial.println("Setting stepper pins...");
  for (int i = 0; i < STEPPER_COUNT; i++) {
    Serial.print("Setting stepper (");
    Serial.print(i+1);
    Serial.print("): ");

    Stepper stepper = steppers[i];

    pinMode(stepper.direction, OUTPUT);
    pinMode(stepper.step, OUTPUT);
    pinMode(stepper.enable, OUTPUT);

    digitalWrite(stepper.enable, HIGH);

    Serial.print("Done! (");
    Serial.print(stepper.direction);
    Serial.print(", ");
    Serial.print(stepper.step);
    Serial.print(", ");
    Serial.print(stepper.enable);
    Serial.println(")");
  }
  Serial.println("Steppers set.");
}