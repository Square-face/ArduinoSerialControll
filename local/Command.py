from typing import List

class JsonBuilder:
    def __init__(self):
        self.args = []

    def addString(self, key: str, value: str):
        self.args.append(f'"{key}":"{value}"')
        return self
    
    def addInt(self, key: str, value: int):
        self.args.append(f'"{key}":{value}')
        return self
    
    def addBoolean(self, key: str, value: bool):
        self.args.append(f'"{key}":{"true" if value else "false"}')
        return self
    
    def build(self):
        return "{" + ",".join(self.args) + "}"

class Command:
    """ A class for representing a command sent to the arduino

    A class representation for managing commands that may be
    converted to serial and sent over to the Arduino

    Attributes
    ------
    type : string
        The type of command this is.
    
    pin : int
        The pin number this command will be executed on on the Arduino.
    
    digital_value : bool, optional
        If applicable, the value used for digital write commands.
    
    analog_value : bool, optional
        If applicable, the value used for analog write commands.    
    """
    def __init__(self, type: str = None, pin: int = None, digital_value: bool = None, analog_value: int = None):
        self.type = type
        self.pin = pin
        self.digital_value = digital_value
        self.analog_value = analog_value
    
    def set_type(self, type: str):
        if type == None:
            raise ValueError("type argument must not be None")

        self.type = type

        return self
    
    def set_pin(self, pin: int):
        if pin == None:
            raise ValueError("pin argument must not be None")
        
        self.pin = pin

        return self
    
    def set_value(self, value):
        if isinstance(value, bool):
            self.analog_value = None
            self.digital_value = value
            return self

        if isinstance(value, int):
            self.analog_value = value
            self.digital_value = None
            return self
        
        raise ValueError("value argument must be either int or bool")
    
    def stringify(self):
        string = JsonBuilder()
        string.addString("origin", "master")
        string.addString("type", self.type)
        string.addInt("pin", self.pin)

        match self.type:
            case "digitalWrite":
                string.addBoolean("value", self.digital_value)
            case "analogWrite":
                string.addInt("value", self.analog_value)
        
        return string.build()

    @staticmethod
    def toString(commands) -> str:
        """Convert list of commands to a string representation
        
        Takes in a list of commands and joins them in a single string representing all of them.

        Parameters
        ------
        commands : List[Command]
            A array containing all the commands
        
        Returns
        ------
        str
            String representation for all commands in a array
        """
        serialString = "["

        for command in commands:
            serialString += command.stringify()
        
        serialString+="]"

        return serialString