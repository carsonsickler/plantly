<template>
    <v-app>
        <v-app-bar>
            <v-row no-gutters justify="space-between" align="center">
                <v-app-bar-nav-icon @click="drawer = !drawer"></v-app-bar-nav-icon>
                <v-img src="/plantly.png" width="10em" height="3em" class="mt-3"></v-img>
\            </v-row>
        </v-app-bar>

        <v-navigation-drawer v-model="drawer" class="gray">
            <v-list two-line subheader>
                <v-subheader class="text-h3 font-weight-medium ml-5">Plants</v-subheader>
                <v-list-item-group>
                    <v-list-item v-for="plant in plants" :key="plant._id" @click="drawer = false" class="background-green">
                        <v-list-item-content class="d-flex flex-row border-md rounded pa-2">
                            <v-icon color="green-darken-3">mdi-leaf</v-icon>
                            <router-link :to="{ name: 'PlantView', params: { plantId: plant._id } }" class="pl-1">
                                <v-list-item-title class="font-weight-medium">{{ plant.name }}</v-list-item-title>
                            </router-link>
                        </v-list-item-content>
                    </v-list-item>
                </v-list-item-group>
            </v-list>
        </v-navigation-drawer>
        <v-main>
        <router-view></router-view>
        </v-main>
    </v-app>
</template>

<script>
export default {
    data() {
        return {
            drawer: false,
            plants: [],
        }
    },
    methods: {
        async getPlants() {
            try {
                const response = await fetch('http://localhost:3000/plants')
                this.plants = await response.json()
            } catch (error) {
                console.error(error)
            }
        },
    },
    mounted() {
        this.getPlants()
    },
}
</script>

<style>



v-subheader {
    font-family: 'Quicksand', sans-serif;
}

a {
    text-decoration: none;
    color: inherit;
}
</style>