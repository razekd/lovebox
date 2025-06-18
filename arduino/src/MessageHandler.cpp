#include "MessageHandler.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

MessageHandler::MessageHandler(const char* serverUrl)
  : _serverUrl(serverUrl) {}

String MessageHandler::fetchMessage() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return "";
  }
  
  
  HTTPClient http;
  
  // For HTTPS URLs (recommended for production)
  if (String(_serverUrl).startsWith("https://")) {
    WiFiClientSecure client;
    client.setInsecure(); // Skip certificate validation (for testing)
    
    if (!http.begin(client, _serverUrl)) {
      Serial.println("Failed to initialize HTTPS connection");
      return "";
    }
  } else {
    // For HTTP URLs
    WiFiClient client;
    if (!http.begin(client, _serverUrl)) {
      Serial.println("Failed to initialize HTTP connection");
      return "";
    }
  }
  
  http.setTimeout(10000); 
  http.addHeader("User-Agent", "ESP8266-Arduino");
  http.addHeader("Content-Type", "application/json");
  
  int httpCode = http.GET();
  Serial.println("HTTP Response Code: " + String(httpCode));
  
  String result = "";
  if (httpCode == HTTP_CODE_OK || httpCode == 200) {
    String payload = http.getString();
    Serial.println("Response: " + payload);
    
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);
    
    if (!error) {
      result = doc["message"].as<String>();
    } else {
      Serial.println("JSON parsing failed: " + String(error.c_str()));
    }
  } else if (httpCode > 0) {
    Serial.println("HTTP Error: " + String(httpCode));
    String payload = http.getString();
    Serial.println("Error response: " + payload);
  } else {
    Serial.println("Connection failed: " + http.errorToString(httpCode));
  }
  
  http.end();
  return result;
}

bool MessageHandler::sendMessage(const String& message) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected");
    return false;
  }
  
  HTTPClient http;
  
  // For HTTPS URLs
  if (String(_serverUrl).startsWith("https://")) {
    WiFiClientSecure client;
    client.setInsecure(); // Skip certificate validation (for testing)
    
    if (!http.begin(client, _serverUrl)) {
      Serial.println("Failed to initialize HTTPS connection");
      return false;
    }
  } else {
    // For HTTP URLs
    WiFiClient client;
    if (!http.begin(client, _serverUrl)) {
      Serial.println("Failed to initialize HTTP connection");
      return false;
    }
  }
  
  http.setTimeout(10000);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("User-Agent", "ESP8266-Arduino");
  
  String postData = "{\"message\":\"" + message + "\"}";
  Serial.println("Sending: " + postData);
  
  int httpCode = http.POST(postData);
  Serial.println("POST Response Code: " + String(httpCode));
  
  bool success = (httpCode == HTTP_CODE_OK || httpCode == 200);
  
  if (success) {
    String response = http.getString();
    Serial.println("Server response: " + response);
  } else {
    Serial.println("POST failed: " + String(httpCode));
  }
  
  http.end();
  return success;
}
