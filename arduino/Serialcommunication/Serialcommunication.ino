#include <ArduinoJson.h>

DynamicJsonDocument commandsBuffer(1024);
DynamicJsonDocument commandBuffer(256);

const String ORIGIN_NOT_MASTER = "{\"type\":\"error\", \"message\":\"Origin is not master\"}";

enum Type {digWrite, digRead, anWrite, anRead};

Type mapType(String type) {
  Serial.println(type);
  if (type == "digitalWrite") return digWrite;
  if (type == "digitalRead") return digRead;
  if (type == "analogWrite") return anWrite;
  if (type == "analogRead") return anRead;
}

String runCommand(JsonVariant command) {
  Serial.println("Running command");
  const char* origin = command["origin"];
  Serial.println(origin);
  Serial.println("typestring:");
  const char* typestring = command["type"];
  Serial.println(typestring);
  Serial.println("endoftype");
  Type type = mapType(typestring);
  int pin;
  bool digvalue;
  bool digresult;
  String result;

  switch(type) {
    case digWrite:
      pin = command["pin"];
      digvalue = command["value"];
      digitalWrite(pin, digvalue);
      return "{}";
    case digRead:
      Serial.println("reading digital pin");
      pin = command["pin"];
      digresult = digitalRead(pin);
      String resultString = String(digresult);
      Serial.println(resultString);

      StaticJsonDocument<1028> responseBuffer;
      JsonObject response = responseBuffer.to<JsonObject>();

      response["origin"] = "arduino";
      String output = "";
      serializeJson(responseBuffer, output);

      Serial.println("Response: ");
      Serial.println(output);

      return output;
    default:
      Serial.println("no matches");
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
  pinMode(3, INPUT);
}

void loop() {
  // wait for command
  while (Serial.available() == 0) {}

  // get json representation
  parseCommands();

}
