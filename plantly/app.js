new Vue({
  el: '#app',
  vuetify: new Vuetify(),
  data: {
    temperature: 'Loading...',
    light: 'Loading...',
    humidity: 'Loading...',
    soilMoisture: 'Loading...'
  },
  methods: {
    fetchStats: function() {
      // TODO: Fetch stats from server
      this.temperature = '70°F';
      this.light = 'Bright';
      this.humidity = '50%';
      this.soilMoisture = 'Moist';
    }
  },
  created: function() {
    this.fetchStats();
  }
});