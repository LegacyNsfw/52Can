#include <Arduino_GFX_Library.h>
#include "Test.h"
#include "Constants.h"
#include "History.h"
#include "DisplayComponent.h"

Arduino_DataBus *bus = nullptr;
Arduino_GFX *display = nullptr;    
Arduino_GFX *canvas = nullptr;

// Colors are wonky:
// red -> green
// green -> blue
// blue -> very light blue

#define SWAPXY

int count;

void DisplayComponent::initialize()
{  
  count = 0;
  Serial.println("Creating bus...");  
  bus =  new Arduino_ESP32SPI(DC, CS, SCLK, MOSI, BL);
  
  Serial.println("Creating display...");

#ifdef SWAPXY
  display = new Arduino_ST7735(
    bus,
    2, //  RST
    3, // rotation - this is what unswaps the x and y below
    true, // ips
    height, // x
    width // y
  );
#else
  display = new Arduino_ST7735(
    bus,
    2, //  RST
    3, // rotation - this is what unswaps the x and y below
    true, // ips
    width, // x
    height // y
  );
#endif  

  Serial.println("Creating canvas...");
#ifdef SWAPXY  
  canvas = new Arduino_Canvas(height, width, display, 0, 0, 0);
#else
  canvas = new Arduino_Canvas(width, height, display, 0, 0, 0);
#endif


  // The Adafruit ST7735 breakout board is natively in portrait mode, and this app wants landscape.
  // Rotation experiments:
  // display: width, height, r=0; canvas: width, height, r=0; stripe on left does not get updated
  // display: width, height, r=0; canvas: height, width, r=0; stripe on left does not get updated
  // display: width, height, r=0; canvas: height, width, r=3; stripe on left does not get updated
  // display: height, width, r=0; canvas: width, height, r=3; stripe on left does not get updated
  // display: height, width, r=0; canvas: height, width, r=3; stripe on left does not get updated
  // display: width, height, r=3; canvas: width, height, r=3; stripe on right does not get updated
  // display: height, width, r=3; canvas: height, width, r=0; full screen works
  // display: height, width, r=3; canvas: width, height, r=0; doesn't work, hard to describe
  
  
  Serial.println("Starting GFX...");
  int speed = 12 * 1000 * 1000;
  
  // This approach doesn't work - only a corner of the display ends up being drawn.
  // display->begin() calls tftInit(), which is required.
  // bus->begin(speed, SPI_MODE0); 
  
  // This works, but not if you use a canvas.
  // display->begin(speed);

  // This allocates memory for the canvas framebuffer, and calls begin() on the display.
  canvas->begin(speed);

  display->fillScreen(RGB565_BLACK);
  Serial.println("Display initialized.");  
}

void DisplayComponent::draw(History *pHistory, int temperature)
{ 
  count = count+1;
//  uint color = ((count % 2) == 1) ? RGB565_RED : RGB565_GREEN;

  display->fillRect(0, 0, width, height, RGB565_WHITE);
  drawHistory(pHistory, temperature);
  display->flush(); 
}

void DisplayComponent::drawHistory(History *pHistory, uint16_t temperature)
{
  for (int x = 0; x < height; x++)
  {
    double fraction = (double)x / (double)height;
    int y = fraction * width;
    display->drawPixel(y, x, RGB565_BLACK);

/*    int y = pHistory->get(width - x);
    canvas->drawPixel(height, x, RGB565_BLACK);

    if (y < height - 1)
      canvas->drawPixel(height+1, x, RGB565_BLACK);
  }*/
  }
}


/*
void DisplayComponent::drawHistoryTop(History *pHistory, uint16_t color)
{
  for (int x = 0; x < width; x++)
  {
    int y = pHistory->get(width - x);
    if (y > height / 2)
    {
      canvas->drawPixel(x, height - y, color);
      canvas->drawPixel(x, (height - y) - 1, color);
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
      canvas->drawPixel(x, height / 2 - y, color);
      canvas->drawPixel(x, (height / 2 - y) - 1, color);    
    }
  }
}
*/