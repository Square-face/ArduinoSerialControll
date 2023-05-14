<script lang="ts">
    import Message from "./message.svelte";
    import { messages } from "../stores/messages";

</script>

<div class="messages">
    {#each $messages as message, index}
    {#if !message.showed}
    <Message bind:message={$messages[index]}/>
    {/if}
    {/each}
</div>