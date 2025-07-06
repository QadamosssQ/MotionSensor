#include <ESP8266WiFi.h>
#include "request.h"
#include <ArduinoJson.h>

#define ir_pin 5

int configuration_ticks = 5; 
const char* apiURL = "https://discord.com/api/webhooks/1391484488772616405/5Y0kYvEr8bAB6EzTuG-L7LRvIfeC8g0k3ssy0Fkc5EYp8PkimNd1A_uBPa2kRMopmEDk";

void setup() {
  Serial.begin(115200);
  pinMode(ir_pin, INPUT_PULLUP);

  WiFi.begin("mobile-wifi", "ghta1284");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
}

void loop() {
  while (configuration_ticks != 0) {
    configuration_ticks--;

    if(WiFi.status() == WL_CONNECTED){
      if (digitalRead(ir_pin) == HIGH) {
        DynamicJsonDocument jsonDoc(1024);
        jsonDoc["content"] = "configuration: good";
        JsonObject jsonObject = jsonDoc.as<JsonObject>();
        String response = make_request(apiURL, jsonObject);
        Serial.println(response);
        delay(1000);
      }else{
        DynamicJsonDocument jsonDoc(1024);
        jsonDoc["content"] = "configuration: bad";
        JsonObject jsonObject = jsonDoc.as<JsonObject>();
        String response = make_request(apiURL, jsonObject);
        Serial.println(response);
        delay(1000);
      }
    }
    delay(10);
  }
  
  if(digitalRead(ir_pin) == HIGH) {
    DynamicJsonDocument jsonDoc(1024);
    jsonDoc["content"] = "motion detected";
    JsonObject jsonObject = jsonDoc.as<JsonObject>();
    String response = make_request(apiURL, jsonObject);
    Serial.println(response);
  }
}


