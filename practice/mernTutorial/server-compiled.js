(()=>{var e={252:e=>{"use strict";e.exports=require("express")},518:e=>{"use strict";e.exports=require("mongodb")}},t={};function o(n){var s=t[n];if(void 0!==s)return s.exports;var r=t[n]={exports:{}};return e[n](r,r.exports,o),r.exports}(()=>{const e=o(252),{MongoClient:t}=o(518);let n;const s=e();s.set("view engine","ejs"),s.set("views","./views"),s.use(e.static("public")),s.get("/",(async(e,t)=>{const o=await n.collection("animals").find({}).toArray();console.log(o),t.render("home",{allAnimals:o})})),s.get("/admin",((e,t)=>{t.render("admin")})),async function(){const e=new t("mongodb://root:root@localhost:27017/AmazingMernApp?&authSource=admin");await e.connect(),n=e.db(),s.listen(3e3,(()=>{console.log("Example app listening at http://localhost:3000")}))}()})()})();