import { writable, type Writable } from "svelte/store";

export enum Device {Motor, Servo, Stepper}
export enum Field {speed, position, enabled}

export interface DigitalTarget {
    device: Device,     // if this target is a motor, servo or stepper
    field: Field,       // what field of the device to modify
    index: number,      // the index for this target
    toggle: boolean,    // if the keybind should behave as a toggle
    inverted: boolean   // if the logical input should be inverted
    value: number | boolean // the target value or boolean
}

export interface Keybind {
    keyCode: string,    // the keycode associated with the keybind
    targets: DigitalTarget[],
}

function createKeybinds() {
    const {subscribe, set, update}: Writable<Keybind[]> = writable([])

    return {
        subscribe,
        set,
        /**Create a new keybind with no targets
         * 
         * @param keyCode the keycode for the keybind
         */
        createKeybind(keyCode: string) {
            update(keybinds => {
                keybinds.push({
                    keyCode: keyCode,
                    targets: []
                })
                console.log(keybinds)
                return keybinds
            })
        },
        /**Removes a keybind from the keybinds list
         * 
         * @param index the keybind index
         */
        removeKeybind(index: number) {
            update(keybinds => {
                keybinds.splice(index, 1)
                return keybinds
            })
        },
        /**Bind a target to a keybind
         * 
         * @param keybindIndex Index for the keybind that the target is going to be added to
         * @param device The type of device this target is
         * @param field the device field that will be affected
         * @param index The device index
         * @param toggle If the keybind should work as a toggle
         * @param inverted If the logical input should be inverted
         * @param value the value to be applied to the field of the device
         */
        addTarget(keybindIndex:number, device: Device, field: Field, index: number, toggle:boolean, inverted:boolean, value: number | boolean) {
            // validate field and device
            if (device == Device.Motor && field != Field.speed) {throw new Error("Field does not exist on device")}
            if (device != Device.Motor && field == Field.speed) {throw new Error("Field does not exist on device")}

            // validate value type
            if (field != Field.enabled && typeof value == "boolean") {throw new Error("Speed or position fields can not have a boolean value")}

            update(keybinds => {
                keybinds[keybindIndex].targets.push({
                    device: device,
                    field: field,
                    index: index,
                    toggle: toggle,
                    inverted: inverted,
                    value: value
                })
                return keybinds
            })
        },
    }
}

export const keybinds = createKeybinds()