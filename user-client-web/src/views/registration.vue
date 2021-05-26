<template>
     <!-- форма входа -->
        
            <div>
                <h3> Регистрация </h3>
            <form @submit.prevent="CreatePost" style="display: flex; flex-direction: column; justify-content: center;">
                <div>
                    <label for="auth.login"> Логин </label>
                    <input type="text" id="login" v-model="auth.login">
                </div>
                <div>
                    <label for="auth.password"> Пароль </label>
                    <input type="text" id="auth.password" v-model="auth.password">
                </div>
                <div>
                    <label for="auth.password"> Повторите пароль </label>
                    <input type="text" id="auth.password" v-model="auth.password">
                </div>
                <button v-on:click="createPost"> Зарегистрироваться </button>
            </form>
            <div>
                {{this.$store.auth}}
            </div>
            </div>
        
</template>

<script>



export default {
    computed: {
        loginStatus () {
            return this.$store.auth
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
            fetch("http://192.168.31.65:8080/timecode", requestOptions)
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