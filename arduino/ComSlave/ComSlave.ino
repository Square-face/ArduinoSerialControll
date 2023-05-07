#include "config.h"
#include "Servos.h"
#include "Steppers.h"
#include "Motors.h"

String parseString;
String valuesString;

void setup() {
  Serial.begin(57600);

  initMotors();
  initServos();
  initSteppers();
}

void loop() {
  if (Serial.available()) {
    Serial.println("Processing...");
    parseValues();
  }
  setAll();
}


void parseValues(){
  Controller id;
  while (Serial.available()) {
    id = getCon(Serial.readStringUntil(valueStart));

    switch (id) {
      case MOTOR:
        parseMotor();
      case SERVO:
        parseServo();
      case STEPPER:
        parseStepper();
    }
  }
}

void setAll() {
  for (int i = 0; i < MOTOR_COUNT; i++) {
    updateMotor(i);
  }
  for (int i = 0; i < SERVO_COUNT; i++) {
    updateServo(i);
  }
  for (int i = 0; i < STEPPER_COUNT; i++) {
    updateStepper(i);
  }
}