#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <ESP8266WiFi.h>

void saveCredentials(const char* ssid, const char* password);
void loadCredentials(String& ssid, String& password);
bool connectToWiFi(const char* ssid, const char* password);
void clearEEPROM();

#endif
