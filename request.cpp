#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

String make_request(String url, JsonObject& jsonPayload) {
  WiFiClientSecure wifi;
  wifi.setInsecure();
  HTTPClient http;

  http.begin(wifi, url);

  String payload;
  serializeJson(jsonPayload, payload);

  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(payload);

  if (httpResponseCode == 204) {
    String response = http.getString();
    http.end();
    return response;
  } else {
    Serial.print("HTTP Error: ");
    Serial.println(httpResponseCode);
    http.end();
    return "error";
  }
}
