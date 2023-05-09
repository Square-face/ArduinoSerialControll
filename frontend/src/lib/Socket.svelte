<script lang="ts">

    import { state } from './stores'

    var host = "localhost"
    var port = 8765
    var socket = new WebSocket(`ws://${host}:${port}/`)

    var connected = false
    var statusMessage = "Connecting..."

    const websocketSet = () => {

        socket.onopen = () => {
            console.log("opened")
            connected = true
            statusMessage = "Connected"
        }
        
        socket.onclose = () => {
            console.log("closed")
            connected = false
            statusMessage = "Closed"
        }
    }
    websocketSet()
    
    function connect() {
        if (socket.readyState == 1) {
            console.log("closing websocket")
            socket.close()
        } else {
            console.log("connecting websocket")
            socket = new WebSocket(`ws://${host}:${port}/`)
            websocketSet()
        }
    }

</script>

<div class="fields socket">
    <h2 class="header">Websocket</h2>
    <div class="field" id="adress" data-field-name="Adress">
        ws://<input type="text" name="host" id="host" bind:value={host}>:<input type="number" name="port" id="port" bind:value={port}>/
    </div>
    <div class="field connection-state" id="websocket-state" data-field-name="Status">{statusMessage}</div>
    <div class="field" id="websocket-connect-btn" data-field-name="Connect Websocket">
        <button on:click={connect}>{connected ? "Disconnect" : "Connect"}</button>
    </div>
    
    <div id="output"></div>
</div>

<style lang="scss">

    button {
        border: none;
        padding: 0.5em 0.7em;
        border-radius: 0.5em;
        background-color: rgba(0,0,0,0.2);
        &:hover {
            outline: solid 1px rgb(0, 242, 255);
        }
        &:active {
            background-color: rgba(0,0,0,0.3);
        }
    }

    div.socket {
        display: flex;
        flex-direction: column;
    }
    div.fields {
        display: grid;
        gap: 0.2em;
        grid-template-rows: auto auto auto;
        grid-template-columns: 50% 50%;
        h2.header {
            grid-column-start: 1;
            grid-column-end: 3;
            margin: 0;
        }
        div.field {
            padding: 1em 0.6em 0.4em;
            background: rgba(255,255,255,0.1);
            border-radius: 0.2em;
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: row;
            position: relative;
            
            &#adress {
                grid-column-start: 1;
                grid-column-end: 3;
                border-radius: 0.5em 0.5em 0.2em 0.2em;
            }

            &#websocket-state {
                border-radius: 0.2em 0.2em 0.2em 0.5em;
            }

            &#websocket-connect-btn {
                border-radius: 0.2em 0.2em 0.5em 0.2em;
            }

            &::before {
                content: attr(data-field-name);
                position: absolute;
                top: 0.2em;
                left: 1em;
                font-size: 9px;
            }
        }
    }
    
    div#adress {
        position: relative;
        input {
            padding: 1px 2px;
            margin: 0;
            border: none;
            border-radius: 2px;
            background-color: rgba(0,0,0,0.2);
            color: rgb(0, 242, 255);
            transition: width 0.25s;
            min-width: 10px;
            max-width: 100%;
            &#host {
                width: 10em;
            }
            &#port {
                width:2.5em;
                -moz-appearance: textfield;
                appearance: textfield;
                &::-webkit-inner-spin-button {
                    -webkit-appearance: none;
                }
            }
        }

    }
</style>