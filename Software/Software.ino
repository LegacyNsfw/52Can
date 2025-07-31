#include <Arduino_GFX_Library.h>

#define BL   5
#define SCLK 8
#define MOSI 10
#define CS   2
#define DC   3
#define RST  4

Arduino_DataBus *bus = nullptr;
Arduino_GFX *display = nullptr;    
Arduino_GFX *canvas = nullptr;
int count;

void wait() {
  delay(250);
  yield();
}


void setup() {
  // Wait for the serial port to be available, then announce startup.
  Serial.begin(115200);
  count = 0;
  while(!Serial);
  wait();
  wait();
  Serial.println();
  Serial.println(F("52Can starting. ###########################################"));

  Serial.println("Creating bus...");

  bus =  new Arduino_ESP32SPI(DC, CS, SCLK, MOSI, BL);
  //  1, // DC
  //  0 // CS 
  //);
  Serial.println("Bus created.");
  
  Serial.println("Creating display...");
  display = new Arduino_ST7735(
    bus,
    2, //  RST
    3, // rotation
    true, // ips
    128, // width
    160 // height    
  );
  Serial.println("Display created.");
  
  //Serial.println("Creating canvas...");
  //canvas = new Arduino_Canvas(width, height, display);
  //Serial.println("Canvas created.");

  int speed = 12 * 1000 * 1000;
  // Serial.println("Beginning bus...");
  // bus->begin(speed, SPI_MODE0);
  // Serial.println("Bus started.");

  Serial.println("Filling screen...");
  display->begin(speed);
  display->fillScreen(YELLOW);
  Serial.println("Display initialized.");  

  wait();

  count = 0;
  Serial.println(F("Initialization complete. ##################################"));
  Serial.println(count);

}

void loop() {
  Serial.println(count);
  Serial.println(F("Looping. #####################################"));
  count = count+1;
  uint color = ((count % 2) == 1) ? BLACK : YELLOW;
  Serial.println(color);
  display->fillScreen(color);
  display->flush();
}