<script lang="ts">
    import { messages, importance } from "../stores/messages";

    export let index: number
    const message = $messages[index]

    message.showing=true

    const remove = () => {
        messages.removeMessage(index)
    }

    setInterval(remove, message.timeout*1000)
</script>

<div class="message" class:error={message.importance == importance.ERROR} class:info={message.importance == importance.INFO}>
    <span class="title">{message.title}</span>
    <span class="text">{message.message}</span>
</div>

<style lang="scss">
    div.message {
        width: 500px;
        padding: 0.2em 0.2em;
        border-radius: 0.2em;
        display: grid;
        grid-template-columns: auto 20px;
        grid-template-rows: auto auto;

        span.title {
            grid-row-start: 1;
            grid-row-end: 2;
            text-align: left;
        }
        span.text {
            grid-row-start: 2;
            grid-row-end: 3;
            grid-column-start: 1;
            grid-column-end: 3;
            text-align: left;
        }
        &.error {
            background-color: rgba(201, 23, 23, 0.764);
        }
        &.info {
            background-color: rgba(44, 201, 23, 0.881);
        }
        &.warning {
            background-color: rgba(201, 150, 23, 0.881);
        }
    }
</style>