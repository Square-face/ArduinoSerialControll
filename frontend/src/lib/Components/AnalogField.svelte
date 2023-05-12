<script lang="ts">
    export let gamepad: any
    export let index: number
</script>

<input type="range" min="-1" max="1" step="0.1" bind:value={gamepad.axes[index]}>