// Skeleton code came from https://nathanmelenbrink.github.io/lab/networking/huzzah2.html.
#pragma once
#include <WiFi.h>
#include <HTTPClient.h>
// This include comes from the tutorial link at the very bottom.
#include <SPIFFS.h>
// I can't include this one without downloading from here:
// https://github.com/me-no-dev/ESPAsyncWebServer, https://github.com/me-no-dev/ESPAsyncTCP
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>



// Define the SSID & Password (Removing "const" fixed an error.)
char* network = "MAKERSPACE";
char* password = "12345678";
const String website = "https://pokemonshowdown.com/ladder/gen4randombattle.json";

// Web server from tech tutorials X
AsyncWebServer server(80); // HTTP Port
AsyncWebSocket ws("/test");


// Detects different statuses of the client-server connection. It also prints results to Serial.
void onWsEvent(AsyncWebSocket * server, AsyncWebSocketClient * client, AwsEventType type, void * arg, uint8_t *data, size_t len){
 
  if(type == WS_EVT_CONNECT){
 
    Serial.println("Websocket client connection received");
 
  } else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
    Serial.println("-----------------------");
 
  } else if(type == WS_EVT_DATA){
 
    Serial.print("Data received: ");
 
    for(int i=0; i < len; i++) {
          Serial.print((char) data[i]);
    }
 
    Serial.println();
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  SPIFFS.begin(true);
  if(!SPIFFS.begin()) {
     Serial.println("An Error has occurred while mounting SPIFFS");
     return;
  }
  // I'm mixing code from 2 tutorials. AHHHHHHH!
  
  WiFi.begin(network, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
  // Sets up events and handlers after beginning the Wi-Fi session.
  Serial.println("Connected to the WiFi network");
  ws.onEvent(onWsEvent);
  server.addHandler(&ws);

  // Listens to HTTP Get requests, and sets up a file to write data to.
  server.on("/html", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/ws.html", "text/html");
  });
  server.begin();

}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(website);
    // Seems like HTTP codes cannot be negative numbers.
    int httpCode = http.GET();
    if (httpCode) {
      delay(10000);
      String payload = http.getString();
      Serial.print(httpCode + " " + payload + '\n');
    } else {
      Serial.println("Error.");
    }
    http.end();
  }
  // Random Nerd Tutorials don't have a section for extracting data from a web site's JAVASCRIPT files. I looked at this tutorial:
  // https://techtutorialsx.com/2018/09/13/esp32-arduino-web-server-receiving-data-from-javascript-websocket-client/
  delay(10 * 1000);
  
}
