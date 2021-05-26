import { createWebHistory, createRouter } from 'vue-router'
import passes from '@/views/passes.vue'
import homepage from '@/views/homepage.vue'
import login from '@/views/login.vue'
import registration from '@/views/registration.vue'

const router = createRouter({
    history: createWebHistory(process.env.BASE_URL),
    routes: [
        {
            path: '/',
            name: 'Homepage',
            component: homepage
        },
        {
            path: '/timecodes',
            name: 'Timecodes',
            component: passes
        },
        {
            path: '/login',
            name: 'Login',
            component: login
        },
        {
            path: '/registration',
            name: 'Registration',
            component: registration
        }
    ]
})

export default router;