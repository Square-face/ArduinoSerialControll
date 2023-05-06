const websocket = new WebSocket("ws://localhost:8765/");
var connect = true
var serialOpen = true

var motorSliders = document.querySelectorAll('div.motors>div.motor>input.slider')
for (let i = 0; i < motorSliders.length; i++) {
    console.log(i)
    motorSliders[i].onchange = () => {
        console.log("change detected")
        if (connect) {
            let data = {
                type: "motor",
                index: i,
                value: motorSliders[i].value
            }
            websocket.send(JSON.stringify([data]))
        }
    }
}

var stepperSlider = document.querySelectorAll('div.steppers>div.stepper>input.slider')
for (let i = 0; i < stepperSlider.length; i++) {
    console.log(i)
    stepperSlider[i].onchange = () => {
        console.log("change detected")
        if (connect) {
            let data = {
                type: "stepper",
                index: i,
                value: stepperSlider[i].value
            }
            websocket.send(JSON.stringify([data]))
        }
    }
}


var servoSliders = document.querySelectorAll('div.servos>div.servo>input.slider')
for (let i = 0; i < servoSliders.length; i++) {
    console.log(i)
    servoSliders[i].onchange = () => {
        console.log("change detected")
        if (connect) {
            let data = {
                type: "servo",
                index: i,
                value: servoSliders[i].value
            }
            websocket.send(JSON.stringify([data]))
        }
    }
}
