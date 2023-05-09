<script lang="ts">

    import { state } from '../stores'

    
    var gas: number = ($state.motors[0].speed+$state.motors[1].speed); // (L+R)/2
    var turn: number = 0; // (L-R)/2
    
    var leftspeed = 0
    var rightspeed = 0
    
    function clamp(min:number, value:number, max:number): number {
        if (min > value) return min
        if (max < value) return max
        return value
    }
    
    state.subscribe(state => {
        gas = ((state.motors[0].speed+state.motors[1].speed)/255)*50
        turn = ((state.motors[1].speed-state.motors[0].speed)/255)*50
    })

    function update() {
        leftspeed = gas+turn
        rightspeed = gas-turn
        console.log(leftspeed)
        console.log(rightspeed)

        state.update( state => {
            state.motors[1].speed = (leftspeed/100)*255
            state.motors[0].speed = (rightspeed/100)*255
            return state
        })
    }
</script>

<input on:change={update} type="range" name="gas" id="gasSlider" min="-100" max="100" bind:value={gas}>
<input on:change={update} type="number" name="gas" id="gasNumber" bind:value={gas}>
<input on:change={update} type="range" name="turn" id="turnSlider" min="-100" max="100" bind:value={turn}>
<input on:change={update} type="number" name="turn" id="turnNumber" bind:value={turn}>