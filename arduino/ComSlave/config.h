/**
* Configuraton settings for Arduino Serial Controll (ASC)
*/

#define baudrate 57600

const char valueStart   = "[";
const char valueEnd     = "]";
const char enableString = "E";

enum Controller {MOTOR, SERVO, STEPPER};
Controller getCon(String id){
  if (id = "Motors")    { return MOTOR;   }
  if (id = "Servos")    { return SERVO;   }
  if (id = "Sreppers")  { return STEPPER; }
}