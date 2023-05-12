<script lang="ts">

    export let value: boolean
    export let index: number

</script>

<span class="digital-field" class:enabled={value}>{index}</span>

<style lang="scss">
    span.digital-field {
        width: fit-content;
        padding: 0.5em;
        margin: 0.2em;
        border-radius: 0.5em;
        background-color: red;
        &.enabled {
            background-color: green;
        }
    }
</style>