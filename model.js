const mongoose = require('mongoose');
require('dotenv').config();
mongoose.connect(process.env.DATABASE_URL).then(() => {
    console.log("Connected to the database");
}).catch((err) => {
    console.log("Not connected to the database", err);
})



const plantCycleSchema = new mongoose.Schema({
    temperature: {
        type: Number,
        required: true,
        minlength: 1,
    },
    humidity: {
        type: Number,
        required: true,
        minlength: 1,
    },
    light: {
        type: Number,
        required: true,
        minlength: 1,
    },
    soilMoisture: {
        type: Number,
        required: true,
        minlength: 1,
    },
    resevoir: {
        type: Boolean,
        required: true
    }
}, {timestamps: true});

const plantCycle = mongoose.model("PlantCycle", puzzleSchema);

module.exports = {
    plantCycle: plantCycle
}