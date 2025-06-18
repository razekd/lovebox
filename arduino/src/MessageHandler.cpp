#include "MessageHandler.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

MessageHandler::MessageHandler(const char* serverUrl) 
  : _serverUrl(serverUrl) {}

String MessageHandler::fetchMessage() {
  if (WiFi.status() != WL_CONNECTED) return "";

  Serial.println("Fetching message from server: " + String(_serverUrl));

  WiFiClient client;
  HTTPClient http;
  
//   http.begin(client, _serverUrl);

  if (!http.begin(client, _serverUrl)) {
    Serial.println("Failed to connect to server: " + String(_serverUrl));
    return "";
  }
  
  if (http.GET() == 200) {
    String payload = http.getString();
    
    JsonDocument doc;
    deserializeJson(doc, payload);
    return doc["message"].as<String>();
  }
    else {
        Serial.println("Failed to fetch message, HTTP error: " + String(http.errorToString(http.GET()).c_str()));
    }
  return "";
}

bool MessageHandler::sendMessage(const String& message) {
  if (WiFi.status() != WL_CONNECTED) return false;

  WiFiClient client;
  HTTPClient http;
  
  http.begin(client, _serverUrl);
  http.addHeader("Content-Type", "application/json");
  
  String postData = "{\"message\":\"" + message + "\"}";
  bool success = (http.POST(postData) == 200);
  http.end();
  return success;
}