#include "WebServerConfig.h"
#include "Icons.h"
#include "ScreenConfig.h"


// Initialize the display object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

#define BUTTON_PIN D6
const int DEBOUNCE_DELAY = 50;

// Button state variables
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;


void setupDisplay() {
  // Initialize the display
    tft.init(240, 280); // 240x240 display, check SPI mode based on your display

    tft.setRotation(3); // Set display rotation (0-3)
    tft.fillScreen(ST77XX_BLACK); // Clear the screen
}

void displayWelcomeScreen() {
    tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setTextSize(3);
    tft.setTextColor(ST77XX_WHITE);

    // Draw heart icons
    // drawHeart(tft, 100, 50); // Positioning for first heart icon
    // drawHeart(tft, 140, 50); // Positioning for second heart icon


    tft.setCursor(80, 50); // Centered text positioning
    tft.print("Hello !");
    tft.setTextSize(2);

    tft.setCursor(30, 100);
    tft.print("To configure your");

    tft.setCursor(100, 120);
    tft.print("LoveBox");
      
    tft.setCursor(30, 140);
    tft.print("connect your phone ");
    tft.setCursor(40, 160);
    tft.print("to the LoveBox-AP");

    tft.setCursor(100, 180);
    tft.print("network");

    delay(4000);

    // Add black square to erase content below "Hello!"
    tft.fillRect(0, 70, tft.width(), tft.height() - 70, ST77XX_BLACK); 

    // Print new content
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(40, 100);
    tft.print("Open your browser");
    tft.setCursor(90, 120);
    tft.print("to go to ");
    tft.setCursor(70, 140);
    tft.print("192.168.4.1");
    
}

void displayConnectingFromSaved(){
   tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    
    // Centered text
    tft.setCursor(70, 100);
    tft.print("Using saved ");

    tft.setCursor(70, 130);
    tft.print("credentials");
  
}

void displayConnectingScreen() {
    tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    
    // Centered text
    tft.setCursor(40, 80);
    tft.print("Connecting to the");
    
    tft.setCursor(60, 100);
    tft.print("server of Love");

    drawHeart(tft, 120, 140);

    // tft.setCursor(110, 160);
    // tft.print(attempts+1);
    // tft.setCursor(130, 160);
    // tft.print(" / 3");

    
}
// void displaySuccessScreen(String name) {
  void displaySuccessScreen() {
    tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    
    // Centered text
    tft.setCursor(50, 80); // Adjust based on text length
    tft.print("Your Lovebox is");
    
    tft.setCursor(50, 100); // Adjust based on text length
    tft.print("ready to receive");

    tft.setCursor(90, 120); // Adjust based on text length
    tft.print("messages!");
}

void displayErrorScreen() {
    tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    
    // Centered text
    tft.setCursor(40, 80);
    tft.print("Connecting to the");
    
    tft.setCursor(60, 100);
    tft.print("server failed");

    tft.setCursor(45, 120);
    tft.print("please try again");
}


  void displayMessagesFlow(String newMessages) {
    tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);
    
    // Centered text
    tft.setCursor(50, 80); // Adjust based on text length
    tft.print("Fetching messages");
    // ANimation until callback from firebase

    tft.fillScreen(ST77XX_BLACK); // Clear the screen
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);

    String text_concat = " new message(s)";

    tft.setCursor(70, 80);
    tft.print("You have");

    text_concat = newMessages + text_concat;
    
    tft.setCursor(30, 100);
    tft.print(text_concat);

    tft.setCursor(50, 120);
    tft.print("Press confirm to");

    tft.setCursor(60, 140);
    tft.print("continue ... ");
}
void findWordBoundary(const String& content, unsigned int position, int& newPosition) {
    // If at or past the end of string
    if (position >= content.length()) {
        newPosition = content.length();
        return;
    }
    
    // If position exceeds content length, find last word break
    if (position > content.length()) {
        position = content.length();
    }
    
    // Look backwards from position to find first space
    while (position > 0 && content.charAt(position) != ' ') {
        position--;
    }
    
    // If we found a space, use it
    if (position > 0) {
        newPosition = position;
        return;
    }
    
    // If we're at the start and no space found, look forward
    int nextSpace = content.indexOf(' ');
    if (nextSpace != -1) {
        newPosition = nextSpace;
    } else {
        // If no spaces at all, use entire content
        newPosition = content.length();
    }
}

// void displayMessageSequence(const Message& msg) {
//     pinMode(BUTTON_PIN, INPUT);
//     String fullContent = msg.content;
//     const int CHUNK_SIZE = 90;  
    
//     // Count chunks and store boundaries
//     std::vector<int> chunkBoundaries;
//     int currentPos = 0;
    
//     while (currentPos < fullContent.length()) {
//         int endPos;
//         findWordBoundary(fullContent, min(currentPos + CHUNK_SIZE, (int)fullContent.length()), endPos);
//         chunkBoundaries.push_back(endPos);
//         currentPos = endPos + (endPos < fullContent.length() ? 1 : 0);
//     }
    
//     // Display chunks
//     Message tempMsg;
//     tempMsg.title = msg.title;
//     int currentChunk = 0;
//     int startPos = 0;
    
//     // Show first chunk
//     String chunkContent = fullContent.substring(startPos, chunkBoundaries[0]);

//     tempMsg.content = chunkContent;
//     displayMessage(tempMsg);
//     tft.setCursor(125, 210);
//     String text = "/4";
//     text = String(currentChunk + 1) + text; // Convert the number to a string and concatenate
//     tft.println(text);

//     Serial.println("Waiting for button press");
    
//     while(true) {
//         int reading = digitalRead(BUTTON_PIN);
//         if(reading == HIGH) {
//             Serial.println("Button pressed");
            
//             currentChunk = (currentChunk + 1) % chunkBoundaries.size();  // Wrap around to 0
//             startPos = (currentChunk == 0) ? 0 : chunkBoundaries[currentChunk - 1] + 1;
            
//             // Get content for current chunk
//             String chunkContent = fullContent.substring(startPos, chunkBoundaries[currentChunk]);
            
//             tempMsg.content = chunkContent;
//             displayMessage(tempMsg);
//             tft.setCursor(125, 210);
//             String text = "/4";
//             text = String(currentChunk + 1) + text; // Convert the number to a string and concatenate
//             tft.println(text);
//             delay(200);  // Simple debounce
//         }
//         delay(50);  // Prevent CPU hogging
//     }
// }

// void displayMessage(const Message& msg) {
//     const int MAX_CHARS_PER_LINE = 20;
//     const int LINE_HEIGHT = 25;
//     const int START_Y = 30;
//     int MARGIN_X = 20;
//     const int TEXT_SIZE = 2;
//     const int CONTENT_START_Y = START_Y + LINE_HEIGHT * 2;
//     const int TITLE_UNDERLINE_Y = START_Y + LINE_HEIGHT - 5;
    
//     // Only clear the content area, not the title
//     tft.fillRect(0, CONTENT_START_Y, tft.width(), tft.height() - CONTENT_START_Y, ST77XX_BLACK);
    
//     tft.setTextSize(TEXT_SIZE);
//     tft.setTextColor(ST77XX_WHITE);
    
//     // Display Title (only if this is first chunk)
//     static String lastTitle;
//     if (lastTitle != msg.title) {
//         tft.fillRect(0, 0, tft.width(), CONTENT_START_Y, ST77XX_BLACK);
//         tft.setCursor(MARGIN_X, START_Y);
//         tft.setTextSize(TEXT_SIZE);
//         tft.println(msg.title);
        
//         tft.drawLine(MARGIN_X, TITLE_UNDERLINE_Y, tft.width() - MARGIN_X, TITLE_UNDERLINE_Y, ST77XX_WHITE);
//         lastTitle = msg.title;
//     }
    
//     tft.setTextSize(TEXT_SIZE);
//     String content = msg.content;
//     int currentLine = 2;
//     int currentPos = 0;
//     bool isLastLine = false;
    
//     while (currentPos < (int)content.length() && !isLastLine) {
//         int remainingLines = 7 - currentLine;
//         if (remainingLines <= 1) isLastLine = true;
        
//         int nextPos = currentPos + MAX_CHARS_PER_LINE;
//         if (nextPos < content.length()) {
//             while (nextPos > currentPos && content.charAt(nextPos) != ' ') {
//                 nextPos--;
//             }
//             if (nextPos == currentPos) {
//                 nextPos = currentPos + MAX_CHARS_PER_LINE;
//             }
//         } else {
//             nextPos = content.length();
//         }
        
//         String line = content.substring(currentPos, nextPos);
        
//         tft.setCursor(MARGIN_X, START_Y + (currentLine * LINE_HEIGHT));
//         tft.println(line);
        
//         if (isLastLine) break;
        
//         currentPos = nextPos;
//         if (currentPos < content.length() && content.charAt(currentPos) == ' ') currentPos++;
//         currentLine++;
//     }
// }

// void displayLatestMessage(const Message& msg) {
//   if (msg.isNew){
//     turnServo();
//     // updateIsNew(msg);
//     Serial.println("Reseting status");
//     displayMessageSequence(msg);
//   } else{
//     displayMessageSequence(msg);
//   }
// }


