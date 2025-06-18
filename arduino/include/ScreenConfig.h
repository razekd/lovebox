#ifndef SCREEN_CONFIG_H
#define SCREEN_CONFIG_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <Time.h>

#include "Icons.h"

#define TFT_DC    D1     // TFT DC  pin is connected to NodeMCU pin D1 (GPIO5)
#define TFT_RST   D2     // TFT RST pin is connected to NodeMCU pin D2 (GPIO4)
#define TFT_CS    D8     // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)
#define CAPACITIVE_PIN D6

extern Adafruit_ST7789 tft;

// Function prototypes
void setupDisplay();

void displayWelcomeScreen();
void displayConnectingScreen();
// void displaySuccessScreen(String name);
void displaySuccessScreen();
void displayErrorScreen();
void displayConnectingFromSaved();

void drawHeart(int x, int y);
void drawSmiley(int x, int y);


// int calculateScreensNeeded(const Message& msg);
// void displayMessage(const Message& msg);
// void displayLatestMessage(const Message& msg);

#endif 
