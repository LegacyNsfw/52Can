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

int value;
int rise;

void setup() {
  // Initialize static variables
  value = width / 2;
  rise = 1;

  // Wait for the serial port to be available.
  Serial.begin(115200);
  while(!Serial);

  // An extra pause, just to ensure that the serial port is ready.
  wait();
  Serial.println();
  Serial.println(F("52Can self-test starting. #################################"));
  TestHistory();

  Serial.println(F("History component initializing. ##########################"));
  historyComponent = new History(width);
  historyComponent->initialize();

  Serial.println(F("Display component initializing. ##########################"));
  displayComponent = new DisplayComponent();
  displayComponent->initialize();

  Serial.println(F("Initialization complete. ##################################"));
}

void loop() {
  if (value == height-1)
  {
    rise = 0;
  }
  else if (value == 0)
  {
    rise = 1;
  }

  if (rise == 1)
  {
    value+=1;
  }
  else 
  {
    value-=1;
  }  

  historyComponent->push(value);
  displayComponent->draw(historyComponent, 0);

  Serial.println(value);
}