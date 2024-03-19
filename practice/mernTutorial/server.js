const express = require('express')
const { MongoClient } = require('mongodb')
const port = 3000
let db;

const app = express()

app.set('view engine', 'ejs')
app.set('views', './views')
app.use(express.static('public'))



app.get('/', async (req, res) => {
    const allAnimals = await db.collection('animals').find({}).toArray()
    console.log(allAnimals)
    res.render('home', { allAnimals })
})

app.get('/admin', (req, res) => {
    res.render('admin')
})

async function start() {
    const client = new MongoClient("mongodb://root:root@localhost:27017/AmazingMernApp?&authSource=admin")
    await client.connect()
    db = client.db()
    app.listen(port, () => {
        console.log(`Example app listening at http://localhost:${port}`)
    })
}

start()
