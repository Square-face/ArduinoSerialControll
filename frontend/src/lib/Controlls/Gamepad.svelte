<script lang="ts">
    enum type {Motor, Servo, Stepper}
    enum targetType {speed, position, enabled}
    enum analogmode {relative, absolute}

    interface target {
        type: type,
        index: number,
        value: targetType,
    }

    interface digitalkeybind {
        target: target[]
        buttonid: number,
        digital: boolean,
        effect: boolean,
    }

    interface analogkeybind {
        index: number,
        target: target[],
        mode: analogmode,
        inverted: boolean,
        max: number,
        min: number,
        dead: number,
    }

    interface gamepad {
        id: number,
        name: string,
        gamepad: Gamepad,
        connected: boolean,
        saved: boolean,
        analog: analogkeybind[],
        digital: digitalkeybind[]
    }

    let saved_gamepads: gamepad[] = [];
    let gamepads: gamepad[] = [];

    const addGamepad = (gamepad) => {
        console.log("adding gamepad")
        for (let i = 0; i < saved_gamepads.length; i++) {
            if (saved_gamepads[i].gamepad.id == gamepad.id) {
                gamepads[gamepad.index] = saved_gamepads[i]
                return
            }
        }

        gamepads[gamepad.index] = {
            id: gamepad.id,
            name: gamepad.index,
            gamepad: gamepad,
            connected: true,
            saved: false,
            analog: [],
            digital: []
        }
    }

    
    
    document.addEventListener('gamepadconnected', event=>{
        if (!("gamepad" in event)) {alert("Browser does not support gamepads")}
        
        // @ts-expect-error
        addGamepad(event.gamepad)
        
    })
    document.addEventListener('gamepaddisconnected', event => {
        // @ts-expect-error
        let gamepad: gamepad = gamepads[event.gamepad.index]
        if (gamepad.saved) {
            saved_gamepads.push(gamepad)
        }
    })
    
    for (let i = 0; i < navigator.getGamepads().length; i++) {
        addGamepad(navigator.getGamepads[i])
    }
</script>

<div class="gamepads">
    <h2 class="header">Gamepad{(gamepads.length > 1) ? "s" : ""}</h2>

    <div class="gamepaps">
        {#each gamepads as gamepad}
        <div class="gamepap">
            <input type="text" name="name" bind:value={gamepad.name}>
            <div class="digital keybinds">
                {#each gamepad.digital as digital_bind}
                <div class="digital keybind">
                    <span class="button-id">{gamepad.id}</span>
                </div>
                {/each}
            </div>
            <div class="analog keybinds">

            </div>
        </div>
        {/each}
    </div>
</div>


