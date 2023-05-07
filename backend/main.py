import serial, time, json
import State

import asyncio
from websockets.server import serve

arduino = serial.Serial(port='/dev/cu.usbserial-0001', baudrate=57600)
state = State.State(2, 1, 4)

async def handler(websocket):
    print("connected")
    async for message in websocket:
        print(message)
        data = json.loads(message)
        for command in data:
            if command["type"] == "open":
                arduino.open()
            if command["type"] == "close":
                arduino.close()
            if command["type"] == "motor":
                state.motors[command["index"]-1].speed = command["value"]
            if command["type"] == "stepper":
                state.steppers[command["index"]-1].position = command["value"]
            if command["type"] == "servo":
                print("changing servo")
                state.servos[command["index"]].position = command["value"]
        
        arduino.write(state.generate().encode())
        print(state.generate())
        await websocket.send(state.generate())

async def main():
    async with serve(handler, "localhost", 8765):
        await asyncio.Future()  # run forever

asyncio.run(main())
