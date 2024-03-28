const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const { Plant } = require('./model.js');
const { Readings } = require('./model.js');

require('dotenv').config();

// Connect to the database
mongoose.connect(process.env.DATABASE_URL).then(() => {
    console.log("Connected to the database");
}).catch((err) => {
    console.log("Not connected to the database", err);
});


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
app.get('/plants', (req, res) => {
    Plant.find().then((plants) => {
        res.json(plants);
    });
});

// Get a Plant by id
app.get('/plants/:id', (req, res) => {
    Plant.findById(req.params.id).then((plant) => {
        res.json(plant);
    });
});

// Create a new Plant
app.post('/plants', (req, res) => {
    const plant = new Plant(req.body);
    plant.save().then((plant) => {
        res.json(plant);
        console.log(plant);
    });
})


// Add a new reading to Plant with id
app.post('/plants/:id/readings', (req, res) => {
    Plant.findById(req.params.id).then((plant) => {
        console.log(req.body);
        const readings = new Readings(req.body);
        readings.save().then((readings) => {
            plant.data = readings;
            plant.save().then(() => {
                res.json(readings);
            });
        }).catch((err) => {
            res.status(400).json(err);
        });

    });
});


// Start the server
const port = process.env.PORT || 3000;
app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});