<template>
    <Line :data="data" />
</template>
  
<script lang="js">
import {
    Chart as ChartJS,
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend
    } from 'chart.js'

import { Line } from 'vue-chartjs'

ChartJS.register(
CategoryScale,
LinearScale,
PointElement,
LineElement,
Title,
Tooltip,
Legend
)


export default {
  name: 'App',
  components: {
    Line
  },
  props: {
    chartData: Object
  },
  computed: {
    data() {
        return this.chartData
    }
  }
}
</script>

