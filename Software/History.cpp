//#include <stdlib.h>
#include <Arduino.h>
#include "Test.h"
#include "Constants.h"
#include "History.h"
//#include "Test.h"
#include "DisplayComponent.h" // must be included because it has the define for 'width'

void History::debug()
{
  Serial.print(F("History length: "));
  Serial.print(this->size);
  Serial.println();

  Serial.print(F("History index: "));
  Serial.print(this->currentIndex);
  Serial.println();
}

void TestHistory()
{
  History h2 = History(5);
  h2.push(1);
  h2.push(2);
  h2.push(3);
  h2.push(4);
  h2.push(5);
  h2.push(6);

  Assert("b0", h2.get(0), 6);
  Assert("b1", h2.get(1), 5);
  Assert("b3", h2.get(2), 4);
  Assert("b4", h2.get(3), 3);
  Assert("b5", h2.get(4), 2);
}