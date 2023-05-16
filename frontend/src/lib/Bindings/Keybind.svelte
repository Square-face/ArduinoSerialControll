<script lang="ts">
    import AddDigitalTarget from './addDigitalTarget.svelte';
    import {type Keybind} from '../stores/bindings'
    export let keybind: Keybind
</script>

<div class="keybind">
    <span>{keybind.keyCode}</span>
    <div class="targets">
        {#each keybind.targets as target}
            <div class="fields target">
                <span class="field" data-field-name="Device">{target.device}</span>
                <span class="field" data-field-name="Field">{target.field}</span>
                <span class="field" data-field-name="Index">{target.index}</span>
                <span class="field" data-field-name="Inverted">{target.inverted}</span>
                <span class="field" data-field-name="Toggle">{target.toggle}</span>
                <span class="field" data-field-name="Value">{target.value}</span>
            </div>
        {/each}
        <AddDigitalTarget />
    </div>
</div>

<style lang="scss">
    div.fields {
        display: grid;
        gap: 0.2em;
        grid-template-rows: auto auto auto;
        grid-template-columns: 50% 50%;
        span.field {
            padding: 1.2em 0.6em 0.4em;
            background: rgba(255,255,255,0.1);
            border-radius: 0.2em;
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: row;
            position: relative;

            &::before {
                content: attr(data-field-name);
                position: absolute;
                top: 0.2em;
                left: 1em;
                font-size: 9px;
            }
        }
    }
</style>