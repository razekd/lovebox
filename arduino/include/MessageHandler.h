#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <Arduino.h>
#include <ESP8266HTTPClient.h> 
#include <ArduinoJson.h>

class MessageHandler {
  public:
    MessageHandler(const char* serverUrl);
    String fetchMessage();
    bool sendMessage(const String& message);
  
  private:
    const char* _serverUrl;
};

#endif