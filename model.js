const mongoose = require('mongoose');
require('dotenv').config();
mongoose.connect(process.env.DATABASE_URL).then(() => {
    console.log("Connected to the database");
}).catch((err) => {
    console.log("Not connected to the database", err);
})


const readingsSchema = new mongoose.Schema({
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
    reservoir: {
        type: Boolean,
        required: true
    }
}, {timestamps: true});

const plantSchema = new mongoose.Schema({
    name: {
        type: String,
        required: true,
        minlength: 1,
    },
    type: {
        type: String,
        required: true,
        minlength: 1,
    },
    readings: {
        type: [readingsSchema],
        ref: "Readings"
    },
    lastWatered: {
        type: Date,
        required: true,
        default: Date.now
    }
});

const Plant = mongoose.model("Plant", plantSchema);
const Readings = mongoose.model("Readings", readingsSchema);

module.exports = {
    Plant: Plant,
    Readings: Readings
}