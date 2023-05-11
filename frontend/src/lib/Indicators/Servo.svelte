<script lang="ts">
    export let index: number

    import { state, keybinds, type servo, type, targetType } from '../stores'
    import Switch from '../Components/Switch.svelte';

    const avg = (numbers: number[]) => {
        var total = 0;
        for(var i = 0; i < numbers.length; i++) {
            total += numbers[i];
        }
        return total / numbers.length;
    }

    let servo: servo;
    let keybindPositions:number[] = []
    let keybindEnabled:boolean[] = []
    state.subscribe(state => servo=state.servos[index])
    keybinds.subscribe(keybinds => {
        keybindPositions = []
        keybindEnabled = []
        keybinds.activeKeybinds.forEach((keybind, _, __)=>{
            if (keybind.type != type.Servo){return}
            if (keybind.id != index) {return}
            switch(keybind.targetType) {
                case (targetType.position):
                    keybindPositions.push(keybind.value)
                case (targetType.enabled):
                    keybindEnabled.push(keybind.value)
            }

        })
        if (keybindPositions.length > 0){
            servo.position = avg(keybindPositions)
        }
    })

    const update = () => {
        state.updateServo(index, servo)
    }

</script>

<h2>Servo {index+1}</h2>
<Switch bind:value={servo.enabled} onChange={update}/>
<input
    type="range"
    name="ServoPositionSlider"
    id="Servo{index}PositionSlider"
    min="0"
    max="180"
    on:change={update}
    bind:value={servo.position}
>
<input type="number" name="ServoPositionInput" id="Servo{index}PositionInput" bind:value={servo.position}>