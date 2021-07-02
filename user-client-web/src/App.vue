<template>
    
    <div id="nav">
    <div style="display: flex; align-items: center; justify-content: center;" class="bitfont">
      
      <div v-if="loginStatus"> 
      <router-link :to="{ name: 'Timecodes'}">
        <div class="navbarItem">
          Временные коды 
        </div>
      </router-link>
      </div>
      <div v-if="!loginStatus "> 
      
        <router-link :to="{ name: 'Login'}">
          <div class="navbarItem">
            Войти 
          </div> 
        </router-link>
      </div>
      <div v-if="!loginStatus"> 
      <router-link :to="{ name: 'Admin'}">
        <div class="navbarItem">
          Администрирование
        </div> 
      </router-link>
      </div>
       <div v-if="!loginStatus"> 
      <router-link :to="{ name: 'Registration'}">
      
        <div class="navbarItem">
          Регистрация
        </div> 
      </router-link>
      </div>
      <div v-if="loginStatus"> 
      <div class="navbarItem">
          В системе как 
      <div style="color: red;">
        {{usernameLoggedIn}}
      </div> 
        </div> 
          
      
      </div>
      <div v-if="loginStatus"> 
        <div class="navbarItem" v-on:click="logoutUser">
          Выйти
        </div> 
      </div>
      
    </div>
    <div class="monkeysLogo">
        MonKeys
    </div>
    
    </div>
    <transition name="justSlide">
      <router-view>
    </router-view>
    </transition>
  
</template>

<script>

export default {
    computed: {
        loginStatus () {
            return this.$store.state.loggedin
        },
        usernameLoggedIn () {
            return this.$store.state.auth.login
        },
        adminLoggedIn () {
            return this.$store.state.adminLoggedIn
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

.slide-left-enter-active,
.slide-left-leave-active,
.slide-right-enter-active,
.slide-right-leave-active {
  transition-duration: 0.5s;
  transition-property: height, opacity, transform;
  transition-timing-function: cubic-bezier(0.55, 0, 0.1, 1);
  overflow: hidden;
}

.slide-left-enter,
.slide-right-leave-active {
  opacity: 0;
  transform: translate(2em, 0);
}

.slide-left-leave-active,
.slide-right-enter {
  opacity: 0;
  transform: translate(-2em, 0);
}

.monkeysLogo{
    text-align: start;
    font-family: "Minecraft";
    color:black;
    font-size: 500%;
}


.justSlide-enter-active{
  overflow: hidden;
    animation: slideInside 2s;
}

.justSlide-leave-active{
  overflow: hidden;
    animation: slideOut 2s;
}

@keyframes slideOut {
    0% {height: 600px;
    overflow: hidden;
    transform: translate(0, 0);}
    100% {height: 0px;
    overflow: hidden;
        transform: translate(-100%, 0);
        }
    
}
.navbarItem{
  color: black;
  text-decoration: none;
  padding: 10px;
  height: 40px;
  border: 1px solid black;
}
@keyframes slideInside {
    0% {height: 0px;
        transform: translate(100%, 0);
        }
    100% {height: 600px;
    transform: translate(0, 0);}
    
}
</style>

