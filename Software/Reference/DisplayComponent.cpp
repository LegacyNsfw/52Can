#include <Arduino_GFX_Library.h>
#include "Constants.h"
#include "History.h"
#include "DisplayComponent.h"

int16_t backgroundColor;// = BLACK;

Arduino_DataBus *bus = nullptr;
Arduino_GFX *display = nullptr;    
Arduino_GFX *canvas = nullptr;
int speed = 12 * 1000 * 1000;

void DisplayComponent::initialize()
{  
  backgroundColor = BLACK;
  Serial.println("Display: Creating bus...");

  bus = new Arduino_HWSPI(
    1, // DC
    0 // CS 
  );
  Serial.println("Display: Bus created.");
  
  Serial.println("Display: Creating display...");
  display = new Arduino_ST7735(
    bus,
    2 //  RST
  );
  Serial.println("Display: Display created.");
  
  Serial.println("Display: Creating canvas...");
  canvas = new Arduino_Canvas(width, height, display);
  Serial.println("Display: Canvas created.");

  Serial.println("Display: Beginning bus...");
  bus->begin(speed, SPI_MODE0);
  Serial.println("Bus started.");

  Serial.println("Display: Filling screen...");
  display->fillScreen(YELLOW);
  Serial.println("Display blanked.");  

  delay(250);
  yield();
  Serial.println("Display initialization complete.");
}

void DisplayComponent::draw(History *pHistory, int temperature)
{
  //char szTemperature[5];
  //itoa(temperature, szTemperature, 10);

  // Draw the top half and then the bottom half.
  // Because there isn't enough RAM to buffer the entire screen.
  canvas->fillScreen(backgroundColor);

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
