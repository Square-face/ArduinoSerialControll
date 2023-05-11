<script lang="ts">
    export let index: number

    import { state, type stepper } from '../stores'
    import Switch from '../Components/Switch.svelte';

    var stepper: stepper;
    state.subscribe(state => stepper=state.steppers[index])

    const update = () => {
        state.updateStepper(index, stepper)
    }

</script>

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
