<script lang="ts">
    import { keybinds } from "../stores/bindings";
    import { messages, importance } from "../stores/messages"

    let creating = false

    window.onkeydown = (event: KeyboardEvent) => {
        if (!creating) {return}
        keybinds.createKeybind(event.code)
        creating = false
        messages.createMessage(
            "New keybind created",
            "A new keyboard binding has been created",
            3.0,
            importance.INFO
        )
    }
</script>

{#if creating}
<span>Press a key</span>
{:else}
<button on:click={()=>{creating=true}}>Add new keyboard binding</button>
{/if}