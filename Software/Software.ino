#include <Arduino_GFX_Library.h>
#include "Test.h"
#include "History.h"
#include "DisplayComponent.h"
#include "Constants.h"

History *historyComponent = nullptr;
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

  Serial.println(F("52Can self-test starting. #################################"));
  TestHistory();

  Serial.println(F("History component initializing. ##########################"));
  historyComponent = new History(height);
  historyComponent->initialize();

  Serial.println(F("Display component initializing. ##########################"));
  displayComponent = new DisplayComponent();
  displayComponent->initialize();

  Serial.println(F("Initialization complete. ##################################"));
}

void loop() {
  
  displayComponent->draw(nullptr, 0);

  wait();
}