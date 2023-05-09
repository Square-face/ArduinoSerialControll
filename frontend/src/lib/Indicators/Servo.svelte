<script lang="ts">
    export let index: number

    import { state, type servo } from '../stores'

    var servo: servo;
    state.subscribe(state => servo=state.servos[index])

    const update = () => {
        state.updateServo(index, servo)
    }

</script>

<h2>Servo {index+1}</h2>
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