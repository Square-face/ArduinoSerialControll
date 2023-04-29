import serial, Command, Response

class Arduino:
    def __init__(self, port: str, baudrate: int, timeout: float = 10.0):
        self.port = port
        self.baudrate = baudrate
        self.timeout = timeout
        self.serial = serial.Serial()

        serial.baudrate = self.baudrate
        serial.port = self.port
        serial.timeout = self.timeout
    
    def open(self):
        serial.open()

    def _wait_for_response(self):
        start = serial.read()

    
    def send_commands(self, command: Command) -> Response:
        serial.write(command.toString())

        
