import { createApp } from 'vue'
import App from './App.vue'
import vuex from 'vuex'
import store from "./store/store"
import router from "./router/router"



createApp(App).use(store).use(router).use(vuex).mount('#app')

window.axios = require('axios')