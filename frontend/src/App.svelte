<script lang="ts">
  import svelteLogo from './assets/svelte.svg'
  import viteLogo from '/vite.svg'
  import Socket from './lib/Socket.svelte';
  import Serial from './lib/Serial.svelte';
  import Motor from './lib/Indicators/Motor.svelte'
  import Servo from './lib/Indicators/Servo.svelte';
  import Stepper from './lib/Indicators/Stepper.svelte';
  import Driving from './lib/Controlls/Driving.svelte';
  import Gamepad from './lib/Controlls/Gamepad.svelte';
  import Keybinds from './lib/Controlls/Keybinds.svelte';
</script>

<main class="serial-controll">

  <div class="settings">
    <Socket/>
    <Serial/>
  </div>

  <div class="controlls">
    <Driving/>
    <Gamepad/>
    <Keybinds/>
  </div>

  <div class="visualization">
    
      <div class="motors">
        <Motor index={0}/>
        <Motor index={1}/>
      </div>
      <div class="servos">
        <Servo index={0}/>
        <Servo index={1}/>
        <Servo index={2}/>
        <Servo index={3}/>
      </div>
      <div class="steppers">
        <Stepper index={0}/>
      </div>

  </div>

</main>

<style lang="scss">
  main.serial-controll {
    display: flex;
    flex-direction: row;
    div.settings {
      width: 250px;
    }
  }
</style>
