import { writable } from "svelte/store";

export interface motor {
    speed: number,
}
export interface servo {
    position: number,
    enabled: boolean,
}
export interface stepper {
    position: number,
    enabled: boolean,
}
export interface State {
    motors: motor[]
    servos: servo[]
    steppers: stepper[]
}

function createState() {
    const { subscribe, set, update } = writable({
        motors: [
            {speed: 0},
            {speed: 0},
        ],
        servos: [
            {position: 0, enabled: false},
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

// Websocket

// Get saved host from local storage or use the default fallback
export const host = writable(localStorage.host || 'localhost')
host.subscribe(value => localStorage.host = value)

// Get saved port from local storage or use the default fallback
export const port = writable(localStorage.port || '8080')
port.subscribe(value => localStorage.port = value)

export const ports = writable([])
export const serial = writable({
    open: false,
    port: null,
    baud: null,
    waiting: false,
})
