<script lang="ts">
    import AddDigitalTarget from './AddDigitalTarget.svelte';
    import DigitalTarget from './DigitalTarget.svelte';
    import { keybinds } from '../stores/bindings'
    export let index: number
    let keybind = $keybinds[index]
</script>

<div class="keybind">
    <span>{keybind.keyCode}</span>
    <div class="targets">
        {#each $keybinds[index].targets as target, targetIndex}
            <DigitalTarget keybindIndex={index} {targetIndex}/>
        {/each}
        <AddDigitalTarget {index}/>
    </div>
</div>