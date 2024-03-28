
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Mater";
const char* password = "password";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://localhost:3000/plants";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  Serial.begin(9600);
  delay(1000);

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
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
    
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"name\":\"janet\",\"type\":\"cactus\"}");


      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      if (httpResponseCode < 0) {
        Serial.print("HTTP Error: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

// the setup function runs once when you press reset or power the board
// #define RGB_BUILTIN 7
// void setup() {
//   Serial.begin(9600);
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
//   Serial.println("red");
//   delay(1000);
//   neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // Green
//   Serial.println("green");  
//   delay(1000);
//   neopixelWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS); // Blue
//   Serial.println("blue");
//   delay(1000);
//   neopixelWrite(RGB_BUILTIN,0,0,0); // Off / black
//   delay(5000);
// #endif
// }