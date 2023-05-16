<script lang="ts">
    import AnalogField from "../Components/AnalogField.svelte";
    import DigitalField from "../Components/DigitalField.svelte";

    export let gamepad: Gamepad;

</script>

<div class="gamepad">
    <h3>{gamepad.id}</h3>
    <h4>Buttons</h4>
    <div class="digital-buttons">
        {#each gamepad.buttons as button, index}
            <DigitalField {index} bind:value={button.pressed}/>
        {/each}
    </div>
    <h4>Axes</h4>
    <div class="analog-axes">
        {#each gamepad.axes as axis, index}
            <AnalogField {index} {gamepad}/>
        {/each}
    </div>
</div>

<style lang="scss">
    div.gamepad {
        background-color: rgba(255,255,255,0.1);
        padding: 0.5em;
        border-radius: 0.5em;
        div.digital-buttons{
            display: flex;
            flex-direction: row;
            flex-wrap: wrap;
        }
    }
</style>