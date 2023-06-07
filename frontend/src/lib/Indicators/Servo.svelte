<script lang="ts">
    /**Handle servo interactions
     * 
     * Stores the current angle and enable state of the servo.
     * Manages how the servo handles user inputs
    */

    // dependencies
    import { state, type Servo } from '../stores/devices'
    import Switch from '../Components/Switch.svelte'

    // get servo from global servo array
    export let index: number
    let servo: Servo = $state.servos[index]

    // update state store with new servo values
    const update = () => {
        state.updateServo(index, servo)
    }
</script>

<div class="servo">
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
</div>