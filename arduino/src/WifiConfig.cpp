#include "WiFiConfig.h"
#include <EEPROM.h>

#include "ScreenConfig.h"

#define EEPROM_SIZE 96

void saveCredentials(const char* ssid, const char* password) {
    EEPROM.begin(EEPROM_SIZE);

    // Clear the areas first
    for (int i = 0; i < 64; i++) {
        EEPROM.write(i, 0);
    }

    // Write SSID (max 31 chars + null terminator)
    for (int i = 0; i < 31 && ssid[i] != '\0'; i++) {
        EEPROM.write(i, ssid[i]);
    }

    // Write password (max 31 chars + null terminator)
    for (int i = 0; i < 31 && password[i] != '\0'; i++) {
        EEPROM.write(i + 32, password[i]);
    }

    EEPROM.commit();
    EEPROM.end();

    Serial.println("Wi-Fi credentials saved to memory:");
    Serial.print("SSID saved: ");
    Serial.println(ssid);
    Serial.print("Password saved: ");
    Serial.println(password);
}

void clearEEPROM() {
    EEPROM.begin(EEPROM_SIZE);
    for (int i = 0; i < EEPROM_SIZE; i++) {
        EEPROM.write(i, 0);
    }
    EEPROM.commit();
    EEPROM.end();
    Serial.println("EEPROM cleared.");
}

void loadCredentials(String& ssid, String& password) {
    EEPROM.begin(EEPROM_SIZE);

    // Create temporary buffers to read the char arrays
    char ssid_temp[32] = {0};
    char pass_temp[32] = {0};

    // Read raw bytes from EEPROM into our buffers
    for (int i = 0; i < 32; i++) {
        char c = EEPROM.read(i);
        if (c == 0) break;
        if (!isprint(c)) break;
        ssid_temp[i] = c;
    }

    for (int i = 0; i < 32; i++) {
        char c = EEPROM.read(i + 32);
        if (c == 0) break;
        if (!isprint(c)) break;
        pass_temp[i] = c;
    }

    EEPROM.end();

    // Convert to Strings
    ssid = String(ssid_temp);
    password = String(pass_temp);

    // Debug output
    Serial.println("Loaded Wi-Fi credentials from memory:");
    Serial.print("SSID loaded: ");
    Serial.println(ssid);
    Serial.print("Password loaded: ");
    Serial.println(password);
}

bool connectToWiFi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting to Wi-Fi...");
    displayConnectingScreen();
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }
   
    if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Connected to Wi-Fi!");
            Serial.print("IP Address: ");
            Serial.println(WiFi.localIP());
            displaySuccessScreen();
            return true;
        }

    Serial.println("\nFailed to connect to Wi-Fi.");
    displayErrorScreen();
    return false;
}
