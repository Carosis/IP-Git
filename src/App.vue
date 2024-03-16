<template>
  <div class="app" v-cloak>
    <router-view></router-view>
  </div>
</template>

<script>
export default {
  name: "app",
  data() {
    return {};
  },
};
</script>

<style>
* {
  margin: 0;
  padding: 0;
}
.app {
  height: 100vh;
}
</style>
