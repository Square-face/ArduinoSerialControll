<script lang="ts">
  import Servo from "../Indicators/Servo.svelte";


    import { state, keybinds, type, targetType } from "../stores"


    keybinds.addAnalogKeybind({
        id: 0,
        axis: 1,
        gamepad: 0,
        value: 0,
        targets: [{
            type: type.Motor,
            targetType: targetType.speed,
            index: 0,
            absolute: true,
            inverted: true,
            inMin: -1,
            inMax: 1,
            outMin: -255,
            outMax: 255,
        },{
            type: type.Motor,
            targetType: targetType.speed,
            index: 1,
            absolute: true,
            inverted: false,
            inMin: -1,
            inMax: 1,
            outMin: -255,
            outMax: 255,
        }]
    })
    keybinds.addAnalogKeybind({
        id: 0,
        axis: 0,
        gamepad: 0,
        value: 0,
        targets: [{
            type: type.Motor,
            targetType: targetType.speed,
            index: 0,
            absolute: true,
            inverted: true,
            inMin: -1,
            inMax: 1,
            outMin: -255,
            outMax: 255,
        },{
            type: type.Motor,
            targetType: targetType.speed,
            index: 1,
            absolute: true,
            inverted: true,
            inMin: -1,
            inMax: 1,
            outMin: -255,
            outMax: 255,
        }]
    })

    document.addEventListener('keydown', event => {keybinds.pressKey(event.code)})
    document.addEventListener('keyup', event => {keybinds.unpressKey(event.code)})

</script>

<div class="keybinds">
    <h2>Keybinds</h2>
    {#each $keybinds.keyboard as keybind}
    <div class="keybind">
        <span class="keybind-id">{keybind.id}</span>
        <span class="keybind-key">{keybind.key}</span>
        <span> {keybind.value ? "active" : "passive" } </span>
        <div class="keybind-targets">
            <span>Affects</span>
            {#each keybind.targets as target}
            <div class="keybind-target">
                <span>{target.type}</span>
                <span>{target.targetType}</span>
                <span>{target.index}</span>
                <span>{target.targetValue}</span>
                <span>{target.toggle}</span>
                <span>{target.inverted}</span>
            </div>
            {/each}
        </div>
    </div>
    {/each}
    <button>Create new</button>
</div>