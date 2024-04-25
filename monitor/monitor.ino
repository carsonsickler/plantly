
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "dht11.h"
#define DHT11PIN 4

dht11 DHT11;
int waterSensorPin = 5;
const int pump1 = 6;
const int pump2 = 7;

const int dry = 2400;
const int wet = 1350;

float humidity;
float temperature;
float light;
int soilMoisture;
bool reservoir;
bool watered;

const char* ssid = "Mater"; //"Mater";
const char* password = "password"; //"password";
const char* serverName = "http://172.20.10.5:3000/plants/6605d893267d6ae57440d717/readings";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;


void setup() {
  Serial.begin(9600);
  pinMode(pump1, OUTPUT);
  pinMode(pump2, OUTPUT);
  pumpOff();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if(WiFi.status()== WL_CONNECTED){

      testPOST();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void readings() {
  int chk = DHT11.read(DHT11PIN);

  temperature = ((float)DHT11.temperature * (9/5) + 32);
  humidity = ((float)DHT11.humidity);

  // Full sun: 6+ hours
  // Partial sun: 4-6 hours
  // Partial shade: 1.5 – 4 hours
  // Full shade: less then 1.5 hours
  light = analogRead(A2);

  soilMoisture = analogRead(A3);
  if(soilMoisture >= dry){
    if (digitalRead(5)){
      water();
    } else {
      Serial.println("No Water in reservoir");
    }
  } else {
    Serial.println("No need to water");
  }

  if (digitalRead(5)){
    reservoir = true;
  } else {
    reservoir = false;
  }
}

void pumpOff(){
  digitalWrite(pump1, LOW);
  digitalWrite(pump2, LOW);
}

void pumpOn(){
  digitalWrite(pump1, HIGH);
  digitalWrite(pump2, LOW);
}

void water(){
  Serial.println("watering");
  pumpOn();
  delay(5000);
  pumpOff();
  watered = true;
}

void waterPlant() {
  //TODO
  watered = true;
}

void testPOST() {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);
  http.addHeader("Content-type", "application/json");
  readings(); // Call the readings function to update the variables

  // Create a JSON object
  JsonDocument jsonDoc;
  
  // Add variables to the JSON object
  jsonDoc["temperature"] = temperature;
  jsonDoc["humidity"] = humidity;
  jsonDoc["light"] = light;
  jsonDoc["soilMoisture"] = soilMoisture;
  jsonDoc["reservoir"] = reservoir;
  jsonDoc["watered"] = watered;

  // Serialize the JSON object to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send the JSON string via POST request
  int httpResponseCode = http.POST(jsonString);

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  watered = false;    
  // Free resources
  http.end();
}

