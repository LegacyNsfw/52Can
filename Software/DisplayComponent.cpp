#include <Arduino_GFX_Library.h>
#include <font/u8g2_font_chill7_h_cjk.h>
//#include <font/u8g2_font_cubic11_h_cjk.h>
#include "Test.h"
#include "Constants.h"
#include "History.h"
#include "DisplayComponent.h"

Arduino_DataBus *bus = nullptr;
Arduino_GFX *display = nullptr;    
Arduino_GFX *canvas = nullptr;

#define TEXT_HEIGHT 12

// Colors are wonky:
// red -> green
// green -> blue
// blue -> very light blue

void DisplayComponent::initialize()
{
  Serial.println("Creating bus...");  
  bus =  new Arduino_ESP32SPI(DC, CS, SCLK, MOSI, BL);
  
  Serial.println("Creating display...");
  display = new Arduino_ST7735(
    bus,
    2, //  RST
    3, // rotation - this is what unswaps the x and y below
    true, // ips
    height, // x
    width // y
  );

  Serial.println("Creating canvas...");
  canvas = new Arduino_Canvas(width, height, display, 0, 0, 0);
    
  Serial.println("Starting GFX...");
  int speed = 12 * 1000 * 1000;
  
  // This approach doesn't work - only a corner of the display ends up being drawn.
  // display->begin() calls tftInit(), which is required.
  // bus->begin(speed, SPI_MODE0); 
  
  // This works, but not if you use a canvas.
  // display->begin(speed);

  // This allocates memory for the canvas framebuffer, and calls begin() on the display, and initializes the bus.
  canvas->begin(speed);

  Serial.println("Clearing display...");  
  display->fillScreen(RGB565_BLACK);
  Serial.println("Display initialized.");  
}

void toAfr(uint16_t aemLambda, char *szAfr)
{
  // Convert AEM Lambda to AFR
  float lambda = aemLambda / 10000.0; // Convert to Lambda
  float afr = 14.7 * lambda;
  
  // Convert to string
  dtostrf(afr, 4, 2, szAfr);
}

int getYCoordinateForAemLambda(uint16_t aemLambda)
{
  // Rescale the value so that MIN_LAMBDA is zero and MAX_LAMBDA is height-TEXT_HEIGHT.
  int result = (aemLambda - MIN_LAMBDA) * (height - TEXT_HEIGHT) / (MAX_LAMBDA - MIN_LAMBDA);
  
  if (result < 1)
  {
    result = 1;
  }
  else if (result >= height)
  {
    result = height - 1;
  }
  
  return (height - result);
}

void DisplayComponent::draw(History *pHistory1, History *pHistory2, int temperature)
{ 
  canvas->fillRect(0, 0, width, height, WTF_BLACK);

  //char szTemperature[5];
  //itoa(temperature, szTemperature, 10);
  uint16_t leftAfr = pHistory1->get(width);
  uint16_t rightAfr = pHistory2->get(width);

  char szLeftAfr[7];
  char szRightAfr[7];
  toAfr(leftAfr, szLeftAfr);
  toAfr(rightAfr, szRightAfr);

  canvas->setTextSize(2);
  
  canvas->setCursor(0, 0);
  canvas->setTextColor(WTF_GREEN);
  canvas->print(szLeftAfr);

  canvas->setCursor(100, 0);
  canvas->setTextColor(WTF_BLUE);
  canvas->print(szRightAfr);

  int stoichLine = getYCoordinateForAemLambda(10000);
  canvas->drawFastHLine(0, stoichLine, width, WTF_GREY);

  int powerLine = getYCoordinateForAemLambda(8500);
  canvas->drawFastHLine(0, powerLine, width, WTF_GREY);

  // Still not sure how to get fonts to work...
  // canvas->setFont(u8g2_font_chill7_h_cjk);
  // canvas->setFont(u8g2_font_cubic11_h_cjk);
  // canvas->setTextColor(WTF_WHITE);
  // canvas->print(szTemperature);

  drawHistory(pHistory1, WTF_GREEN);
  drawHistory(pHistory2, WTF_BLUE);
  canvas->flush(); 
}

void DisplayComponent::drawHistory(History *pHistory, int color)
{
  for (int x = 0; x < (width-5); x++)
  {
    uint16_t value = pHistory->get(width - x);
    int y = getYCoordinateForAemLambda(value);
    canvas->drawPixel(x, y, color);
  }
}
