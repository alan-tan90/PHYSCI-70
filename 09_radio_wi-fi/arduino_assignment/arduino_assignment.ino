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

struct ShowdownPlayer {
  String m_username;
  String m_elo;
  ShowdownPlayer(String, String);
};

ShowdownPlayer::ShowdownPlayer(String username, String elo): m_username(username), m_elo(elo) {
  
}

// Define the SSID & Password (Removing "const" fixed an error.)
char* network = "MAKERSPACE";
char* password = "12345678";
const String website = "https://pokemonshowdown.com/ladder/gen4randombattle.json";

// Make an array for player classes. I would do more than 10, but I need to conserve RAM. I'll stick to usernames and ELO rankings.
// I assigned it this way to prevent an error. All of this has to be overwritten, anyway.
ShowdownPlayer players[10] = {ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null"), ShowdownPlayer("null", "null")};
  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  // I was mixing code from 2 tutorials. AHHHHHHH!
  
  WiFi.begin(network, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println(WiFi.localIP());
  // Sets up events and handlers after beginning the Wi-Fi session.
  Serial.println("Connected to the WiFi network.");

}

// This was originally going to modify the payload, but I ended up realizing that I should just make a new Player class array that has "cleaned" up data.
void modifyPayload(String &str, ShowdownPlayer* showdownPlayers) {
  
  // This marks the "new start" of the "file".
  size_t index = str.indexOf("[") + 1;
  size_t newIndex = index;
  int j = 0;
  for(ShowdownPlayer *i = showdownPlayers; j < 10; *i++) {
    index = str.indexOf("\"username\":", index) + 12;
    newIndex = str.indexOf(',', index);
    String username = str.substring(index, newIndex - 1);
    index = str.indexOf("\"elo\":", index) + 6;
    newIndex = str.indexOf('}', index);
    String ELO = str.substring(index, newIndex);
    *i = ShowdownPlayer(username, ELO);
    j++;
  }
  
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(website);
    
    int httpCode = http.GET();
    if (httpCode > 0) {
      delay(4000);
      
      String payload = http.getString();
      
      ShowdownPlayer* showdownPlayers = players; 
      modifyPayload(payload, showdownPlayers);
      
      for(int i = 0; i < 10; i++) {
        Serial.print("\n");
        Serial.print(players[i].m_username);
        Serial.print(" has an ELO of ");
        Serial.print(players[i].m_elo);
      }
      Serial.println("\n--------------- END OF DATA ---------------");
    } else {
      Serial.println("Error.");
    }
    http.end();
  }
  // Random Nerd Tutorials don't have a section for extracting data from a web site's JAVASCRIPT files. I looked at this tutorial:
  // I ended up using a ".json" file from Pokemon Showdown. This can change dynamically.
  // https://techtutorialsx.com/2018/09/13/esp32-arduino-web-server-receiving-data-from-javascript-websocket-client/
  delay(1000);
  
}
