const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const { Plant } = require('./model.js');
const { Readings } = require('./model.js');


// Create an Express app
const app = express();
app.use([
    express.urlencoded({ extended: true }),
    cors(),
    express.static("public"),
    express.json()
]);

// Define routes

// Get list of all Plants
app.get('/plants', async (req, res) => {
    try {
        const plants = await Plant.find();
        res.json(plants);
    } catch (err){
        let errorMessage = {}
        if (err.errors){
            errorMessage.details = {}
            Object.keys(err.errors).forEach((key) => {
                errorMessage.details[key] = err.errors[key].message;
            });
            res.status(422).json(errorMessage);
        }
    }
});

// Get a Plant by id
app.get('/plants/:id', (req, res) => {
    Plant.findById(req.params.id).then((plant) => {
        res.json(plant);
    });
});

// Create a new Plant
app.post('/plants', (req, res) => {
    if (!req.body.name) {
        return res.status(400).json({ error: 'Name is required' });
    }
    if (!req.body.type) {
        return res.status(400).json({ error: 'Type is required' });
    }
    try {
        const plant = new Plant(req.body);
        plant.save().then((plant) => {
            res.json(plant);
        });
    } catch (err) {
        res.status(400).json(err);
    }
})


// Add a new reading to Plant with id
app.post('/plants/:id/readings', (req, res) => {
    console.log(req.body);
    Plant.findById(req.params.id).then((plant) => {
        if (req.body.watered == true) {
            plant.lastWatered = Date.now();
        }
        const readings = new Readings({
            temperature: req.body.temperature,
            humidity: req.body.humidity,
            light: req.body.light,
            soilMoisture: req.body.soilMoisture,
            reservoir: req.body.reservoir
        });
        plant.readings.push(readings);
        plant.save().then((plant) => {
            res.json(plant);
        });
    });
});


// Start the server
const port = process.env.PORT || 3000;
app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});


// Full sun: 6+ hours
// Partial sun: 4-6 hours
// Partial shade: 1.5 – 4 hours
// Full shade: less then 1.5 hours

// Direct bright light (sunny spot): between 20.000 and 50.000 lux
// Indirect bright light (partial sunny): entre 10.000 y 20.000 lux
// Medium light (half-shade): entre 2.500 y 10.000 lux
// Low light (shade): entre 500 y 2500 lux