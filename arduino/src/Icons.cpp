#include "Icons.h"

void drawHeart(Adafruit_GFX &tft, int x, int y) {
    tft.drawBitmap(x, y, heartBitmap, 39, 34, ST77XX_RED); // Draw heart at (x, y) with red color
}

void drawArrow(Adafruit_GFX &tft, int x, int y) {
    tft.drawBitmap(x, y, arrowBitmap,46, 23, ST77XX_WHITE); // Draw smiley at (x, y) with yellow color
}
