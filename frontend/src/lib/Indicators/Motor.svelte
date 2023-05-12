<script lang="ts">
    export let index: number

    import { state, type motor, keybinds, type, targetType } from '../stores'

    var motor: motor;

    const map = (inMin: number, inMax: number, value: number, outMin:number, outMax:number) => {
        let range = inMax-inMin
        let adj = value-inMin
        let pre = adj/range
        let outRange = outMax-outMin
        let outValue = outRange*pre
        return outValue+outMin
    }

    const avg = (numbers: number[]) => {
        var total = 0;
        for(var i = 0; i < numbers.length; i++) {
            total += numbers[i];
        }
        return total / numbers.length;
    }

    state.subscribe(state => motor=state.motors[index])
    keybinds.subscribe(keybinds => {
        let motorSpeeds = []
        keybinds.analog.forEach(keybind => {
            keybind.targets.forEach(target => {
                if (target.type != type.Motor ) {return}
                if (target.targetType != targetType.speed) {return}
                if (target.index != index) {return}

                if (target.absolute) {
                    let value = target.inverted ? keybind.value*-1 : keybind.value
                    let out = map(target.inMin, target.inMax, value, target.outMin, target.outMax)
                    motorSpeeds.push(out)
                }
            });
        });
        motor.speed = avg(motorSpeeds)
    })

    const update = () => {
        state.updateMotor(index, motor)
    }
</script>

<h2>Motor {index+1}</h2>
<input
    type="range"
    name="MotorSpeedSlider"
    id="Motor{index}SpeedSlider"
    min="-255"
    max="255"
    on:change={update}
    bind:value={motor.speed}
>
<input on:change={update} type="number" name="MotorSpeedInput" id="Motor{index}SpeedInput" bind:value={motor.speed}>