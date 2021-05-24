<template>
    <div id="nav">
    
    <router-link :to="{ name: 'Homepage'}">
    
         Главная 
    
    </router-link>
    <div v-if="loginStatus"> 
    <router-link :to="{ name: 'Timecodes'}">
    
         Временные коды 
    
    </router-link>
    </div>
    <router-link :to="{ name: 'Login'}">
    
         Войти </router-link>
    
    <div v-if="loginStatus"> 
    
        Logged in as {{usernameLoggedIn}} 
    
    </div>
    <button v-on:click="logoutUser">
        logout
    </button>
    </div>
    
    <router-view/>
</template>

<script>

export default {
    computed: {
        loginStatus () {
            return this.$store.state.loggedin
        },
        usernameLoggedIn () {
            return this.$store.state.auth.login
        }
    },
  data() {
        return {
            itemRefs: [],
            percentage: 20,
            timeLeft: 0,
            selected: "none",
            
        }
    },
  

  mounted: function() {

  },
  methods: {
    setUser(login, password)
    {
      this.auth.login=login;
      this.auth.password=password;
    },
    logoutUser: function () { 
       
        this.$store.commit('LOGOUT_USER',false);
    }
  }
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

#nav {
    padding: 30px;
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
