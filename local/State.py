class motor():
    def __init__(self):
        self.speed = 0

class stepper():
    def __init__(self):
        self.position = 0

class servo():
    def __init__(self):
        self.position = 0



class State:
    def __init__(self, motorCount, stepperCount, servoCount):
        self.motorCount = motorCount
        self.stepperCount = stepperCount
        self.servoCount = servoCount

        self.motors = [motor() for _ in range(motorCount)]
        self.steppers = [stepper() for _ in range(stepperCount)]
        self.servos = [servo() for _ in range(servoCount)]
    
    def generate(self):

        motorSpeeds = [str(motor.speed) for motor in self.motors]
        stepperPositions = [str(stepper.position) for stepper in self.steppers]
        servoPositions = [str(servo.position) for servo in self.servos]

        return f"Motor[{','.join(motorSpeeds)}]Stepper[{','.join(stepperPositions)}]Servo[{','.join(servoPositions)}]"
