/** Motor configuration
 * All speeds are from -255 to 255 with 0 being a standstill.
 * negative speed will pull the direction pin to HIGH while
 * PWM will be the absolute value.
*/

// motor Temaplate
struct Motor {
  int pwm;          // GPIO pin used for PWM controll
  int in1;    // GPIO pin used for direction controll
  int in2;    // GPIO pin used for direction controll
  int targetSpeed;  // requested speed, usualy Zero when initialized
  int currentSpeed; // current speed, should be Zero
};

// config motors
#define MOTOR_COUNT 2 // number of motors
Motor motors[MOTOR_COUNT] = {
  {9, A5, A4, 0, 0},
  {10, A3, A2, 0, 0}
};


// set all the pins as output pins
void initMotors() {
  Serial.print("Setting motor pins... ");
  for (int i = 0; i < MOTOR_COUNT; i++) {

    Motor motor = motors[i];
    pinMode(motor.pwm, OUTPUT);
    pinMode(motor.in1, OUTPUT);
    pinMode(motor.in2, OUTPUT);
  }
  Serial.println("Done");
}

// convert serial stream to motor values
void parseMotor() {
  String values = Serial.readStringUntil(valueEnd);
  for (int i = 0; i < MOTOR_COUNT; i++) {
    // break if values string is empty
    if (values == "") {break;}

    // get the index of the next ,
    // the , indicates the next stepper to get the target pos for
    int endIndex = values.indexOf(",");

    // get the string holding the speed value for this motor
    String value;
    if (endIndex == -1) {value = values;}
    else {value = values.substring(0, endIndex);}

    // get speed
    int targetspeed = value.toInt();
    
    // save speed
    motors[i].targetSpeed = targetspeed;

    // cut it from the string
    values.remove(0, endIndex+1);
  };
}

void updateMotor(int index) {
  Motor motor = motors[index];

  // set direction pin
  if (motor.targetSpeed < 0) {
    digitalWrite(motor.in1, HIGH);
    digitalWrite(motor.in2, LOW);
  } else {
    digitalWrite(motor.in1, LOW);
    digitalWrite(motor.in2, HIGH);
  }

  // set pwm
  analogWrite(motor.pwm, abs(motor.targetSpeed));
  motor.currentSpeed = motor.targetSpeed;
}