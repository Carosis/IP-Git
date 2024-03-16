import Vue from 'vue'
import VueRouter from 'vue-router'
Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'loginView',
    component:  () => import('../views/login/index.vue')
  },
  {
    path: '/login',
    name: 'loginView',
    component:  () => import('../views/login/index.vue')
  },
  {
    path: '/register',
    name: 'register',
    component: () => import('../views/register/index.vue')
  },
  {
    path: '/forget',
    name: 'forgetView',
    component: () => import('../views/forget/index.vue')
  },
  {
    path: '/home',
    name: 'homeView',
    component: () => import('../views/home/index.vue')
  },
  {
    path: '/admin',
    name: 'adminView',
    component: () => import('../views/admin/index.vue')
  },
  {
    path: '/management',
    name: 'managementView',
    component: () => import('../views/management/index.vue')
  },
  {
    path: '/profile',
    name: 'profileView',
    component: () => import('../views/profile/index.vue')
  }
]

const router = new VueRouter({
  routes
})

export default router
