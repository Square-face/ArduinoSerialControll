<script lang="ts">

    export let value: boolean
    export let index: number

</script>

<span class="digital-field" class:enabled={value}>{index}</span>

<style lang="scss">
    span.digital-field {
        width: 2em;
        height: 2em;
        border-radius: 0.2em;
        margin: 0.1em;
        background-color: rgba(255,255,255,0.1);
        display: flex;
        align-items: center;
        justify-content: center;
        &.enabled {
            background-color: green;
        }
    }
</style>