<template>
     <!-- форма входа -->
        
            <div>
                <div v-if="!loginStatus">
                <h3> Выполните вход </h3>
            <form @submit.prevent="CreatePost">
                <div>
                    <label for="auth.login"> Логин </label>
                    <input type="text" id="login" v-model="auth.login">
                </div>
                <div>
                    <label for="auth.password"> Пароль </label>
                    <input type="text" id="auth.password" v-model="auth.password">
                </div>
                <button v-on:click="createPost"> Логин </button>
            </form>
                </div>
            <div>
                <div v-if="loginStatus"> 
                    Добро пожаловать,
                    <div class="noPasses">
                {{usernameLoggedIn}}!
                </div>
                </div>
            </div>
            </div>
        
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
            auth :{
                
            }
        }
    },
    methods: {
        createPost(){
            
            const requestOptions = {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(
                    { 
                        "login": this.auth.login, 
                        "password": this.auth.password
                    }
                    )
            };
            fetch("http://172.20.10.2:8080/timecode", requestOptions)
            .then(response => 
                    response.json().then(data => ({
                        data: data,
                        status: response.status
                    })
                ).then(res => {
                    this.$store.commit('LOGIN_USER',res.data);
                })).catch((error) => console.log(error));
            
        }
    }
}
</script>

<style scoped>
.noPasses{
    font-family: "Minecraft";
    animation: rainbow 5s;
    font-size: 200%;
    animation-iteration-count: infinite;
}

@keyframes rainbow{
    0% {color: rgb(255, 196, 100);}
    10% {color: rgb(87, 255, 115);}
    20% {color: rgb(255, 157, 157);}
    30% {color: rgb(160, 241, 255);}
    40% {color: rgb(251, 114, 222);}
    50% {color: rgb(251, 79, 79);}
    60% {color: rgb(185, 63, 255);}
    70% {color: rgb(231, 72, 72);}
    80% {color: rgb(255, 0, 0);}
    90% {color: rgb(251, 255, 0);}
    100% {color: rgb(255, 196, 100);}
}
</style>