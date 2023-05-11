<script lang="ts">
    export let value: boolean
    export let onChange: EventListener
    export let width = "60px"
    export let height = "30px"

</script>

<label style:--width={width} style:--height={height} class="switch">
    <input type="checkbox" bind:checked={value} on:change={onChange}>
    <span class="slider round"></span>
</label>

<style>

.switch {
  width: var(--width);
  height: var(--height);
  position: relative;
  display: inline-block;
}

.switch input { 
  opacity: 0;
  width: 0;
  height: 0;
}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: rgba(0,0,0,0.2);
  -webkit-transition: .4s;
  transition: .4s;
  border-radius: 34px;
}

.slider:before {
  position: absolute;
  content: "";
  height: calc(var(--height) * 0.75);
  width: calc(var(--height) * 0.75);
  left: calc(var(--height) * 0.125);
  bottom: calc(var(--height) * 0.125);
  background-color: white;
  -webkit-transition: .4s;
  transition: .4s;
  border-radius: 50%;
}
input:checked + .slider {
  background-color: rgb(0, 115, 255);
}

input:focus + .slider {
  box-shadow: 0 0 1px rgb(0, 242, 255);
}

input:checked + .slider:before {
  -webkit-transform: translateX(calc(var(--width) - var(--height)));
  -ms-transform: translateX(calc(var(--width) - var(--height)));
  transform: translateX(calc(var(--width) - var(--height)));
}

/* Rounded sliders */
</style>