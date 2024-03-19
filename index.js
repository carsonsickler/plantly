const express = require('express');
const mongoose = require('mongoose');
const { Puzzle } = require('./path/to/your/mongoose/file');

require('dotenv').config();

// Connect to the database
mongoose.connect(process.env.DATABASE_URL).then(() => {
    console.log("Connected to the database");
}).catch((err) => {
    console.log("Not connected to the database", err);
});

// Import the Puzzle model

// Create an Express app
const app = express();

// Define routes
app.get('/', (req, res) => {
    res.send('Hello, world!');
});

// Start the server
const port = process.env.PORT || 3000;
app.listen(port, () => {
    console.log(`Server is running on port ${port}`);
});