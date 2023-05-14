import { writable, type Writable } from "svelte/store";

export interface gamepad {

}

function createGamepads() {
    const {subscribe, set, update}: Writable<Gamepad[]> = writable([])
    return {
        subscribe,
        set,
        update
    }
}

export const gamepads = createGamepads()