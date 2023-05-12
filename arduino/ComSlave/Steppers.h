#include "round.h"

/** Stepper configuration
 * Stepper movement is just guesswork about how many stepps
 * it thinks it has moved from the starting position. 
*/
struct Stepper {
  int direction;    // direction Pin
  int step;         // step Pin
  int enable;       // enable Pin
  bool enabled;     // if the stepper is enabled
  int targetPos;    // the current target position
  float currentPos; // the current position
  int actualPos;    // the number of steps traveled relative to start pos
  float dpi;          // the amount of movement for each loop cycle, high = more
};


// {direction, step, enable, enabled, targetPos, currentPos, actualPos, dpi}
#define STEPPER_COUNT 1
Stepper steppers[STEPPER_COUNT] = {
  {4, 5, 12, false, 0, 0.0, 0.0, 1.0} // arm
};




void initSteppers() {
  Serial.print("Setting stepper pins... ");
  for (int i = 0; i < STEPPER_COUNT; i++) {

    Stepper stepper = steppers[i];

    pinMode(stepper.direction, OUTPUT);
    pinMode(stepper.step, OUTPUT);
    pinMode(stepper.enable, OUTPUT);

    // enable or dissable the stepper
    if (stepper.enabled) {
      digitalWrite(stepper.enable, HIGH);
    } else {
      digitalWrite(stepper.enable, LOW);
    }
  }
  Serial.println("Done");
}

void parseStepper() {
  String values = Serial.readStringUntil(valueEnd);
  Serial.println(values);
  for (int i = 0; i < STEPPER_COUNT; i++) {
    // break if values string is empty
    if (values == "") {break;}

    // get the index of the next ,
    // the , indicates the next stepper to get the target pos for
    int endIndex = values.indexOf(",");

    // get the string holding the enable and position values for this servo
    String value;
    if (endIndex == -1) {value = values;}
    else {value = values.substring(0, endIndex);}

    // get enable and position values
    bool enabled = values.startsWith(String(enableString));
    int targetPos = values.substring(1, endIndex).toInt();
    Serial.print(enabled);
    Serial.print(" : ");
    Serial.println(targetPos);

    // save enable and position values
    steppers[i].enabled = enabled;
    steppers[i].targetPos = targetPos;

    // cut it from the string
    values.remove(0, endIndex+1);
  };
}

void updateStepper(int index) {
  Stepper stepper = steppers[index];

  // ignore this stepper if it is disabled
  if (!stepper.enabled) { digitalWrite(stepper.enable, HIGH); return; }

  // enable stepper
  digitalWrite(stepper.enable, LOW);

  
  if (stepper.targetPos > stepper.currentPos) {
    Serial.print("T:C ");
    Serial.print(stepper.targetPos);
    Serial.print(" : ");
    Serial.println(stepper.currentPos);
    // to avoid overshoot if the current position is less than the target one, use the 
    // smallest value between the target posstion and current position plus stepper dpi
    steppers[index].currentPos = min(stepper.currentPos + stepper.dpi, stepper.targetPos);
  } else if (stepper.targetPos < stepper.currentPos) {
    Serial.print("T:C ");
    Serial.print(stepper.targetPos);
    Serial.print(" : ");
    Serial.println(stepper.currentPos);
    // to avoid undershoot if the current position is more than the target one, use the 
    // largest value between the target posstion and current position minus stepper dpi
    steppers[index].currentPos = max(stepper.currentPos - stepper.dpi, stepper.targetPos);
  }

  // while the actual position is more than the current position, reduce the actual position until it is less than or equal to the current position
  while (stepper.actualPos > roundUp(stepper.currentPos)) {
    Serial.print("A:C ");
    Serial.print(stepper.actualPos);
    Serial.print(" : ");
    Serial.println(stepper.currentPos);
    digitalWrite(stepper.direction, HIGH);
    digitalWrite(stepper.step, LOW);
    delayMicroseconds(5);
    digitalWrite(stepper.step, HIGH);
    stepper.actualPos--;
    steppers[index].actualPos--;
    delayMicroseconds(5);
  }

  // while the actual position is less than the current position, increase the actual position until it is more than or equal to the current position
  while (stepper.actualPos < roundUp(stepper.currentPos)) {
    Serial.print("A:C ");
    Serial.print(stepper.actualPos);
    Serial.print(" : ");
    Serial.println(stepper.currentPos);
    digitalWrite(stepper.direction, LOW);
    digitalWrite(stepper.step, LOW);
    delayMicroseconds(5);
    digitalWrite(stepper.step, HIGH);
    stepper.actualPos++;
    steppers[index].actualPos++;
    delayMicroseconds(5);
  }
}