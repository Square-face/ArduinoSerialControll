#include "Controllers.h"

int targetMotorSpeed[MOTOR_COUNT];
int targetServoPos[SERVO_COUNT];
int targetStepperPos[STEPPER_COUNT];

String parseString;
String valuesString;

void setup() {
  Serial.begin(57600);
  Serial.println("Communication Established. Setting pins...");

  setMotorPins();
  setStepperPins();
}

void parseMotorValues(String speed) {
  for (int i = 0; i < MOTOR_COUNT; i++) {
    // get the index of the next ,
    // the , indicates the next stepper to get the target pos for
    int speedIndex = speed.indexOf(",");

    // if the index is -1, there are no more comas and the last value will be stored
    if (speedIndex == -1) {
      motors[i].targetSpeed = speed.toInt();
      continue;
    }

    // save the target position
    int targetspeed = speed.substring(0, speedIndex+1).toInt();
    motors[i].targetSpeed = targetspeed;

    // cut it from the string
    speed.remove(0, speedIndex+1);
  };
}
void parseStepperValues(String pos) {
  for (int i = 0; i < STEPPER_COUNT; i++) {
    // get the index of the next ,
    // the , indicates the next stepper to get the target pos for
    int targetPosIndex = pos.indexOf(",");
    bool enabled = (pos.charAt(0) == "E");
    int targetPos = pos.substring(1, targetPosIndex+1).toInt();

    // if the index is -1, there are no more comas and the last value will be stored
    if (targetPosIndex == -1) {
      steppers[i].enabled = enabled
      steppers[i].targetPos = pos.substring(1, pos.length()-1);
      continue;
    }

    // save the target position
    steppers[i].enabled = enabled;
    steppers[i].targetPos = targetPos;

    // cut it from the string
    pos.remove(0, targetPosIndex+1);
  };
}

void parseServoValues(String pos) {
  for (int i = 0; i < SERVO_COUNT; i++) {
    // get the index of the next ,
    // the , indicates the next servo to get the target pos for
    int targetPosIndex = pos.indexOf(",");

    // if the index is -1, there are no more comas and the last value will be stored
    if (targetPosIndex == -1) {
      servos[i].targetPos = pos.toInt();
      continue;
    }

    // save the target position
    int targetPos = pos.substring(0, targetPosIndex+1).toInt();
    servos[i].targetPos = targetPos;

    // cut it from the string
    pos.remove(0, targetPosIndex+1);
  };
}

void parseValues(){
  String input = Serial.readString();

  // =====Motors=====
  parseString = input.substring(0, input.indexOf("["));
  if (parseString != "Motor") {return false;}
  input.remove(0, input.indexOf("[")+1);

  valuesString = input.substring(0, input.indexOf("]"));
  input.remove(0, input.indexOf("]")+1);

  parseMotorValues(valuesString);

  // =====Steppers=====
  parseString = input.substring(0, input.indexOf("["));

  if (parseString != "Stepper") {return false;}

  input.remove(0, input.indexOf("[")+1);

  valuesString = input.substring(0, input.indexOf("]"));
  input.remove(0, input.indexOf("]")+1);

  parseStepperValues(valuesString);

  // =====Servos=====
  parseString = input.substring(0, input.indexOf("["));

  if (parseString != "Servo") {return false;}

  input.remove(0, input.indexOf("[")+1);

  valuesString = input.substring(0, input.indexOf("]"));
  input.remove(0, input.indexOf("]")+1);

  parseServoValues(valuesString);
}

void loop() {
  if (Serial.available()) {
    Serial.println("Processing...");
    parseValues();
  }

  setAll();
}

// Motor[]Stepper[0]Servo[0,0,0,0]