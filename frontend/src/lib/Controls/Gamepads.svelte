<script lang="ts">
    import Gamepad from "./Gamepad.svelte";
    import { gamepads } from "../stores/gamepads";

    window.onload = () => {
        if (!("getGamepads" in navigator)) {
            alert("Browser does not support gamepads")
            return;
        }
        
        $gamepads = navigator.getGamepads()
        console.log("fetched gamepads")
        console.log($gamepads)
    }

    window.ongamepadconnected = event => {
        console.log("gamepad connected")
        gamepads.update(gamepads => {gamepads.push(event.gamepad); return gamepads})
    }
</script>

<div class="gamepads">
    {#each $gamepads as gamepad}
        <Gamepad bind:gamepad />
    {/each}
</div>