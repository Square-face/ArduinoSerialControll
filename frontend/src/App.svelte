<script lang="ts">
  import Messages from './lib/Components/messages.svelte';
  
  // connections
  import Socket from './lib/Socket.svelte';
  import Serial from './lib/Serial.svelte';
  import Gamepads from './lib/Controls/Gamepads.svelte';

  // devices
  import Motor from './lib/Indicators/Motor.svelte'
  import Servo from './lib/Indicators/Servo.svelte';
  import Stepper from './lib/Indicators/Stepper.svelte';
  
  // controlling
  import Driving from './lib/Controls/Driving.svelte';
</script>

<main class="serial-control">
  <h1>Arduino Serial Controller</h1>

  <div class="content">

    <div class="connections">
      <Socket/>
      <Serial/>
      <Gamepads/>
    </div>
    
    <div class="controls">
      <Driving/>
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
  </div>
  <Messages/>

</main>

<style lang="scss">
  main.serial-control {
    display: flex;
    flex-direction: column;
    div.content{
      display: grid;
      grid-template-columns: 30% 45% 25%;
      div.settings {
        width: 250px;
      }
    }
  }
</style>
