<script lang="ts">
    export let index: number

    import { state, type stepper } from '../stores'

    var stepper: stepper;
    state.subscribe(state => stepper=state.steppers[index])

    const update = () => {
        state.updateStepper(index, stepper)
    }

</script>

<h2>Stepper {index+1}</h2>
<input
    type="range"
    name="StepperPositionSlider"
    id="Stepper{index}PositionSlider"
    min="-600"
    max="600"
    on:change={update}
    bind:value={stepper.position}
>
<input type="number" name="StepperPositionInput" id="Stepper{index}PositionInput" bind:value={stepper.position}>