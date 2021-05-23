<template>
    <div>
        hello from the other side
        <form @submit.prevent="CreatePost">
            <div>
                <label for="userId"> Post User ID </label>
                <input type="text" id="userID" v-model="fromData.userID">
            </div>
            <div>
                <label for="title"> Post Title </label>
                <input type="text" id="title" v-model="fromData.title">
            </div>
            <div>
                <label for="body"> Post Body </label>
                <input type="text" id="body" v-model="fromData.body">
            </div>
            <button> CreatePost </button>
        </form>
    </div>
</template>

<script>

import axios from 'axios'

export default {
    name: 'CreatePost',
    data() {
        return {
            formData :{
                userID: '',
                title: '',
                body: ''
            }
        }
    },
    methods: {
        createPost(){
            axios.post('http://jsonplacholder.typicode.com/posts', this.fromData)
            .then(Response => console.log(Response))
            .catch((error) => console.log(error))
        }
    }
}
</script>


<style scoped>

</style>