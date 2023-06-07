<script lang="ts">
	import Switch from './../Components/Switch.svelte';
    import { keybinds, Device, Field } from "../stores/bindings";
    import { state } from '../stores/devices';

    export let index: number

    let addingTarget = false
    let toggle = false
    let inverted = false
    let device = null
    let indexes = []
    let deviceIndex = 0
    let fields = []
    let field = null
    let value = 0;

    function generateArray(n: number): number[] {
        let list = []
        for (let i = 1; i <= n; i++) {
            list.push(i);
        }
        return list
    }

    function setFields() {
        if (device == null) {
            indexes = []
            fields = []
            field = null
        }
        else if (device == Device.Motor) {
            indexes = generateArray($state.motors.length)
            fields = [{
                name: "Speed",
                value: Field.speed
            }]
            field = Field.speed
        }
        else {
            if (device = Device.Servo) {indexes = generateArray($state.servos.length)}
            if (device = Device.Stepper) {indexes = generateArray($state.steppers.length)}

            fields = [{
                name: "Position",
                value: Field.position
            },
            {
                name: "Enabled",
                value: Field.enabled
            }]
            if (field == Field.speed) {
                field = Field.position
            }
        }
    }

    function addTarget() {
        keybinds.addTarget(index, device, field, deviceIndex, toggle, inverted, value)
        addingTarget = false
    }

</script>
{#if addingTarget}
<div class="add-target">
    <h3>Add target</h3>
    <span>Toggle</span>
    <Switch bind:value={toggle} onChange={()=>{}}/>
        <span>Inverted</span>
    <Switch bind:value={inverted} onChange={()=>{}}/>
    <label for="device">Device</label>
    <select name="device" id="device" bind:value={device} on:change={setFields}>
        <option value="{Device.Motor}">Motor</option>
        <option value="{Device.Servo}">Servo</option>
        <option value="{Device.Stepper}">Stepper</option>
    </select>
    <select name="deviceIndex" id="device-index" bind:value={deviceIndex}>
        {#each indexes as index}
            <option value="{index}">{index}</option>
        {/each}
    </select>
    <label for="field">Field</label>
    <select name="field" id="field" bind:value={field}>
        {#each fields as field}
        <option value="{field.value}">{field.name}</option>
        {/each}
    </select>
    {#if (field in [Field.enabled, null])}
        <label for="value">Value</label>
        <input id="value" type="number" bind:value>
    {/if}
    {#if (field != null)}
    <button on:click={addTarget}>Add Target</button>
    {/if}
    
</div>
{:else}
<button on:click={()=>{addingTarget=true}}>Add Target</button>
{/if}

<style lang="scss">
    div.add-target {
        display: flex;
        flex-direction: column;
        align-items: center;
    }
</style>