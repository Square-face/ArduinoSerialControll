<script lang="ts">
  import Servo from "../Indicators/Servo.svelte";


    import { state, keybinds, type, targetType } from "../stores"
    import CreateKeybind from "../Components/CreateKeyboardKeybind.svelte";

    let creatingKeybind = false;

    const keyUp = (code: string) => {
        if (creatingKeybind) {return}
        keybinds.unpressKey(code)
    }
    const keyDown = (code: string) => {
        if (creatingKeybind) {return}
        keybinds.pressKey(code)
    }

    document.addEventListener('keydown', event => {keyDown(event.code)})
    document.addEventListener('keyup', event => {keyUp(event.code)})

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
    <CreateKeybind bind:creatingKeybind/>
</div>