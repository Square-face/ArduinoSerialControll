<script lang="ts">
    import { type message } from "../stores/messages";

    export let message: message

    message.showing=true

    const remove = () => {
        message.showed=true
        message.showing=false
    }

    setInterval(remove, message.timeout*1000)
</script>

<div class="message" style:--color:{() => {
return `rgb(${message.color.red},${message.color.green},${message.color.green})`
}}>
    <span class="title">{message.title}</span>
    <span class="text">{message.message}</span>
</div>