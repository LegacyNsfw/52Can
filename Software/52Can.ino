#include <SPI.h>
//#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735

#include "History.h"
#include "DisplayComponent.h"
#include "CanComponent.h"

DisplayComponent displayComponent;
CanComponent canComponent;

int value = height / 2;
int rise = 1;
const int drawMax = height / 2;

History history = History(width);

void setup() 
{
  // Wait for the serial port to be available, then announce startup.
  Serial.begin(9600);
  while(!Serial);
  Serial.println();
  Serial.println();
  delay(250);
  Serial.println(F("CAN Display starting."));

  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);  

#ifdef SEEED_XIAO_M0
  // Fast display, broken CAN:
  //SPI.beginTransaction(SPISettings(12 * 1000 * 1000, MSBFIRST, SPI_MODE0));

  // still broken CAN with 3 or 6
  //SPI.beginTransaction(SPISettings(3 * 1000 * 1000, MSBFIRST, SPI_MODE0));
  // broken with 2,4,8
  //SPI.setClockDivider(2);

  // Display + CAN worked with this, but only without the SPI patch, which probably means it was only doing SPI at 6mhz.
  SPI.begin();
  SPI.beginTransaction(SPISettings(12 * 1000 * 1000, MSBFIRST, SPI_MODE0));

#endif


  // ESP32C3: Display does not initialize with this. But without this, frame rate is about 1hz.
  SPI.begin();
  SPI.beginTransaction(SPISettings(12 * 1000 * 1000, MSBFIRST, SPI_MODE0));

  // Run unit tests.
  //TestHistory();

  // Experimental SPI speed stuff.
  //SPI.begin(SCK, MISO, MOSI, SS);  
  
  // with SAMD21:
  // 12 = can init worked, display broken
  
  // with ESP32:
  // 12 = no can, no display
  // 10 = no can, no display
  // 6 = no can, no display
  //SPI.begin(); // SCK, MISO, MOSI, SS);  
  //SPI.beginTransaction(SPISettings(12 * 1000 * 1000, MSBFIRST, SPI_MODE0));

  // still broken CAN with 3 or 6
  //SPI.beginTransaction(SPISettings(3 * 1000 * 1000, MSBFIRST, SPI_MODE0));
  // broken with 2,4,8

  // esp32
  // 2 = serial works, can works, display doesn't 
  // 3 = same
  // 4 = same
  // 8 = same
  // 16 = same
  // 32 = same
  //SPI.setClockDivider(32);

  //canComponent.initialize();

  displayComponent.initialize();

  // Fill the history buffer with fake data.
  for (int i = 0; i < width; i++)
  {
    history.push(height / 2);
  }

  Serial.print("Setup complete.");
}
    
void loop() {  
  Serial.print("-");
  
  /*
  if (value == height)
  {
    rise = 0;
  }
  else if (value == 0)
  {
    rise = 1;
  }

  if (rise == 1)
  {
    value+=2;
  }
  else 
  {
    value-=2;
  }
*/
  history.push(value);
  history.push(value);

  Serial.print(".");

  displayComponent.draw(&history, 0); // canComponent.temperature);
  //canComponent.loop();
  Serial.print("|");
}


