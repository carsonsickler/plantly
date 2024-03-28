#include <WiFi.h>
#include <WebServer.h>
#include "dht11.h"
#define DHT11PIN 21

dht11 DHT11;

const char* ssid = "Mater";
const char* password = "password";

float temperature;
float humidity;

WebServer server(80);

void readSensors(){
  int chk = DHT11.read(DHT11PIN);
  temperature = (DHT11.temperature * 9/5) + 32;
  humidity = DHT11.humidity;
}

void setup(){
    Serial.begin(9600);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());

    server.on("/hello", HTTP_GET, []() {
      // send data as JSON
      //readSensors();
      //String json = "{\"temperature\": " + String(temperature, 2) + ", \"humidity\": " + String(humidity, 2) + "}";
      server.send(200, "text/plain", "hello");
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop(){
  server.handleClient();
}




// // the setup function runs once when you press reset or power the board
// #define RGB_BUILTIN 7
// void setup() {
//   // No need to initialize the RGB LED
// }

// // the loop function runs over and over again forever
// void loop() {
// #ifdef RGB_BUILTIN
//   digitalWrite(RGB_BUILTIN, HIGH);   // Turn the RGB LED white
//   delay(1000);
//   digitalWrite(RGB_BUILTIN, LOW);    // Turn the RGB LED off
//   delay(1000);

//   neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0); // Red
//   delay(1000);
//   neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
//   delay(1000);
//   neopixelWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS); // Blue
//   delay(1000);
//   neopixelWrite(RGB_BUILTIN,0,0,0); // Off / black
//   delay(1000);
// #endif
// }