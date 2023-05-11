class motor():
    def __init__(self, speed: int = 0):
        self.speed = speed
    
    @staticmethod
    def fromDict(data: dict):
        return motor(data["speed"])
    
    def stringify(self):
        return f"{self.speed}"

class stepper():
    def __init__(self, enabled:bool = False, position: int = 0):
        self.enabled = enabled
        self.position = position

    @staticmethod
    def fromDict(data: dict):
        return stepper(data["enabled"], data["position"])
    
    def stringify(self):
        return f"{'E' if self.enabled else 'D'}{self.position}"

class servo():
    def __init__(self, enabled:bool = False, position: int = 0):
        self.enabled = enabled
        self.position = position
    
    @staticmethod
    def fromDict(data: dict):
        return servo(data["enabled"], data["position"])
    
    def stringify(self):
        return f"{'E' if self.enabled else 'D'}{self.position}"



class State:
    def __init__(self, motorCount, stepperCount, servoCount):
        self.motorCount = motorCount
        self.stepperCount = stepperCount
        self.servoCount = servoCount

        self.motors = [motor() for _ in range(motorCount)]
        self.steppers = [stepper() for _ in range(stepperCount)]
        self.servos = [servo() for _ in range(servoCount)]
    
    def updateAll(self, data: dict):
        self.motors = [motor.fromDict(motorData) for motorData in data["motors"]]
        self.steppers = [stepper.fromDict(stepperData) for stepperData in data["steppers"]]
        self.servos = [servo.fromDict(servoData) for servoData in data["servos"]]
    
    def generate(self):

        motorSpeeds       = [motor.stringify()      for motor   in self.motors  ]
        stepperPositions  = [stepper.stringify()    for stepper in self.steppers]
        servoPositions    = [servo.stringify()      for servo   in self.servos  ]

        return f"Motors[{','.join(motorSpeeds)}]Steppers[{','.join(stepperPositions)}]Servos[{','.join(servoPositions)}]"
