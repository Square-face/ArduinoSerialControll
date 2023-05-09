class motor():
    def __init__(self):
        self.speed = 0
    
    def stringify(self):
        return f"{self.speed}"

class stepper():
    def __init__(self):
        self.enabled = False
        self.position = 0
    
    def stringify(self):
        return f"{self.enabled if 'E' else 'D'}{self.position}"

class servo():
    def __init__(self):
        self.enabled = False
        self.position = 0
    
    def stringify(self):
        return f"{self.enabled if 'E' else 'D'}{self.position}"



class State:
    def __init__(self, motorCount, stepperCount, servoCount):
        self.motorCount = motorCount
        self.stepperCount = stepperCount
        self.servoCount = servoCount

        self.motors = [motor() for _ in range(motorCount)]
        self.steppers = [stepper() for _ in range(stepperCount)]
        self.servos = [servo() for _ in range(servoCount)]
    
    def generate(self):

        motorSpeeds       = [motor.stringify()      for motor   in self.motors  ]
        stepperPositions  = [stepper.stringify()    for stepper in self.steppers]
        servoPositions    = [servo.stringify()      for servo   in self.servos  ]

        return f"Motors[{','.join(motorSpeeds)}]Steppers[{','.join(stepperPositions)}]Servos[{','.join(servoPositions)}]"
