#include <ArduinoJson.h>
#include "ResponsePresets.h"

// recomended to set to the maximum analog pin
// A15 for arduino mega

DynamicJsonDocument commandBuffer(512);

enum Type {setPin, digWrite, digRead, anWrite, anRead};


/**A array holding all the pin states.
 * 
 * The length of th array must be more than or equal to
 * pin that is going to be used with the largest port id.
 * if the pin with the highest pin number is 13 then
 * MAX_PINS must also be 13 or more.
*/
Mode pins[MAX_PINS];

Type mapType(String type) {
  if (type == "setPin")       return setPin;
  if (type == "digitalWrite") return digWrite;
  if (type == "digitalRead")  return digRead;
  if (type == "analogWrite")  return anWrite;
  if (type == "analogRead")   return anRead;
}

String getType(Type type) {
  switch(type) {
    case setPin:    return "setPin";
    case digWrite:  return "digitalWrite";
    case digRead:   return "digitalRead";
    case anWrite:   return "analogWrite";
    case anRead:    return "analogRead";
  }
}

String check_pin(String response, int pin, Mode mode) {
  if (pins[pin] != mode) {
    return incorrect_pin_mode(response, pin, pins[pin]);
  }
  return "";
}

String runCommand(JsonVariant command) {
  const char* origin = command["origin"];
  const char* typestring = command["type"];
  Type type = mapType(typestring);
  int pin = command["pin"];;
  bool digvalue;
  int anvalue;
  String check;

  // standard response
  String response = "{";
  response += addString("origin", "arduino");

  switch(type) {
    case setPin:
      if (pin > MAX_PINS) { return pin_number_exceds_max(response, pin); }
      digvalue = command["value"];
      pinMode(pin, digvalue);
      pins[pin] = digvalue ? output : input;

      // generate response
      response += addString("type", getType(type));
      response += addInt("pin", pin);
      response += addBool("value", digvalue, false);
      response += "}";

      return response;

    case digWrite:
      // make sure pin is initialized and in the right mode
      check = check_pin(response, pin, output);
      if (check != NULL) { return check; }

      // write to the pin
      digvalue = command["value"];
      digitalWrite(pin, digvalue);

      // generate response
      response += addString("type", getType(type));
      response += addInt("pin", pin);
      response += addBool("value", digvalue, false);
      response += "}";

      return response;

    case digRead:

      check = check_pin(response, pin, input);
      if (check != NULL) { return check; }

      digvalue = digitalRead(pin);

      // generate response
      response += addString("type", getType(type));
      response += addInt("pin", pin);
      response += addBool("value", digvalue, false);
      response += "}";

      return response;

    case anWrite:
      // make sure pin is initialized and in the right mode
      check = check_pin(response, pin, output);
      if (check != NULL) { return check; }

      // write to the pin
      anvalue = command["value"];
      analogWrite(pin, anvalue);

      // generate response
      response += addString("type", getType(type));
      response += addInt("pin", pin);
      response += addInt("value", anvalue, false);
      response += "}";

      return response;

    case anRead:

      check = check_pin(response, pin, input);
      if (check != NULL) { return check; }

      anvalue = analogRead(pin);

      // generate response
      response += addString("type", getType(type));
      response += addInt("pin", pin);
      response += addInt("value", anvalue, false);
      response += "}";

      return response;

    default:
      return "{}";
  }
}

void parseCommands() {
  String result = "[";

  while(Serial.available()) {

    String input = Serial.readStringUntil("}");
    input.trim();
    if (input.startsWith("[")) { input.remove(0); }
    if (input == "]") {
      if (result.endsWith(",")) {
        result.remove(result.length());
      }
      break;
    }
    deserializeJson(commandBuffer, input);
    JsonObject command = commandBuffer.as<JsonObject>();

    String response = runCommand(command);
    
    result += response;
    result += ",";
  }
  result.
  result += "]";
  Serial.println(result);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  for (int i = 0; i <= MAX_PINS; i++ ){
    pinMode(i, OUTPUT);
    pins[i] = output;
  }
  Serial.println("Hello, World!");
}

void loop() {
  // wait for command
  while (Serial.available() == 0) {}

  // get json representation
  parseValues();
}
