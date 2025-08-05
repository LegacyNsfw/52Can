#include <Arduino_GFX_Library.h>
#include "Constants.h"
#include "Test.h"
#include "History.h"
#include "DisplayComponent.h"
#include "CanComponent.h"

History *historyComponent1 = nullptr;
History *historyComponent2 = nullptr;
DisplayComponent *displayComponent = nullptr;
CanComponent *canComponent = nullptr;


void wait() {
  delay(250);
  yield();
}

int value1;
int rise1;

int value2;
int rise2;

void setup() {
  // Initialize static variables
  value1 = 0;
  rise1 = 1;

  value2 = 64;
  rise2 = 1;

  // Wait for the serial port to be available.
  Serial.begin(115200);
  while(!Serial);

  // An extra pause, just to ensure that the serial port is ready.
  wait();
  Serial.println();
  Serial.println(F("52Can self-test starting. #################################"));
  TestHistory();

  Serial.println(F("History component initializing. ##########################"));
  historyComponent1 = new History(width);
  historyComponent1->initialize();

  historyComponent2 = new History(width);
  historyComponent2->initialize();

  Serial.println(F("Display component initializing. ##########################"));
  displayComponent = new DisplayComponent();
  displayComponent->initialize();

  Serial.println(F("CAN component initializing. ###############################"));
  canComponent = new CanComponent();
  canComponent->initialize();

  Serial.println(F("Initialization complete. ##################################"));
}

void loop() {
  // Animate value1
  if (value1 == height-1)
  {
    rise1 = 0;
  }
  else if (value1 == 0)
  {
    rise1 = 1;
  }

  if (rise1 == 1)
  {
    value1+=1;
  }
  else 
  {
    value1-=1;
  }  

  // Animate value2
  if (value2 == height-1)
  {
    rise2 = 0;
  }
  else if (value2 == 0)
  {
    rise2 = 1;
  }

  if (rise2 == 1)
  {
    value2+=1;
  }
  else
  {
    value2-=1;
  }

  canComponent->loop();
  int temperature = canComponent->temperature;
  historyComponent1->push(value1);
  historyComponent2->push(value2);
  displayComponent->draw(historyComponent1, historyComponent2, temperature);

  //Serial.print(value1);
  //Serial.print(", ");
  //Serial.println(value2);
}