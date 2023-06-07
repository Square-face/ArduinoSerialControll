<script lang="ts">
    /**Handle stepper interactions
     * 
     * Stores the current position and enable state
     * Manages how the stepper handles user inputs
    */

    // dependencies
    import { state, type Stepper } from '../stores/devices'
    import Switch from '../Components/Switch.svelte';

    // get current stepper from global stepper array
    export let index: number
    var stepper: Stepper = $state.steppers[index];

    // update state with new stepper values
    const update = () => {
        state.updateStepper(index, stepper)
    }
</script>

<div class="stepper">
    <h2>Stepper {index+1}</h2>
    <Switch bind:value={stepper.enabled} onChange={update}/>
    <input
        type="range"
        name="StepperPositionSlider"
        id="Stepper{index}PositionSlider"
        min="-600"
        max="600"
        on:change={update}
        bind:value={stepper.position}
    >
    <input on:change={update} type="number" name="StepperPositionInput" id="Stepper{index}PositionInput" bind:value={stepper.position}>
</div>
