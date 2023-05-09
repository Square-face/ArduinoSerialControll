<script lang="ts">
    export let index: number

    import { state, type motor } from '../stores'

    var motor: motor;
    state.subscribe(state => motor=state.motors[index])

    const update = () => {
        state.updateMotor(index, motor)
    }
</script>

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