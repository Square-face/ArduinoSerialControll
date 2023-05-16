<script lang="ts">
    import Gamepad from "./Gamepad.svelte";
    import { gamepads } from "../stores/gamepads";
    import { messages, importance } from "../stores/messages";

    const pollRates = [10, 50, 100, 150, 200, 250]
    let pollRate = 100

    window.onload = () => {
        if (!("getGamepads" in navigator)) {
            messages.createMessage("Gamepads not supported", "This browser does not support gamepads. Consider updating or switching browser.", 10, importance.WARNING)
            return;
        }
    }

    window.ongamepadconnected = event => {
        messages.createMessage("Gamepad connected", "New gamepad device detected", 5.0, importance.INFO)
        gamepads.update(gamepads => {gamepads.push(event.gamepad); return gamepads})
    }

    function pollGamepads() {
        $gamepads = navigator.getGamepads()
    }

    setInterval(pollGamepads, 1000/pollRate)
</script>

<div class="gamepads">
    <label for="gamepad-poll-rate">Poll Rate</label>
    <select id="gamepad-poll-rate" bind:value={pollRate}>
        {#each pollRates as pollRate}
        <option value="{pollRate}">{pollRate}</option>
        {/each}
    </select>
    {#each $gamepads as gamepad}
        <Gamepad bind:gamepad />
    {/each}
</div>

<style>
    div.gamepads {
        display: flex;
        flex-wrap: wrap;
        justify-content: center;
        gap: 1em;
        margin-top: 1em;
    }
</style>