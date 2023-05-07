#include <Servo.h>
/** Servo configuration
 * Servo Angels are between 0 and 180.
*/

// servo template
struct ServoStruct {
  int signal;       // GPIO pin connected to servo
  float dpi;        // the amount of movement for each loop cycle, high number = more
  int targetPos;    // the target position to travel to
  float currentPos; // the current modpint position
  bool enabled;     // if the servo is enabled(attached) or not
};


// config servos
#define SERVO_COUNT 4 // the number of servos
ServoStruct servos[SERVO_COUNT] = {
  {13,  0.0001, 0, 0.0, false}, // shoulder
  {11,  0.0001, 0, 0.0, false}, // elbow
  {10,  0.01,   0, 0.0, false}, // wrist
  {9,   0.1,    0, 0.0, false}  // claw
};




Servo servoControllers[SERVO_COUNT];

void initServos() {}

void parseServo() {
  String values = Serial.readStringUntil(valueEnd);

  for (int i = 0; i < SERVO_COUNT; i++) {
    // break if the string is empty
    if (values == "") {break;}

    // get the index of the next ,
    // the , indicates the next servo to get the target pos for
    int endIndex = values.indexOf(",");

    // create a string for the value for this servo only
    String value;
    if (endIndex == -1) {value = values;}
    else {value = values.substring(0, endIndex);}

    // get enable state and target pos
    bool enabled = values.startsWith(String(enableString)); // if the servo is enabled or not
    int targetPos = values.substring(1, endIndex).toInt(); // the position value for the servo

    // save values
    servos[i].enabled = enabled;
    servos[i].targetPos = targetPos;

    // cut it from the string
    values.remove(0, endIndex);
  };
}

void attach(int index) {
  // don't do anything if the serv is alredy attached
  if (servoControllers[index].attached()) {return;}

  // attach the servo
  servoControllers[index].attach(servos[index].signal);
}

void detach(int index) {
  // don't do anything if the servo isn't attached
  if (!servoControllers[index].attached()) {return;}

  // detach the servo
  servoControllers[index].detach();
}

void updateServo(int index) {
  ServoStruct servo = servos[index];

  // detach or attach servo
  if (!servo.enabled) {detach(index);}
  else {attach(index);}

  // increase or decrease the current position
  if (servo.currentPos > servo.targetPos) {
    // to avoid an undershoot, pick the biggest value if the current position is more than the target position
    servo.currentPos = max(servo.currentPos-servo.dpi, servo.targetPos);
  } else if (servo.currentPos < servo.targetPos) {
    // to avoid an overshoot, pick the lowest value if the current position is less than the target position
    servo.currentPos = min(servo.currentPos+servo.dpi, servo.targetPos);
  }

  // update position
  servoControllers[index].write(round(servo.currentPos));
  servos[index].currentPos = servo.currentPos;
}