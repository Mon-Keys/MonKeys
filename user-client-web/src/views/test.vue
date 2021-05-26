<template>
  <div>
      <div v-for="item in list" v-bind:key="item.name">
          {{item.name}}
      </div>
  </div>
</template>

<script>
export default {
    data() {
        return {
            list: [ 
                { name: "first "},
                { name: "second"},
                { name: "third" }
            ]
        }
    }
}
</script>

<style>

</style>