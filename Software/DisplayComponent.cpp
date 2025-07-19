// To use hardware SPI With the ESP32c3, get this version of the TFT_eSPI library:
// https://github.com/AndroidCrypto/TFT_eSPI?tab=readme-ov-file
// Use the "Download ZIP" option under the Code button, unzip it, and put the directory in your "Arduino/libraries" folder.
// Add this line to the User_Setup_Select.h file in the library:
// #include <My_User_Setups/Setup702_C3_SM_ST7735_128x160.h>
// For more information:
// https://medium.com/@androidcrypto/getting-started-with-an-esp32-c3-supermini-device-connected-to-an-st7735-tft-display-6ba1a1027a88

#include "SPI.h"
#include "TFT_eSPI.h"

#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
//#include <Fonts/FreeMonoBold24pt7b.h>
#include "History.h"
#include "DisplayComponent.h"

#define ARDUINO_SEEED_XIAO_ESP32C3

#ifdef ARDUINO_SEEED_XIAO_ESP32C3
    #warning Display = Xiao ESP32C3
    #define TFT_DC D1
    #define TFT_CS D0
    #define TFT_RST D2
    #define TFT_MOSI D10
    #define TFT_SCLK D8  
    //Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
    TFT_eSPI tft = TFT_eSPI();

#elif SEEED_XIAO_M0
    #warning Display = Xiao SAMD21

    // Pin configuration
    #define TFT_CS        0
    #define TFT_RST       -1 // not used
    #define TFT_DC        1
    Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

#else
    #warning Display is not configured, see DisplayComponent.cpp
#endif


// Left/right split
//GFXcanvas16 canvas(width/2, height);
// Top/bottom split
GFXcanvas16 canvas(width, height/2);

void DisplayComponent::initialize()
{
  Serial.print("Display: ");
#ifdef SEEED_XIAO_M0  
  Serial.printf("Clock %d\r\n", F_CPU);
  Serial.printf("SPI   %d\r\n", MAX_SPI);
  Serial.printf("divid %d\r\n", SPI_MIN_CLOCK_DIVIDER);
#endif

  // https://learn.adafruit.com/1-8-tft-display/breakout-wiring-and-test 
  tft.init(INITR_BLACKTAB);      // Init ST7735S chip, black tab

  // landscape, through-holes on left side
  tft.setRotation(3);

  tft.fillScreen(BLACK);
  canvas.fillScreen(BLACK);

  Serial.println("Initialized.");
}

void DisplayComponent::draw(History *pHistory, int temperature)
{
  char szTemperature[5];
  itoa(temperature, szTemperature, 10);

  // Draw the top half and then the bottom half.
  // Because there isn't enough RAM to buffer the entire screen.
  canvas.fillScreen(BLACK);

  canvas.setFont(&FreeMonoBold24pt7b);
  canvas.setCursor(30, 48);
  canvas.setTextColor(LIGHTGREY);
  canvas.print(szTemperature);

  drawHistoryTop(pHistory, LIGHTBLUE);
  tft.drawBitmap(0, 0, canvas.getBuffer(), width, height/2);

  canvas.fillScreen(BLACK);
  drawHistoryBottom(pHistory, YELLOW);
  tft.drawRGBBitmap(0, height / 2, canvas.getBuffer(), width, height/2);
}

void DisplayComponent::drawHistoryTop(History *pHistory, uint16_t color)
{
  for (int x = 0; x < width; x++)
  {
    int y = pHistory->get(width - x);
    if (y > height / 2)
    {
      canvas.drawPixel(x, height - y, color);
      canvas.drawPixel(x, (height - y) - 1, color);
    }
  }
}

void DisplayComponent::drawHistoryBottom(History *pHistory, uint16_t color)
{
  for (int x = 0; x < width; x++)
  {
    int y = pHistory->get(width - x);
    if (y <= height / 2)
    {
      canvas.drawPixel(x, height / 2 - y, color);
      canvas.drawPixel(x, (height / 2 - y) - 1, color);    
    }
  }
}




  // The XIAO SAMD21 doesn't have enough RAM to buffer the entire display
  // So we do the left half and then the right half.
  /*
  canvas.fillScreen(BLACK);
  for (int x = 0; x < width / 2; x++)
  {
    int y = height - history.get(width - x);
    canvas.drawPixel(x, y, WHITE);
  }
  tft.drawRGBBitmap(0, 0, canvas.getBuffer(), width/2, height);

  canvas.fillScreen(BLACK);
  for (int x = width / 2; x < width; x++)
  {
    int y = height - history.get(width - x);
    canvas.drawPixel(x - width / 2, y, WHITE);
  }
  tft.drawRGBBitmap(width/2, 0, canvas.getBuffer(), width/2, height);  
  */

