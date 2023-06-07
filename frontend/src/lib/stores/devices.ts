import { writable, type Writable } from "svelte/store";

export interface Entry {
    keybindIndex: number
    targetIndex: number
    value: number | boolean
}

export interface Motor {
    speed: number,
    entries: Entry[],
}
export interface Servo {
    position: number,
    enabled: boolean,
    entries: Entry[],
}
export interface Stepper {
    position: number,
    enabled: boolean,
    entries: Entry[],
}
export interface State {
    motors: Motor[]
    servos: Servo[]
    steppers: Stepper[]
}

function createState() {

    const { subscribe, set, update }: Writable<State> = writable({
        motors: [
            {speed: 0, entries: []},
            {speed: 0, entries: []},
        ],
        servos: [
            {position: 0, enabled: false, entries: []},
            {position: 0, enabled: false, entries: []},
            {position: 0, enabled: false, entries: []},
            {position: 0, enabled: false, entries: []},
        ],
        steppers: [
            {position: 0, enabled: false, entries: []},
        ],
    })

    return {
        subscribe,
        set,
        update,
        updateServo:    (index: number, servo: Servo)       => update(state => {state.servos[index]     = servo;    return state}),
        updateStepper:  (index: number, stepper: Stepper)   => update(state => {state.steppers[index]   = stepper;  return state}),
        updateMotor:    (index: number, motor: Motor)       => update(state => {state.motors[index]     = motor;    return state}),
    }
}

export const state = createState()