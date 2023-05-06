#include "Pins.h"

const float SERVO_DPI = 0.002;

int roundUp(double num) {
  int test = round(num);
  if ((test < num) && (num > 0)) {
    return test+1;
  } else if ((test > num) && (num < 0)){
    return test-1;
  }
  else{
    return test;
  }
}

void setMotor(int index) {
  Motor motor = motors[index];

  if (motor.targetSpeed < 0) {
    digitalWrite(motor.direction, HIGH);
  } else {
    digitalWrite(motor.direction, LOW);
  }
  analogWrite(motor.pwm, abs(motor.targetSpeed));
  motor.currentSpeed = motor.targetSpeed;
}

void setStepper(int index) {
  Stepper stepper = steppers[index];

  if (stepper.targetPos > stepper.currentPos) {
    digitalWrite(stepper.direction, HIGH);
    digitalWrite(stepper.step, LOW);
    delayMicroseconds(2);
    digitalWrite(stepper.step, HIGH);
    steppers[index].currentPos = stepper.currentPos + 1;
  }

  if (stepper.targetPos < stepper.currentPos) {
    digitalWrite(stepper.direction, LOW);
    digitalWrite(stepper.step, LOW);
    delayMicroseconds(2);
    digitalWrite(stepper.step, HIGH);
    steppers[index].currentPos = stepper.currentPos - 1;
  }
}

void setServo(int index) {
  ServoStruct servo = servos[index];
  float difference = servo.currentPos - servo.targetPos;
  float movement = difference * servo.dpi;

  if ((movement > 1) || (movement < -1)) {
    servo.currentPos = servo.currentPos - movement;
  } else {
    servo.currentPos = servo.targetPos;
  }


  servo.controller.write(round(servo.currentPos));
  servos[index].currentPos = servo.currentPos;
}

void setAll() {
  for (int i = 0; i < MOTOR_COUNT; i++) {
    setMotor(i);
  }
  for (int i = 0; i < STEPPER_COUNT; i++) {
    setStepper(i);
  }
  for (int i = 0; i < SERVO_COUNT; i++) {
    setServo(i);
  }
}