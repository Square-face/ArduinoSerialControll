<script lang="ts">
    var serial_ports = ["test", "test2"]
    var serial_port:string

    var serial_baudrates = ["test", "test2"]
    var serial_baudrate:string = "test"
</script>

<div class="fields serial">
    <h2 class="header">Serial</h2>

    <div class="field serial" id="serial-port" data-field-name="Port">
        <select name="serial port" bind:value={serial_port}>
            {#each serial_ports as port}
            <option value="{port}">{port}</option>
            {/each}
        </select>

    </div>
    <div class="field serial" id="serial-baud" data-field-name="Baudrate">
        <select name="serial baud" bind:value={serial_baudrate}>
            {#each serial_baudrates as baudrate}
            <option value="{baudrate}">{baudrate}</option>
            {/each}
        </select>
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
            padding: 1em 0.6em 0.4em;
            background: rgba(255,255,255,0.1);
            border-radius: 0.2em;
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: row;
            position: relative;

            &#serial-port {
                border-radius: 0.5em 0.2em 0.2em 0.5em;
            }
            &#serial-baud {
                border-radius: 0.2em 0.5em 0.5em 0.2em;
            }
            &::before {
                content: attr(data-field-name);
                position: absolute;
                top: 0;
                left: 1em;
                font-size: 9px;
            }
        }
    }

</style>