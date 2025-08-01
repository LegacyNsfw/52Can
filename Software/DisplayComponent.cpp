#include <Arduino_GFX_Library.h>
#include "Constants.h"
#include "History.h"
#include "DisplayComponent.h"

Arduino_DataBus *bus = nullptr;
Arduino_GFX *display = nullptr;    
Arduino_GFX *canvas = nullptr;


int count;

void DisplayComponent::initialize()
{  
  count = 0;
  Serial.println("Creating bus...");
  bus =  new Arduino_ESP32SPI(DC, CS, SCLK, MOSI, BL);
  //  1, // DC
  //  0 // CS 
  //);
  
  Serial.println("Creating display...");
  display = new Arduino_ST7735(
    bus,
    2, //  RST
    0, // rotation
    true, // ips
    width, // width
    height // height
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

  // This allocates memory for the canvas framebuffer, and calls begin() on the display.
  canvas->begin(speed);

  display->fillScreen(RGB565_BLUE);
  Serial.println("Display initialized.");  
}

void DisplayComponent::draw(History *pHistory, int temperature)
{
  Serial.println(count);
  
  count = count+1;
  uint color = ((count % 2) == 1) ? RGB565_BLACK : RGB565_WHITE;

  canvas->fillRect(0, 0, width, height, color);
  canvas->flush();
  display->flush(); 

  //char szTemperature[5];
  //itoa(temperature, szTemperature, 10);

//  canvas.setFont(&FreeMonoBold24pt7b);
//  canvas.setCursor(30, 48);
//  canvas.setTextColor(LIGHTGREY);
//  canvas.print(szTemperature);

  //drawHistoryTop(pHistory, LIGHTBLUE);
  //canvas->flush();

  //canvas->fillScreen(backgroundColor);
  //drawHistoryBottom(pHistory, YELLOW);
  //canvas->flush();
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