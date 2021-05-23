<template>
<div>
  <navbar/>
    <login @setUser="setUser($event)" />
    <passes/>
</div>
</template>

<script>

import passes from './components/passes.vue'

import login from './components/login.vue'

import navbar from './components/navbar.vue'


export default {
  data() {
        return {
            itemRefs: [],
            percentage: 20,
            timeLeft: 0,
            selected: "none",
            auth :{
                login: '',
                password: '',
                loggedIn: false
            },
            res: {
                "status": "success",
                "ID": "1",
                "login": "pierrelean",
                "email": "perlinleo@gmail.com",
                "password": "admin",
                "passes": [{
                        "privateKey": "sdsdsdsdsdsd",
                        "companyID": "1233232",
                        "companyName": "mail.ru",
                        "passID": "1233232",
                        "timecode": "92303494939434",
                    },
                    {
                        "privateKey": "dsdsdsdd",
                        "companyID": "13232232",
                        "companyName": "контора",
                        "passID": "123343232",
                        "timecode": "92303494939234",
                        
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "ёбаных",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "долбаебов",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "как же",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "я ебал",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "их сучьи",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "рты",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "дайте",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "допуск",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "к защите",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    },
                    {
                        "privateKey": "sd43sdsdsdsdsd",
                        "companyID": "12332434332",
                        "companyName": "мрази",
                        "passID": "123324545432",
                        "timecode": "92303494464554",
                       
                    }
                ]
            }
        }
    },
  name: 'App',
  components: {
    passes,
    navbar,
    login
  },

  mounted: function() {

  },
  methods: {
    setUser(login, password)
    {
      this.auth.login=login;
      this.auth.password=password;
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
