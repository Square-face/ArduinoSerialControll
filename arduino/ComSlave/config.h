/**
* Configuraton settings for Arduino Serial Controll (ASC)
*/

#define baudrate 57600

const char valueStart   = '[';
const char valueEnd     = ']';
const char enableString = 'E';

enum Controller {MOTOR, SERVO, STEPPER};
Controller getCon(String id){
  if (id == "Motor")    { return MOTOR;   }
  if (id == "Servo")    { return SERVO;   }
  if (id == "Srepper")  { return STEPPER; }
}