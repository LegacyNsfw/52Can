#include <Arduino_GFX_Library.h>

#define BL   5
#define SCLK 8
#define MOSI 10
#define CS   2
#define DC   3
#define RST  4

#define width 128
#define height 160

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
    0, // rotation
    true, // ips
    width, // width
    height // height
  );
  Serial.println("Display created.");
  
  //Serial.println("Creating canvas...");
  canvas = new Arduino_Canvas(width, height, display, 0, 0, 0);
  //Serial.println("Canvas created.");

  
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

  wait();

  count = 0;
  Serial.println(F("Initialization complete. ##################################"));
  Serial.println(count);

}

// With the ST7735:
// RGB565_RED is actually yellow

void loop() {
  Serial.println(count);
  Serial.println(F("Looping. #####################################"));
  count = count+1;
  uint color = ((count % 2) == 1) ? RGB565_BLACK : RGB565_WHITE;
  Serial.println(color);

  canvas->fillRect(0, 0, width, height, color);
  canvas->flush();
  display->flush(); 

  wait();
}