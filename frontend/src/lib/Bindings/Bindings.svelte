<script lang="ts">
    import Keybind from './Keybind.svelte'
    import CreateKeybind from './CreateKeybind.svelte';
    import { keybinds } from '../stores/bindings'

</script>

<div class="bindings">
    <h2>Bindings</h2>
    <div class="analog"></div>
    <div class="digital"></div>
    <div class="keyboard">
        {#each $keybinds as keybind, index}
            <Keybind {index}/>
        {/each}
        <CreateKeybind/>
    </div>
</div>