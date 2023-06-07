<script lang="ts">
	import { state, type Entry, type Motor, type Servo, type Stepper } from '../stores/devices';
    import { Device, Field, keybinds } from "../stores/bindings";
    export let keybindIndex: number
    export let targetIndex: number
    let target = $keybinds[keybindIndex].targets[targetIndex]
    let toggleKeyReleased: boolean = true

    const device = () => {
        switch(target.device) {
            case Device.Motor: return "Motor"
            case Device.Servo: return "Servo"
            case Device.Stepper: return "Stepper"
        }
    }

    const field = () => {
        switch(target.field) {
            case Field.speed: return "Speed"
            case Field.position: return "Position"
            case Field.enabled: return "Enabled"
        }
    }

    function indexesIn(array: Entry[], keybindIndex: number, targetIndex: number): number {
        let index = -1
        array.forEach((entry, entryIndex) => {
            if (entry.keybindIndex != keybindIndex) {return}
            if (entry.targetIndex != targetIndex) {return}
            index = entryIndex
        })
        return index
    }

    function moveEntryToLast(entryIndex: number) {
        let entry: Entry
        
        switch(target.device) {
            case Device.Motor:
                entry = $state.motors[target.index].entries[entryIndex]
                $state.motors[target.index].entries.splice(entryIndex, 1)
                $state.motors[target.index].entries.push(entry)
                break
            case Device.Servo: 
                entry = $state.servos[target.index].entries[entryIndex]
                $state.servos[target.index].entries.splice(entryIndex, 1)
                $state.servos[target.index].entries.push(entry)
                break
            case Device.Stepper: 
                entry = $state.steppers[target.index].entries[entryIndex]
                $state.steppers[target.index].entries.splice(entryIndex, 1)
                $state.steppers[target.index].entries.push(entry)
                break
        }
    }

    function removeEntry(entryIndex: number) {
        switch(target.device) {
            case Device.Motor: $state.motors[target.index].entries.splice(entryIndex, 1); break
            case Device.Servo: $state.servos[target.index].entries.splice(entryIndex, 1); break
            case Device.Stepper: $state.steppers[target.index].entries.splice(entryIndex, 1); break
        }
    }

    function addEntry(value: number | boolean) {
        switch(target.device) {
            case Device.Motor: $state.motors[target.index].entries.push({keybindIndex: keybindIndex, targetIndex:targetIndex, value:value}); break
            case Device.Servo: $state.servos[target.index].entries.push({keybindIndex: keybindIndex, targetIndex:targetIndex, value:value}); break
            case Device.Stepper: $state.steppers[target.index].entries.push({keybindIndex: keybindIndex, targetIndex:targetIndex, value:value}); break
        }
    }

    function keybindHandler(event: KeyboardEvent, logical: boolean) {
        /**Handles firing of keybind
         * 
        */
        
        // invert input if target is inverted
        if (target.inverted) {
            logical != logical
        }
        
        // get device
        let device: Motor | Servo | Stepper
        switch (target.device) {
            case Device.Motor: device = $state.motors[target.index]; break
            case Device.Servo: device = $state.servos[target.index]; break
            case Device.Stepper: device = $state.steppers[target.index]; break
        }

        // check if this keybind is alredy active
        let entryIndex = indexesIn(device.entries, keybindIndex, targetIndex)
        if (entryIndex == -1) {
            // this keybind is not previously enabled

            // add an entry for the enabled field
            if (target.field == Field.enabled) {
                addEntry(logical)
                return
            }

            // ignore if the logical value is false
            if (!logical) {return}

            // add entry
            addEntry(target.value)
            return
        }

        if (target.toggle) {
            // if toggle mode is enabled, the logical value is true and the entry alredy exists, remove the entry
            if (!logical) {return}
            removeEntry(entryIndex)
            return
        }

        removeEntry(entryIndex)
    }

    document.addEventListener('keydown', event => {
        console.log(`Key: ${event.code} was pressed`)
        // make sure the affected key is relevant
        if (event.code != $keybinds[keybindIndex].keyCode) {return}
        keybindHandler(event, true)
    })

    document.addEventListener('keyup', event => {
        console.log(`Key: ${event.code} was released`)
        // make sure the affected key is relevant
        if (event.code != $keybinds[keybindIndex].keyCode) {return}
        keybindHandler(event, false)
    })


</script>

<div class="fields target">
    <span class="field" data-field-name="Device">{device()}</span>
    <span class="field" data-field-name="Field">{field()}</span>
    <span class="field" data-field-name="Device index">{target.index}</span>
    <span class="field" data-field-name="Value">{target.value}</span>
    <span class="field" data-field-name="Toggle">{target.toggle}</span>
    <span class="field" data-field-name="Inverted">{target.inverted}</span>
</div>

<style lang="scss">
    div.fields {
        display: grid;
        gap: 0.2em;
        grid-template-rows: auto auto auto;
        grid-template-columns: 50% 50%;
        span.field {
            padding: 1.2em 0.6em 0.4em;
            background: rgba(255,255,255,0.1);
            border-radius: 0.2em;
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: row;
            position: relative;

            &::before {
                content: attr(data-field-name);
                position: absolute;
                top: 0.2em;
                left: 1em;
                font-size: 9px;
            }
        }
    }
</style>