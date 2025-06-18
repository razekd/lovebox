
#include "WiFiConfig.h"
#include "MessageHandler.h"  
#include "ScreenConfig.h"
#include "WebServerConfig.h"
#include "Config.h"  

#include <EEPROM.h>
#include <Arduino.h>

#define CAPACITIVE_PIN D6
#define RESET_HOLD_TIME 3000


MessageHandler messageHandler(SERVER_URL);  

// Function to check for reset button hold before setup
void checkForResetBeforeSetup() {
    unsigned long buttonPressTime = 0; 
    pinMode(CAPACITIVE_PIN, INPUT);    

    Serial.println("Checking for reset button hold...");

    // Wait and check if button is pressed
    while (digitalRead(CAPACITIVE_PIN) == HIGH) {
        if (buttonPressTime == 0) {
            buttonPressTime = millis(); // Record when the button was first pressed
        }

        // If button is held long enough
        if (millis() - buttonPressTime >= RESET_HOLD_TIME) {
            Serial.println("Reset button held. Clearing EEPROM...");
            clearEEPROM();
            ESP.restart(); // Restart the ESP after clearing EEPROM
        }

        delay(10); // Small delay to avoid busy-looping
    }

    Serial.println("No reset button detected. Continuing with setup.");


    
}


void setup() {
    Serial.begin(115200);
    delay(2000);
    checkForResetBeforeSetup();
    setupDisplay();

    String ssid, password;
    loadCredentials(ssid, password);

    if (!ssid.isEmpty() && !password.isEmpty()) {
        displayConnectingFromSaved();
        delay(2000);
        if (connectToWiFi(ssid.c_str(), password.c_str())) {
            String welcomeMsg = messageHandler.fetchMessage();
            if (!welcomeMsg.isEmpty()) {
                Serial.println("Received Message: " + welcomeMsg);
            }    
        }    
    } else {
        displayWelcomeScreen();
        WiFi.softAP("WiFi_Config_AP", "password1234");
        setupWebServer();
    }    
}    

void loop() {
    handleWebServer();
    
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 10000 && WiFi.status() == WL_CONNECTED) {
        String newMessage = messageHandler.fetchMessage();
        if (!newMessage.isEmpty()) {
            Serial.println("New Message: " + newMessage);
        }    
        lastCheck = millis();
    }    
}    



