<template>
     <!-- форма входа -->
        
            <div>
                <h3> Регистрация </h3>
            <form @submit.prevent="CreatePost" style="display: flex; flex-direction: column; justify-content: center;">
                <div>
                    <label for="register.login"> Логин </label>
                    <input type="text" id="login" v-model="register.login">
                </div>
                <div>
                    <label for="register.password"> Пароль </label>
                    <input type="text" id="register.password" v-model="register.password">
                </div>
               
                
                <div>
                    <label for="register.email"> Email </label>
                    <input type="text" id="register.email" v-model="register.email">
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
            register :{
                login: "",
                password: "",
                email: ""
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
                        "login": this.register.login, 
                        "password": this.register.password,
                        "email": this.register.email
                    }
                    )
            };
            alert(this.register.email)
            fetch("http://192.168.0.104:8080/registr", requestOptions)
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