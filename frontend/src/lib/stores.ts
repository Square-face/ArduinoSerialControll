import { writable } from "svelte/store";

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
            {position: 0, enabled: false},
            {position: 0, enabled: false},
            {position: 0, enabled: false},
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

export interface target {
    type: type,
    targetType: targetType,
    index: number,
    targetValue: number | boolean,
    toggle: boolean,
    inverted: boolean,
}
export interface keybind {
    id: number,
    key: string
    targets: target[]
}

function createKeybinds() {
    const { subscribe, set, update } = writable({
        keybinds: [],
        activeKeybinds: [],
    })

    return {
        subscribe: subscribe,
        pressKey: (key: string) => {
            // when a key is pressed, add all asosciated keybinds to active keybinds

            update(keybinds => {

                for (let i = 0; i<keybinds.keybinds.length; i++) {
                    let keybind = keybinds.keybinds[i]
                    
                    if (keybind.key != key) {continue}
                    
                    if (keybinds.activeKeybinds.includes(keybind)) {continue}
                    keybinds.activeKeybinds.push(keybind)
                }
                return keybinds
            })
        },
        unpressKey: (key: string) => {
            // when a key is unpressed, remove all asosciated keybinds from active keybinds
            
            update(keybinds => {
                for (let i = 0; i<keybinds.activeKeybinds.length; i++) {
                    let keybind = keybinds.activeKeybinds[i]
                    
                    if (keybind.key != key) {continue}
                    
                    keybinds.activeKeybinds.splice(i, 1)
                }
                return keybinds
            })
        },
        addkeybind: (keybind: keybind) => {
            // add a new keybind to the keybinds array

            update(keybinds => {
                keybinds.keybinds.push(keybind)
                return keybinds
            })
        
        },
        removekeybind: (id: number) => {
            // remove a keybind from the keybinds array

            update(keybinds => {
                for (let i = 0; i<keybinds.keybinds.length; i++) {
                    let keybind = keybinds.keybinds[i]
                    
                    if (keybind.id != id) {continue}
                    
                    keybinds.keybinds.splice(i, 1)
                }
                return keybinds
            })
        },
    }
}

export const keybinds = createKeybinds()