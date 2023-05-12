<script lang="ts">

    import { gamepads, keybinds } from '../stores'
    import DigitalField from '../Components/DigitalField.svelte';
    import AnalogField from '../Components/AnalogField.svelte';

    let axis: Array<number[]> = []
    let f
    
    window.addEventListener('gamepadconnected', event=>{
        console.log("gamepad connected")
        
        gamepads.connectGamepad(event.gamepad)
        
    })
    window.addEventListener('gamepaddisconnected', event => {
        console.log("gamepad disconnected")
        console.log(event.gamepad)
        gamepads.disconnectGamepad(event.gamepad.index)
    })
    
    const getGamepads = () => {
        navigator.getGamepads().forEach(gamepad => {
            gamepads.connectGamepad(gamepad)
        });
    }

    setInterval(()=>{
        navigator.getGamepads().forEach(gamepad=>{
            gamepads.updateGamepad(gamepad)
            gamepads.updateAxes(gamepad.index)
            gamepad.buttons.forEach((button, index) => {
                if (button.pressed) {
                    keybinds.pressButton(gamepad.index, index)
                } else {
                    keybinds.unpressButton(gamepad.index, index)
                }
            })
            gamepad.axes.forEach((value, index) => {
                keybinds.setAnalogValue(gamepad.index, index, value)
            })
        })
    }, 100)
</script>

<div class="gamepads">
    <h2 class="header">Gamepad{($gamepads.length > 1) ? "s" : ""}</h2>
    <button on:click={getGamepads}>Update Gamepads</button>

    <div class="gamepaps">
        {#each $gamepads as gamepad}
        <div class="gamepap">
            <span class="gamepad-id">{gamepad.id}</span>
            <div class="digital inputs">
                {#each gamepad.gamepad.buttons as button}
                    <DigitalField bind:value={button.pressed} index={gamepad.gamepad.buttons.indexOf(button)}/>
                {/each}
            </div>
            <div class="analog inputs">
                {#each gamepad.axes as axes, index}
                    <AnalogField bind:gamepad={gamepad} index={index}/>
                {/each}
            </div>
        </div>
        {/each}
    </div>
</div>

<style lang="scss">
    div.inputs {
        display: flex;
        flex-direction: row;
        flex-wrap: wrap;
    }
</style>

