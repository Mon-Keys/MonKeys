import { createStore } from "vuex"

const store = createStore({
    state:{
        adminErrorMessage: "",
        passadminErrorMessage: "",
        loggedin: false,
        adminLoggedIn: false,
        addPass: {

        },
        adminAuth: {

        },
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
            
        },
        ADMIN_LOGIN: (state, val) => {
            state.adminAuth = val;
            if(state.adminAuth.status === "success"){
                state.adminLoggedIn = true
                
            } else {
                state.adminErrorMessage = state.adminAuth.status
            }
            alert(state.adminErrorMessage)
            
            console.log(state.adminAuth)
            
            
            
        },
        ADD_PASS: (state, val) => {
            state.addPass = val;
            state.passadminErrorMessage = state.addPass.status
            alert(state.addPass)
            
            console.log(state.addPass)
            
            
            
        }
    },
    getters: {
        getAuth: (state) => {
            return state.auth;
        } 
    }

})

export default store