import { createWebHistory, createRouter } from 'vue-router'
import passes from '@/views/passes.vue'
import homepage from '@/views/homepage.vue'
import login from '@/views/login.vue'

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
        }
    ]
})

export default router;