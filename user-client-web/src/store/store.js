import { createStore } from "vuex"

const store = createStore({
    state:{
        loggedin: false,
        auth:{
            
        },
        res: {

        }
    },
    mutations: {
        LOGIN_USER: (state, auth) => {
            state.auth = auth;
            if(state.auth.status === "success"){
                state.loggedin = true
            }
            console.log(state.auth)
            
        },
        GET_TIMECODES: (state, res) => {
            state.res = res;
            console.log(state.res)
            
        },
        LOGOUT_USER: (state, val) => {
            console.log(state)
            
            state.loggedin = val
            state.loggedin = false
            
        }
    },
    getters: {
        getAuth: (state) => {
            return state.auth;
        } 
    }

})

export default store