
const int MAX_PINS = A5;

enum Mode {output, input};

String addString(String key, String value, bool cap = true) {
  String result = "\"" + key + "\":\""+ value +"\"";
  if (cap) {
    result += ",";
  }
  return result;
}

String addInt(String key, int value, bool cap = true) {
    String result = "\"" + key + "\":"+ String(value);
  if (cap) {
    result += ",";
  }
  return result;
}

String addBool(String key, bool value, bool cap = true) {
  String result = "\"" + key + "\":"+ (value?"true":"false");
  if (cap) {
    result += ",";
  }
  return result;
}

String origin_not_master(String base){

  base += addString("type", "error");
  base += addString("error", "ORIGIN_NOT_MASTER");
  base += addString("message", "Command origin is not master.", false);

  return base+"}";
}

String pin_number_exceds_max(String base, int pin) {

  base += addString("type", "error");
  base += addString("error", "PIN_SELECT_OUTSIDE_MAX_PIN_RANGE");
  base += addString("message", "The requested pin(" + String(pin) + ") is outside than the maximum pin range of " + String(MAX_PINS), false);

  return base+"}";
}

String incorrect_pin_mode(String base, int pin, Mode mode){

  base += addString("type", "error");
  base += addString("error", "INCORRECT_PIN_MODE");
  base += addString("message", String((mode == output) ? "Input" : "Output") + " opperations are not supported when pin(" + String(pin) + ") is in " + ((mode == output) ? "Output" : "Input") + " mode", false);

  return base+"}";
}

// [{"origin":"master","type":"digitalWrite","pin":13,"value":true}]
// [{"origin":"master","type":"setPin","pin":14,"value":false}]
// [{"origin":"master","type":"analogRead","pin":14}]