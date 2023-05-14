<script lang="ts">
    /**Handle motor interactions
     * 
     * Stores the current motor speed
     * Manages how the motor behaves from different inputs
    */
    
    // dependencies
    import { state, type motor } from '../stores'
    
    // get this motor from global motor array
    export let index: number
    var motor: motor = $state.motors[index];


    // update global state with new motor values
    const update = () => {
        state.updateMotor(index, motor)
    }
</script>

<div class="motor">
    <h2>Motor {index+1}</h2>
    <input
        type="range"
        name="MotorSpeedSlider"
        id="Motor{index}SpeedSlider"
        min="-255"
        max="255"
        on:change={update}
        bind:value={motor.speed}
    >
    <input on:change={update} type="number" name="MotorSpeedInput" id="Motor{index}SpeedInput" bind:value={motor.speed}>
</div>