<template>
     <!-- форма входа -->
        <div class="form" v-if="!auth.loggedIn">
            <div>
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
                <button v-on:click="createPost"> Login </button>
            </form>
            </div>
        </div> 
</template>

<script>



export default {
    data() {
        return { 
            auth :{
                login: '',
                password: '',
                loggedIn: false
            }
        }
    },
    methods: {
        createPost(){
            
            
            const jsonData = { "login": "pierrelean11233", "password": "admin"};
            alert(jsonData.login)
            alert(jsonData.password)
            const requestOptions = {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(
                    { 
                        "login": "pierrelean", 
                        "password": "admin"
                    }
                    )
            };
            fetch("http://127.0.0.1:8080/timecode", requestOptions)
            .then(Response => console.log(Response.json()))
            .catch((error) => console.log(error))
            this.auth.loggedIn = true;
        }
    }
}
</script>