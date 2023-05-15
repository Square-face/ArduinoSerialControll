<script lang="ts">
    /**Manages the WebSocket connection to the backend
     * 
     * Relays changes made in the ui to the backend for them to be sent over to the arduino.
     * 
    */

    // dependencies
    import { state } from './stores/devices'
    import { ports, serial, host, port } from './stores/connection'
    import { messages, importance } from './stores/messages'
    import Switch from './Components/Switch.svelte';

    let autorefresh = false
    let socket = new WebSocket(`ws://${$host}:${$port}/`)
    let data = {};

    let connected = false
    let statusMessage = "Connecting..."

    state.subscribe(state => {data = state})
    serial.subscribe(data => {
        if (!data.waiting) {return}
        if (!connected) {return}

        let cmd = {
            type: data.open ? "open" : "close",
            baud: data.baud,
            port: data.port,
        }
        socket.send(JSON.stringify([cmd]))
        serial.update(serial => {
            serial.waiting = false
            return serial
        })
    })

    const websocketSet = () => {

        socket.onopen = () => {
            console.log("opened")
            connected = true
            statusMessage = "Connected"
            socket.send(JSON.stringify([{type:"getPorts"},{type:"getSerial"}]))
        }
        
        socket.onclose = () => {
            messages.createMessage("Socket closed", "Websocket connection closed", 6.0, importance.ERROR)
            connected = false
            statusMessage = "Closed"
        }

        socket.onmessage = event => {
            console.log(event.data.toString())
            let data = JSON.parse(event.data.toString())

            switch (data.type) {
                case "fullState":
                    let jsonState = data.value
                    state.set(jsonState)
                    break
                case "ports":
                    ports.set(data.value)
                    break
                case "serialState":
                    serial.update(serial => {
                        serial.baud = data.baud
                        serial.port = data.port
                        serial.open = data.open
                        return serial
                    })
            }
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
        ws://<input type="text" bind:value={$host}>:<input type="number" bind:value={$port}>/
    </div>
    <div class="field connection-state" id="websocket-state" data-field-name="Status">{statusMessage}</div>
    <div class="field websocket-btn" id="websocket-connect-btn" data-field-name="Connect Websocket">
        <button on:click={connect}>{connected ? "Disconnect" : "Connect"}</button>
    </div>
    <div class="field autorefresh" id="autorefresh" data-field-name="Auto Refresh">
        <Switch bind:value={autorefresh} onChange={()=>{}}/>
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

    input[type=number] {
        width: 100%;
        border: none;
        outline: none;
        padding: 0.1em 0.2em;
        background-color: rgba(0,0,0,0.2);
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
            padding: 1.2em 0.6em 0.4em;
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

            &#refreshrate {
                border-radius: 0.2em 0.2em 0.2em 0.5em;
            }

            &#autorefresh {
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