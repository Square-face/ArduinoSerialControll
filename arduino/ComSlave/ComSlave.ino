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
    delay(1);
    parseValues();
    Serial.println("Done");
  }
  setAll();
}


void parseValues(){
  Serial.println("getting values");
  Controller id;
  while (Serial.available()) {
    String text = Serial.readStringUntil(valueStart);
    id = getCon(text);
    Serial.print(text);
    Serial.print(" : ");
    Serial.println(id);

    switch (id) {
      case MOTOR:
        parseMotor();
        break;
      case SERVO:
        parseServo();
        break;
      case STEPPER:
        parseStepper();
        break;
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