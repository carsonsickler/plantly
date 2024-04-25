<template>
    <v-app>
        <v-card id="page">
            <v-card id="name" class="bg-surface-color pa-4">
                <v-card-title class="headline text-h3 font-weight-medium text-center pb-4">Name: {{ plant.name }}</v-card-title>
                <v-card-subtitle class="text-h5 text-center font-weight-medium mt-2 pa-1">Type: {{ plant.type }}</v-card-subtitle>
                <v-card-subtitle class="text-h5 text-center font-weight-medium mt-1 pa-1 mb-2">Reservoir: {{ reservoir ? "Full" : "Empty" }}</v-card-subtitle>
            </v-card>
            <v-card class="bg-surface-color mt-4">
                <v-card>
                    <v-card-text>Last watered on {{ lastWateredDate }} at {{ lastWateredTime }}</v-card-text>
                </v-card>
                <v-container class="mb-6 d-flex flex-column align-center">
                    <v-row align="start" no-gutters>
                        <v-col cols="12" md="4">
                            <v-card class="pa-3 ma-2" color="yellow-lighten-5">
                                <v-icon>mdi-weather-sunny</v-icon>
                                <v-card-title class="headline">Light</v-card-title> 
                                <v-card-text>
                                    <LineChart :data="lightChartData"/>
                                </v-card-text>
                            </v-card>
                        </v-col>
                        <v-col cols="12" md="4">
                            <v-card class="pa-3 ma-2" color="light-blue-lighten-5">
                                <v-icon>mdi-water</v-icon>
                                <v-card-title class="headline">Humidity</v-card-title>
                                <v-card-text>
                                    <LineChart :data="humidityChartData" />
                                </v-card-text>
                            </v-card>
                        </v-col>
                        <v-col cols="12" md="4">
                            <v-card class="pa-3 ma-2" color="red-lighten-5">
                                <v-icon>mdi-thermometer</v-icon>
                                <v-card-title class="headline">Temperature</v-card-title>
                                <v-card-text>
                                    <LineChart :data="tempChartData" />
                                </v-card-text>
                            </v-card>
                        </v-col>
                    </v-row>
                    <v-row>
                        <v-card>
                            <v-card-text>
                                <v-date-picker v-model="selectedDate" @input="formatChartData"></v-date-picker>
                                <v-btn @click="formatChartData">Update</v-btn>
                            </v-card-text>
                        </v-card>
                    </v-row>
                </v-container>
            </v-card>
        </v-card>
    </v-app>
</template>

<script>
import LineChart from "../components/LineChart.vue";

export default {
    name: "PlantView",
    components: {
        LineChart,
    },
    data() {
        return {
            reservoir: false,
            plant: {
                name: "Loading...",
                readings: [
                    {
                        "temperature": 0,
                        "humidity": 0,
                        "light": 0,
                        "soilMoisture": 0,
                        "reservoir": 0,
                        "_id": "0",
                        "createdAt": "2024-03-31T00:15:33.814Z",
                        "updatedAt": "2024-03-31T00:15:33.814Z",
                    }
                ],
            },
            lastWateredDate: "Loading...",
            lastWateredTime: "",
            selectedDate: new Date(),
            light: [],
            humidity: [],
            tempChartData: {
                labels: Array.from( { length: 25 }, ( _, i ) => i ),
                datasets: [
                    {
                        label: "Data One",
                        backgroundColor: "#f87979",
                        data: [],
                    },
                ],
            },
            lightChartData: {
                labels: Array.from( { length: 25 }, ( _, i ) => i ),
                datasets: [
                    {
                        label: "Data One",
                        backgroundColor: "#f8f8f8",
                        data: [],
                    },
                ],
                options: {
                    scales: {
                        xAxes: [{
                            scaleLabel: {
                                display: true,
                                labelString: 'Hour'
                            },
                            ticks: {
                                stepSize: 1
                            }
                        }],
                        yAxes: [{
                            ticks: {
                                min: 0,
                                max: 24,
                                stepSize: 1
                            },
                            scaleLabel: {
                                display: true,
                                labelString: 'Hours'
                            }
                        }]
                    }
                }
            },
            humidityChartData: {
                labels: Array.from( { length: 25 }, ( _, i ) => i ),
                datasets: [
                    {
                        label: "Data One",
                        backgroundColor: "#f87979",
                        data: [],
                    },
                ],
            },
        };
    },
    methods: {
        formatChartData() {
            var selectedDate = new Date(this.selectedDate);
            const filteredReadings = this.plant.readings.filter( ( reading ) => {
                var readingDate = new Date( reading.createdAt );
                console.log(this.formatDate(selectedDate).split(",")[0] , this.formatDate(readingDate).split(",")[0])
                return this.formatDate(selectedDate).split(",")[0] === this.formatDate(readingDate).split(",")[0];
            } );

            this.tempChartData = {
                labels: Array.from( { length: 25 }, ( _, i ) => i ),
                datasets: [
                    {
                        label: "Temperature",
                        backgroundColor: "#f87979",
                        data: filteredReadings.map( ( reading ) => reading.temperature ),
                    },
                ],
            };
            this.lightChartData = {
                labels: Array.from( { length: 25 }, ( _, i ) => i ),
                datasets: [
                    {
                        label: "Light",
                        backgroundColor: "#f87979",
                        data: filteredReadings.map( ( reading ) => reading.light ),
                    },
                ],
            };
            this.humidityChartData = {
                labels: Array.from( { length: 25 }, ( _, i ) => i ),
                datasets: [
                    {
                        label: "Humidity",
                        backgroundColor: "#f87979",
                        data: filteredReadings.map( ( reading ) => reading.humidity ),
                    },
                ],
            };
        },
        formatDate( dateString ) {
            const date = new Date( dateString );
            const options = {
                year: "2-digit",
                month: "2-digit",
                day: "2-digit",
                hour: "2-digit",
                minute: "2-digit",
                second: "2-digit",
                hour12: false,
            };
            return new Intl.DateTimeFormat( "en-US", options ).format( date );
        },
        changeFromMilitary( time ) {
            const [ hours, minutes, seconds ] = time.split( ":" );
            const hour = hours % 12 || 12;
            void seconds;
            return `${ hour }:${ minutes } ${ hours >= 12 ? "PM" : "AM" }`;
        },
        async fetchPlant() {
            this.isLoading = true;
            const response = await fetch(
                `http://localhost:3000/plants/${ this.$route.params.plantId }`
            );
            this.plant = await response.json();
            this.isLoading = false;
            this.reservoir =
                this.plant.readings[ this.plant.readings.length - 1 ].reservoir;
            this.plant.lastWatered = this.formatDate(
                this.plant.readings[ this.plant.readings.length - 1 ].createdAt
            );
            this.lastWateredDate = this.plant.lastWatered.split( " " )[ 0 ].replace(',', '');
            this.lastWateredTime = this.changeFromMilitary(this.plant.lastWatered.split( " " )[ 1 ]);
            this.formatChartData();
        },
    },
    async beforeMount() {
        if ( !this.plant._id ) {
            this.fetchPlant();
        }
    },
};
</script>

<style scoped>
#page {
    padding-top: 10px;
    background-color: rgb(160, 160, 160);
    height: 100%;
    display: flex;
    flex-direction: column;
    align-items: center;
}
#name {
    max-width: 75vw;
}

</style>
