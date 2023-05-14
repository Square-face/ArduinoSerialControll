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