<template>
  <v-app>
    <v-main>
      <v-container fluid>
        <v-row align="center" justify="center">
          <v-col cols="12" sm="8" md="6">
            <v-card color="green lighten-4">
              <v-card-title class="headline green--text text--darken-2">
                Welcome to Plantly
              </v-card-title>
              <v-card-text class="black--text">
                Plantly is a smart plant pot that merges Vue frontend, Express server, and ESP32 sensors. The sensors monitor light, humidity, temperature, and soil moisture. If the soil is dry, the ESP32 waters the plant via a pump. The data is sent to a database via the Express server, which is accessible through the Vue frontend with Chart.js for visualization and manual watering.
              </v-card-text>
            </v-card>
          </v-col>
        </v-row>
      </v-container>
    </v-main>
  </v-app>
</template>

<script>
export default {
  name: 'HomeView',
}
</script>

<style scoped>
.v-card {
  margin-top: 20px;
}
</style>