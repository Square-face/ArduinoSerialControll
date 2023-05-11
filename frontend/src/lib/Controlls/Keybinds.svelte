<script lang="ts">

    import { state, keybinds, type, targetType } from "../stores"

    let configuredKeybinds = []
    let activeKeybinds = []

    keybinds.addkeybind({
        id: 0,
        key: "KeyF",
        targets: [{
            type: type.Servo,
            targetType: targetType.position,
            index: 2,
            targetValue: 180,
            toggle: false,
            inverted: false,
        }]
    })

    // get upp to date keybinds
    keybinds.subscribe(keybinds => {
        configuredKeybinds = keybinds.keybinds
        activeKeybinds = keybinds.activeKeybinds
    })

    document.addEventListener('keydown', event => {keybinds.pressKey(event.code)})
    document.addEventListener('keyup', event => {keybinds.unpressKey(event.code)})

</script>

<div class="keybinds">
    <h2>Keybinds</h2>
    {#each configuredKeybinds as keybind}
    <div class="keybind">
        <span class="keybind-id">{keybind.id}</span>
        <span class="keybind-key">{keybind.key}</span>
        <span> {activeKeybinds.includes(keybind) ? "active" : "passive" } </span>
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