#include <ArduinoJson.h>

// recomended to set to the maximum analog pin
// A15 for arduino mega
const int MAX_PINS = A15;

DynamicJsonDocument commandsBuffer(1024);
DynamicJsonDocument commandBuffer(256);
DynamicJsonDocument responseBuffer(512);

enum Type {setPin, digWrite, digRead, anWrite, anRead};
enum Mode {output, input};

/**A array holding all the pin states.
 * 
 * The length of th array must be more than or equal to
 * pin that is going to be used with the largest port id.
 * if the pin with the highest pin number is 13 then
 * MAX_PINS must also be 13 or more.
*/
Mode pins[MAX_PINS];

Type mapType(String type) {
  Serial.println(type);
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

String check_pin(JsonObject response, int pin, Mode mode) {
  if (pins[pin] != mode) {
    return incorrect_pin_mode(response, pin, pins[pin]);
  }
}

String runCommand(JsonVariant command) {
  Serial.println("Running command");
  const char* origin = command["origin"];
  const char* typestring = command["type"];
  Type type = mapType(typestring);
  int pin = command["pin"];;
  bool digvalue;
  int anvalue;
  String result = "";
  String check;

  // standard response
  JsonObject response = responseBuffer.to<JsonObject>();
  response["origin"] = "arduino";

  switch(type) {
    case setPin:
      if (pin > MAX_PINS) { return pin_number_exceds_max(response, pin); }
      digvalue = command["value"];
      pinMode(pin, digvalue);
      pins[pin] = digvalue ? output : input;

      // generate response
      response["type"] = getType(type);
      response["pin"] = pin;
      response["value"] = digvalue;

      serializeJson(response, result);
      return result;

    case digWrite:
      // make sure pin is initialized and in the right mode
      check = check_pin(response, pin, output);
      if (check != NULL) { return check; }

      // write to the pin
      digvalue = command["value"];
      digitalWrite(pin, digvalue);

      // generate response
      response["type"] = getType(type);
      response["pin"] = pin;
      response["value"] = digvalue;

      serializeJson(response, result);
      return result;

    case digRead:

      check = check_pin(response, pin, input);
      if (check != NULL) { return check; }

      digvalue = digitalRead(pin);

      // generate response
      response["type"] = getType(type);
      response["pin"] = pin;
      response["value"] = digvalue;
      
      serializeJson(response, result);
      return result;

    case anWrite:
      // make sure pin is initialized and in the right mode
      check = check_pin(response, pin, output);
      if (check != NULL) { return check; }

      // write to the pin
      anvalue = command["value"];
      analogWrite(pin, anvalue);

      // generate response
      response["type"] = getType(type);
      response["pin"] = pin;
      response["value"] = anvalue;

      serializeJson(response, result);
      return result;

    case anRead:

      check = check_pin(response, pin, input);
      if (check != NULL) { return check; }

      anvalue = analogRead(pin);

      // generate response
      response["type"] = getType(type);
      response["pin"] = pin;
      response["value"] = anvalue;
      
      serializeJson(response, result);
      return result;

    default:
      return "{}";
  }
}

void parseCommands() {
  String input = Serial.readString();
  input.trim();
  Serial.println(input);
  deserializeJson(commandsBuffer, input);
  JsonArray commands = commandsBuffer.as<JsonArray>();
  Serial.println("number of commands:" + String(commands.size()));

  if (commands.size() == 0) {return;}

  String responses[commands.size()];

  for (int i = 0; i < commands.size(); i++) {
    JsonVariant command = commands[i];

    responses[i] = runCommand(command);
  }

  for (int i=0; i < commands.size(); i++) {
    Serial.print(responses[i]);
  }
  Serial.println();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  for (int i = 0; i <= MAX_PINS; i++ ){
    pinMode(i, OUTPUT);
    pins[i] = output;
  }

}

void loop() {
  // wait for command
  while (Serial.available() == 0) {}

  // get json representation
  parseCommands();
}
