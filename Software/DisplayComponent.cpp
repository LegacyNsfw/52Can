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

int count;

void DisplayComponent::initialize()
{  
  count = 0;
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

void DisplayComponent::draw(History *pHistory, int temperature)
{ 
  count = count+1;
//  uint color = ((count % 2) == 1) ? RGB565_RED : RGB565_GREEN;

  canvas->fillRect(0, 0, width, height, RGB565_WHITE);
  drawHistory(pHistory, temperature);
  canvas->flush(); 
}

void DisplayComponent::drawHistory(History *pHistory, uint16_t temperature)
{
  for (int x = 0; x < width; x++)
  {
    //double fraction = (double)x / (double)width;
    //int y = fraction * height;
    int y = height - pHistory->get(x);
    canvas->drawPixel(x, y, RGB565_BLACK);
  }
}
