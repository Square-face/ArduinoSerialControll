<script lang="ts">

    export let index: number
    export let gamepad: Gamepad
    
</script>

<div class="axis">
    <span class="index">{index}</span>
    <input type="range" min="-1" max="1" step="0.01" bind:value={gamepad.axes[index]}>
</div>