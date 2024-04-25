<template>
  <v-app>
    <Navbar />
  </v-app>
</template>

<script>
import Navbar from './components/Navbar'

export default {
  name: 'App',
  components: {
    Navbar,
  },

  data: () => ({
    
  }),
}
</script>

<style>
@import url('https://fonts.googleapis.com/css2?family=Quicksand:wght@300..700&display=swap');

body {
  font-family: 'Quicksand', sans-serif;
}

.v-application, .v-overlay-container {
  [class*='text-']{
    font-family: 'Quicksand', sans-serif !important;
  }
  font-family: 'Quicksand', sans-serif !important;
}


</style>