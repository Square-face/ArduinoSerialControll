<script lang="ts">
    /**Handle servo interactions
     * 
     * Stores the current angle and enable state of the servo.
     * Manages how the servo handles keybind inputs
    */

    // dependencies
    import { state, keybinds, type servo, type, targetType } from '../stores'
    import { average } from '../../scripts/Numbers'
    import Switch from '../Components/Switch.svelte'

    export let index: number
    // get servo from global servo array
    let servo: servo = $state.servos[index]
    
    let keybindPositions:number[] = []
    let keybindEnabled:boolean[] = []

    keybinds.subscribe(keybinds => {
        // reset stored keybinds
        keybindPositions = []
        keybindEnabled = []
        
        keybinds.keyboard.forEach((keybind, _, __)=>{
            keybind.targets.forEach(target => {
                if (target.type != type.Servo){return}
                if (target.index != index) {return}
                switch(target.targetType) {
                    case (targetType.position):
                        keybindPositions.push(5)
                    case (targetType.enabled):
                        keybindEnabled.push(keybind.value)
                }
            });

        })
        if (keybindPositions.length > 0){
            servo.position = average(keybindPositions)
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