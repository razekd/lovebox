#include <ESP8266WebServer.h>
#include "WebServerConfig.h"
#include "WiFiConfig.h"

ESP8266WebServer server(80);

const char* wifiPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            align-items: center;
            justify-content: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
        }
        .container {
            width: 100%;
            max-width: 400px;
            padding: 20px;
            background-color: #ffffff;
            border-radius: 8px;
            box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.1);
        }
        h2 {
            text-align: center;
            color: #333333;
        }
        label {
            display: block;
            margin-top: 15px;
            font-size: 16px;
            color: #555555;
        }
        input[type="text"],
        input[type="password"] {
            width: 95%;
            padding: 10px;
            margin-top: 5px;
            border: 1px solid #cccccc;
            border-radius: 4px;
            font-size: 16px;
        }
        input[type="submit"] {
            width: 100%;
            padding: 10px;
            margin-top: 20px;
            background-color: #1b1b1b;
            border: none;
            color: white;
            font-size: 16px;
            border-radius: 4px;
            cursor: pointer;
        }
        input[type="submit"]:hover {
            background-color: #333333;
        }
    </style>
</head>
<body>
    <div class="container">
        <h2>Wi-Fi Configuration</h2>
        <form action="/submit" method="POST" accept-charset="UTF-8">
            <label>SSID:</label>
            <input type="text" name="ssid" required>
            <label>Password:</label>
            <input type="password" name="wifiPassword" required>
            <input type="submit" value="Connect">
        </form>
    </div>
</body>
</html>
)rawliteral";

void setupWebServer() {
    server.on("/", HTTP_GET, []() {
        server.send(200, "text/html", wifiPage);
    });

    server.on("/submit", HTTP_POST, []() {
        String ssid = server.arg("ssid");
        String password = server.arg("wifiPassword");
        saveCredentials(ssid.c_str(), password.c_str());

        String response = R"rawliteral(
            <!DOCTYPE html>
            <html>
            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>Configuration Saved</title>
            </head>
            <body style="font-family: Arial, sans-serif; text-align: center; margin-top: 50px;">
                <h2>Wi-Fi Configuration Saved</h2>
                <p>Device is now connecting to the network...</p>
                <p>You can close this window.</p>
            </body>
            </html>
        )rawliteral";

        server.send(200, "text/html", response);
        delay(3000);

        WiFi.softAPdisconnect(true);
        if (!connectToWiFi(ssid.c_str(), password.c_str())) {
            Serial.println("Failed to connect to Wi-Fi.");
        }
    });

    server.begin();
}


void handleWebServer()
{
    server.handleClient();
}

