#include <Arduino_GFX_Library.h>
#include "Test.h"
#include "History.h"
#include "DisplayComponent.h"
#include "Constants.h"

DisplayComponent *displayComponent = nullptr;

void wait() {
  delay(250);
  yield();
}


void setup() {
  // Wait for the serial port to be available, then announce startup.
  Serial.begin(115200);
  
  while(!Serial);
  wait();
  wait();
  Serial.println();
  TestHistory();
  Serial.println(F("52Can starting. ###########################################"));

  displayComponent = new DisplayComponent();
  displayComponent->initialize();

  wait();


  Serial.println(F("Initialization complete. ##################################"));
}

void loop() {
  
  displayComponent->draw(nullptr, 0);

  wait();
}