import { writable, type Writable } from "svelte/store";

export interface motor {
    speed: number,
    manualSpeed: number,
}
export interface servo {
    position: number,
    manualPosition: number,
    enabled: boolean,
    manualEnabled: boolean,
}
export interface stepper {
    position: number,
    manualPosition: number,
    enabled: boolean,
    manualEnabled: boolean,
}
export interface State {
    motors: motor[]
    servos: servo[]
    steppers: stepper[]
}

function createState() {
    const { subscribe, set, update } = writable({
        motors: [
            {speed: 0, manualSpeed: 0},
            {speed: 0, manualSpeed: 0},
        ],
        servos: [
            {position: 0, manualPosition: 0, enabled: false, manualEnabled: false},
            {position: 0, manualPosition: 0, enabled: false, manualEnabled: false},
            {position: 0, manualPosition: 0, enabled: false, manualEnabled: false},
            {position: 0, manualPosition: 0, enabled: false, manualEnabled: false},
        ],
        steppers: [
            {position: 0, enabled: false},
        ],
    })

    return {
        subscribe,
        set,
        update,
        updateServo:    (index: number, servo: servo)       => update(state => {state.servos[index]     = servo;    return state}),
        updateStepper:  (index: number, stepper: stepper)   => update(state => {state.steppers[index]   = stepper;  return state}),
        updateMotor:    (index: number, motor: motor)       => update(state => {state.motors[index]     = motor;    return state}),
    }
}

export const state = createState()

export const ports = writable([])
export const serial = writable({
    open: false,
    port: null,
    baud: null,
    waiting: false,
})

export enum type {Motor, Servo, Stepper}
export enum targetType {speed, position, enabled}

export interface digitalTarget {
    type: type,
    targetType: targetType,
    index: number,
    targetValue: number | boolean,
    toggle: boolean,
    inverted: boolean,
}

export interface analogTarget {
    type: type,
    targetType: targetType,
    index: number,
    absolute: boolean,
    inverted: boolean,
    inMin: number,
    inMax: number,
    outMin: number,
    outMax: number,
}

export interface keyboardKeybind {
    id: number,
    key: string,
    value: boolean,
    targets: digitalTarget[]
}

export interface digitalKeybind {
    id: number,
    gamepad: number,
    button: number,
    value: boolean,
    targets: digitalTarget[]
}

export interface analogKeybind {
    id: number,
    gamepad: number,
    axis: number,
    value: number,
    targets: analogTarget[]
}

interface keybind {
    keyboard: keyboardKeybind[],
    digital: digitalKeybind[],
    analog: analogKeybind[],
}

interface gamepad {
    id: string,
    index: number,
    gamepad: Gamepad,
    connected: boolean,
    saved: boolean,
    axes: number[]
}

const getAxes = (gamepad:Gamepad) => {
    let axes = []
    gamepad.axes.forEach(axis => axes.push(axis))
    return axes
}

function createGamepads() {
    const init:gamepad[] = []
    const {subscribe, set, update} = writable(init)

    return {
        subscribe, set, update,
        updateGamepad: (gamepad: Gamepad) => {
            update(gamepads => {
                gamepads[gamepad.index].gamepad = gamepad
                return gamepads
            })
        },
        updateAxes: (index:number) => {
            update(gamepads => {
                gamepads[index].axes = getAxes(gamepads[index].gamepad)
                return gamepads
            })
        },
        connectGamepad: (gamepad: Gamepad)=>{
            update(gamepads => {
                let connectedBefore = false
                console.log(gamepad)
                console.log(gamepads)
                gamepads.forEach((savedGamepad, index) => {
                    if (gamepad.index != savedGamepad.index) {return}
                    gamepads[index].connected = true
                    connectedBefore = true
                });
                console.log(connectedBefore)
                if (!connectedBefore) {
                    gamepads.push({
                        id: gamepad.id,
                        index: gamepad.index,
                        gamepad: gamepad,
                        connected: true,
                        saved: false,
                        axes: getAxes(gamepad)
                    })
                }
                return gamepads
            })
        },
        disconnectGamepad: index=>{
            update(gamepads => {
                gamepads.forEach((savedGamepad, index) => {
                    if (index == savedGamepad.index) {}
                    gamepads[index].connected = false
                });

                return gamepads
            })
        },
    }
}

export const gamepads = createGamepads()

function createKeybinds() {
    const initKeybinds: keybind = {
        keyboard: [],
        digital: [],
        analog: [],
    }
    const { subscribe, set, update } = writable(initKeybinds)

    return {
        subscribe: subscribe,
        getNextId: ()=> {
            let testId = 0;
            for (let i = 0; i<$keybinds.keyboard.length; i++) {
                let keybind = $keybinds.keyboard[i]
                if (keybind.id == testId) {
                    testId++
                }
            }
        },
        pressKey: (key: string) => {
            // when a key is pressed, set the asosciated keybind to active

            update(keybinds => {

                for (let i = 0; i<keybinds.keyboard.length; i++) {
                    let keybind = keybinds.keyboard[i]
                    
                    if (keybind.key != key) {continue}
                    
                    keybinds.keyboard[i].value = true
                }
                return keybinds
            })
        },
        unpressKey: (key: string) => {
            // when a key is unpressed, set the asosciated keybind to not active
            
            update(keybinds => {
                for (let i = 0; i<keybinds.keyboard.length; i++) {
                    let keybind = keybinds.keyboard[i]
                    
                    if (keybind.key != key) {continue}
                    
                    keybinds.keyboard[i].value = false
                }
                return keybinds
            })
        },
        pressButton: (gamepadIndex: number, index: number)=>{
            // when a button is pressed, set the asosciated keybind to active

            update(keybinds => {

                for (let i = 0; i<keybinds.digital.length; i++) {
                    let keybind = keybinds.digital[i]
                    
                    if (keybind.gamepad != gamepadIndex) {continue}
                    if (keybind.button != index) {continue}
                    
                    keybinds.digital[i].value = true
                }
                return keybinds
            })
        },
        unpressButton: (gamepadIndex: number, index: number)=>{
            // when a button is un pressed, set the asosciated keybind to not active

            update(keybinds => {

                for (let i = 0; i<keybinds.digital.length; i++) {
                    let keybind = keybinds.digital[i]
                    
                    if (keybind.gamepad != gamepadIndex) {continue}
                    if (keybind.button != index) {continue}
                    
                    keybinds.digital[i].value = false
                }
                return keybinds
            })
        },
        setAnalogValue: (gamepadIndex: number, axis: number, value: number) => {
            update(keybinds => {

                for (let i = 0; i<keybinds.analog.length; i++) {
                    let keybind = keybinds.analog[i]

                    if (keybind.gamepad != gamepadIndex) {continue}
                    if (keybind.axis != axis) {continue}

                    keybind.value = value
                }
                return keybinds
            })
        },
        addKeyboardKeybind: (keybind: keyboardKeybind) => {
            // add a new keybind to the keybinds array

            update(keybinds => {
                keybinds.keyboard.push(keybind)
                return keybinds
            })
        
        },
        removeKeyboardKeybind: (id: number) => {
            // remove a keybind from the keybinds array

            update(keybinds => {
                for (let i = 0; i<keybinds.keyboard.length; i++) {
                    let keybind = keybinds.keyboard[i]
                    
                    if (keybind.id != id) {continue}
                    
                    keybinds.keyboard.splice(i, 1)
                }
                return keybinds
            })
        },
        addDigitalKeybind: (keybind: digitalKeybind) => {
            // add a new digital keybind to the keybinds array

            update(keybinds => {
                keybinds.digital.push(keybind)
                return keybinds
            })
        
        },
        removeDigitalKeybind: (id: number) => {
            // add a new digital keybind to the keybinds array

            update(keybinds => {
                for (let i = 0; i<keybinds.digital.length; i++) {
                    let keybind = keybinds.digital[i]
                    
                    if (keybind.id != id) {continue}
                    
                    keybinds.digital.splice(i, 1)
                }
                return keybinds
            })
        
        },
        addAnalogKeybind: (keybind: analogKeybind) => {
            // add a new digital keybind to the keybinds array

            update(keybinds => {
                keybinds.analog.push(keybind)
                return keybinds
            })
        
        },
        removeAnalogKeybind: (id: number) => {
            // add a new digital keybind to the keybinds array

            update(keybinds => {
                for (let i = 0; i<keybinds.analog.length; i++) {
                    let keybind = keybinds.analog[i]
                    
                    if (keybind.id != id) {continue}
                    
                    keybinds.analog.splice(i, 1)
                }
                return keybinds
            })
        
        },
    }
}

export const keybinds = createKeybinds()