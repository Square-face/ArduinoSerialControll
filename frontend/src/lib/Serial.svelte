<script lang="ts">
    import { ports, serial } from './stores/connection'
    import Switch from './Components/Switch.svelte';

    let open: boolean = false;
    let serial_ports = []
    let port: string;

    ports.subscribe(ports => {
        serial_ports = []
        for (let i = 0; i<ports.length;i++) {
            console.log({id:i.toString(), value:"/dev/"+ports[i]})
            serial_ports.push({id:i.toString(), value:"/dev/"+ports[i]})
        }
    })

    var serial_baudrates = [300, 600, 750, 1200, 2400, 4800, 9600, 19200, 31250, 38400, 57600, 74880, 115200, 230400, 250000, 460800, 500000, 921600, 1000000, 2000000]
    let baudrate: number;
    serial.subscribe(serial => {
        for (let i = 0; i<serial_ports.length; i++) {
            if (serial_ports[i].value == serial.port) {
                port = i.toString()
            }
        }
    })
    const update = () => {
        serial.set({
            open: open,
            port: serial_ports[Number(port)].value,
            baud: baudrate,
            waiting: true,
        })
    }
</script>

<div class="fields serial">
    <h2 class="header">Serial</h2>

    <div class="field serial" id="serial-port" data-field-name="Port">
        <select name="serial port" bind:value={port}>
            {#each serial_ports as port}
                <option value="{port.id}">{port.value}</option>
            {/each}
        </select>

    </div>
    <div class="field serial" id="serial-baud" data-field-name="Baudrate">
        <select name="serial baud" bind:value={baudrate}>
            {#each serial_baudrates as baudrate}
            <option value="{baudrate}">{baudrate}</option>
            {/each}
        </select>
    </div>
    <div class="field State" id="serial-state" data-field-name="State">
        {open ? "Open" : "Closed"}<Switch bind:value={open} onChange={update}/>
    </div>
</div>

<style lang="scss">
    div.fields {
        display: grid;
        gap: 0.2em;
        grid-template-rows: auto auto;
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

            &#serial-port {
                grid-column-start: 1;
                grid-column-end: 3;
                border-radius: 0.5em 0.5em 0.2em 0.0em;
            }
            &#serial-baud {
                border-radius: 0.2em 0.2em 0.2em 0.5em;
            }
            &#serial-state {
                border-radius: 0.2em 0.2em 0.5em 0.2em;
            }
            &::before {
                content: attr(data-field-name);
                position: absolute;
                top: 0.2em;
                left: 1em;
                font-size: 9px;
            }

            select {
                border: none;
                outline: none;
                background-color: rgba(0,0,0,0.2);
                width: 100%;
            }
        }
    }

</style>