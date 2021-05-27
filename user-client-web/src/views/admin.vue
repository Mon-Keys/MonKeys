<template>
     <!-- ф<орма входа -->
        <div>
            <div v-if="!adminLoggedIn">
                
                <div v-if="!loginStatus">
                <h3> Введите название компании <br> 
                     и лицензионный ключ </h3>
                    <div style="color: red;">
                        {{getError}}
                    </div>
            <form @submit.prevent="CreatePost">
                <div>
                    <label for="adminAuth.companyName"> Логин компании </label>
                    <input type="text" id="login" v-model="adminAuth.companyName">
                </div>
                <div>
                    <label for="adminAuth.licenseKey"> Лицензионный ключ </label>
                    <input type="text" id="adminAuth.licenseKey" v-model="adminAuth.licenseKey">
                </div>
                <button v-on:click="createPost"> Вход </button>
            </form>
                </div>
            <div>
                
            </div>
            </div>
            <div v-if="adminLoggedIn">
                 
                    Добро пожаловать,
                    <div class="noPasses">
                        {{getCompanyName}}
                    </div>

                    <h3>Добавить пропуск для пользователя</h3>
                    <div>
                        <div style="color: red;">
                        {{getErrorPass}}
                    </div>
                    <label for="addPass.Login"> Добавить пропуск для  </label>
                    <input type="text" id="addPass.Login" v-model="addPass.Login">
                    <button v-on:click="createPostPass"> Подтвердить </button>
                </div>
            </div>
        </div>
</template>

<script>



export default {
    computed: {
        getCompanyName() {
            return this.$store.state.adminAuth.company_name
        },
        loginStatus () {
            return this.$store.state.loggedin
            
        },
        usernameLoggedIn () {
            return this.$store.state.auth.login
        },
        getError () {
            if(this.$store.state.adminErrorMessage==='not_exists'){
                return "Компании с таким именем не существует"
            }
            if(this.$store.state.adminErrorMessage==='incorrect_license_key'){
                return "Неправильный лицензионный ключ"
            }
            return ""
        },
        getErrorPass () {
            if(this.$store.state.passadminErrorMessage==='not_exists_client'){
                
                return "Клиента с таким логином не существует!"
                
            }
            if(this.$store.state.passadminErrorMessage==='not_exists_company'){
                
                return "Компания не существует"
            }
            if(this.$store.state.passadminErrorMessage==='success'){
                return "Пропуск добавлен!"
            }
            return ""
        },
        adminLoggedIn () {
            return this.$store.state.adminLoggedIn
        }
    },
    data() {
        return { 
            adminAuth:{
                "companyName": "",
                "licenseKey": ""
            },
            addPass: {
                "Login": "",
            },
            lastAddPassSuccess: false
        }
    },
    methods: {
        createPost(){
            
            const requestOptions = {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(
                    { 
                        "companyName": this.adminAuth.companyName, 
                        "licenseKey": this.adminAuth.licenseKey
                    }
                    )
            };
            fetch("http://192.168.31.234:8080/admin", requestOptions)
            .then(response => 
                    response.json().then(data => ({
                        data: data,
                        status: response.status
                    })
                ).then(res => {
                    this.$store.commit('ADMIN_LOGIN',res.data);
                })).catch((error) => console.log(error));
            
        },
        createPostPass(){
            
            const requestOptions = {
                method: "POST",
                headers: { "Content-Type": "application/json" },
                body: JSON.stringify(
                    { 
                        "login": this.addPass.Login,
                        "companyName": this.adminAuth.companyName, 
                        "licenseKey": this.adminAuth.licenseKey
                    }
                    )
            };
            fetch("http://192.168.31.234:8080/addpass", requestOptions)
            .then(response => 
                    response.json().then(data => ({
                        data: data,
                        status: response.status
                    })
                ).then(res => {
                    this.$store.commit('ADD_PASS',res.data);
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