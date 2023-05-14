<script lang="ts">
    export let value: number
    export let index: number
</script>

<input type="range" min="-1" max="1" step="0.01" bind:value>