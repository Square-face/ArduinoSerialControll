#include <ArduinoJson.h>

String origin_not_master(JsonObject buffer){

  buffer["type"] = "error";
  buffer["error"] = "ORIGIN_NOT_MASTER";
  buffer["message"] = "Command origin is not master.";

  String result = "";
  serializeJson(buffer, result);
  buffer.clear();
  return result;
}

String pin_number_exceds_max(JsonObject buffer, int pin) {

  buffer["type"] = "error";
  buffer["error"] = "PIN_SELECT_OUTSIDE_MAX_PIN_RANGE";
  buffer["message"] = "The requested pin(" + String(pin) + ") is outside than the maximum pin range of " + String(MAX_PINS);

  String result = "";
  serializeJson(buffer, result);
  buffer.clear();
  return result;
}

String incorrect_pin_mode(JsonObject buffer, int pin, Mode mode){

  buffer["type"] = "error";
  buffer["error"] = "INCORRECT_PIN_MODE";
  buffer["message"] = String((mode == output) ? "Input" : "Output") + " opperations are not supported when pin(" + String(pin) + ") is in " + ((mode == output) ? "Output" : "Input") + " mode";

  String result = "";
  serializeJson(buffer, result);
  buffer.clear();
  return result;
}

// [{"origin":"master","type":"digitalWrite","pin":3,"value":true}]