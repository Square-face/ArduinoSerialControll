<script lang="ts">
    import Message from "./message.svelte";
    import { messages } from "../stores/messages";

</script>

<div class="messages">
    {#each $messages as message, index}
    {#if !message.showed}
    <Message {index}/>
    {/if}
    {/each}
</div>

<style>
    div.messages {
        position: fixed;
        bottom: 0;
        left: 0;
        width: 100%;
        pointer-events: none;
        display: flex;
        flex-direction: column;
        align-items: center;
        gap: 0.3em;
    }
</style>