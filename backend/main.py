import serial, time, json
import State
import serial.tools.list_ports

import asyncio
from websockets.server import serve

arduino = serial.Serial()
arduino.baudrate = 57600
arduino.port = '/dev/cu.usbmodem101'
state = State.State(2, 1, 4)

def getPorts():
    ports = []
    for port in serial.tools.list_ports.comports():
        ports.append(port.name)
    return ports

async def handler(websocket):
    
    async for message in websocket:
        print(message)
        data = json.loads(message)
        for command in data:
            match command["type"]:
                case "open":
                    arduino.port = command["port"]
                    arduino.baudrate = command["baud"]
                    if not arduino.is_open:
                        arduino.open()
                case "close":
                    if arduino.is_open:
                        arduino.close()
                case "getSerial":
                    await websocket.send(json.dumps({"type":"serialState", "open":arduino.is_open, "port":arduino.port, "baud":arduino.baudrate}))
                case "getPorts":
                    data = json.dumps({
                            'type' :'ports',
                            'value' : getPorts()
                        })
                    await websocket.send(data)
                case "motor":
                    state.motors[command["index"]-1].speed = command["value"]
                case "stepper":
                    state.steppers[command["index"]-1].position = command["value"]
                case "servo":
                    state.servos[command["index"]].position = command["value"]
                case "setAll":
                    state.updateAll(command["value"])
        
        if arduino.is_open:
            arduino.write(state.generate().encode())

async def main():
    async with serve(handler, "0.0.0.0", 8765):
        await asyncio.Future()  # run forever

asyncio.run(main())
