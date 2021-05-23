<template>
<div>
<Navbar/>
<test/>

</div>
</template>

<script>

import test from './components/test.vue'

import Navbar from './components/Navbar.vue'


export default {
  data() {
      return {
        value: 'https://example',
        size: 300,
      }
    },
  name: 'App',
  components: {
    test,
    Navbar
  },

  mounted: function() {

  },
 }
</script>

<style>
@font-face {
  font-family: "Minecraft";
  src: local("ProximaNovaCond-Semibold.ttf"),
   url(./fonts/ProximaNovaCond-Semibold.ttf) format("truetype");
}
body {
    display: block;
    margin: 0px;
}
.bitfont{
  font-family: "Minecraft";
  src: local("MinecraftRegular-Bmg3"),
   url(./fonts/MinecraftRegular-Bmg3.otf) format("truetype");
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}
#app {
  font-family: MinecraftRegular-Bmg3, Helvetica, Arial, sans-serif;
  src: local("MinecraftRegular-Bmg3"),
   url(./fonts/MinecraftRegular-Bmg3.otf) format("truetype");
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}
</style>
