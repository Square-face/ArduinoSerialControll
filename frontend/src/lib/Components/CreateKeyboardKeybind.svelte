<script lang="ts">
    export let creatingKeybind: boolean

    import { keybinds, type keyboardKeybind } from "../stores";

    let newKeybind: keyboardKeybind = {
        id: -1,
        key: "",
        value: false,
        targets: []
    }

    window.addEventListener("keydown", event => {
        if (!creatingKeybind) {return}

        newKeybind.key = event.code
        newKeybind.id = $keybinds.keyboard.length
        newKeybind.value = true
    })

</script>

<div class="create-keybind">
    <button on:click={() => creatingKeybind = !creatingKeybind}>{creatingKeybind ? "Cancel" : "New keybind"}</button>
    <div class="create" class:enabled={creatingKeybind}>

        <span id="key">{(newKeybind.key == "") ? "Press a key" : newKeybind.key}</span>
        <h3>Targets</h3>
        <div class="targets">
            {#each newKeybind.targets as target}
            <div class="target">
                <span>Type: {target.type}</span>
                <span>Target Type: {target.targetType}</span>
                <span>index: {target.index}</span>
                <span>Inverted: {target.inverted}</span>
                <span>Toggle: {target.toggle}</span>
                <span>Target Value: {target.targetValue}</span>
            </div>
            {/each}
            <button>Add target</button>
        </div>
    </div>
</div>