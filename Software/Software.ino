#include <Arduino_GFX_Library.h>
#include "Constants.h"
#include "Test.h"
#include "History.h"
#include "DisplayComponent.h"
#include "CanComponent.h"
#include "MockAfrData.h"

History *pLeftHistory = nullptr;
History *pRightHistory = nullptr;
DisplayComponent *pDisplayComponent = nullptr;
CanComponent *pCanComponent = nullptr;
MockAfrData *pMockAfrData = nullptr;

int lastKnock = 0;
int loopCount = 0;

void wait() {
  delay(250);
  yield();
}

void setup() {  
  // Wait for the serial port to be available.
  Serial.begin(115200);
  while(!Serial);

  // An extra pause, just to ensure that the serial port is ready.
  wait();
  Serial.println();
  Serial.println(F("52Can self-test starting. #################################"));
  TestHistory();

  Serial.println(F("History component initializing. ##########################"));
  pLeftHistory = new History(width);
  pLeftHistory->initialize();

  pRightHistory = new History(width);
  pRightHistory->initialize();

  Serial.println(F("Display component initializing. ##########################"));
  pDisplayComponent = new DisplayComponent();
  pDisplayComponent->initialize();

  Serial.println(F("CAN component initializing. ###############################"));
  pCanComponent = new CanComponent();

#ifdef MOCK_DATA
  Serial.println(F("Mock AFR data component initializing. ####################"));
  pMockAfrData = new MockAfrData();
  pMockAfrData->initialize();
#else  
  pCanComponent->initialize();
#endif 

  Serial.println(F("Initialization complete. ##################################"));
}

int knockDisplayCount = 0;
int temperatureDisplayCount = 0;
int pressureDisplayCount = 0;

int ConsiderAlarm(int predicate, int mockRandomizer, int &displayCount, int value, const char* label, int textColor, int backgroundColor) {
#ifdef MOCK_DATA
  predicate = predicate || (loopCount % mockRandomizer == 1);
#endif
  if (predicate || (displayCount > 0)) {
    pDisplayComponent->drawAlarm(value, (char*)label, textColor, backgroundColor);
    if (predicate) {
      displayCount = 10; // Show for 10 loops
    } else {
      displayCount--;
    }
    return 1; // Alarm shown
  }
  return 0; // No alarm shown
}

void loop() {
  loopCount++;
  
#ifdef MOCK_DATA  
  pMockAfrData->loop();
  pLeftHistory->push(pMockAfrData->value1);
  pRightHistory->push(pMockAfrData->value2);  
#else
  canComponent->loop();
  pLeftHistory->push(pCanComponent->lambda1);
  pRightHistory->push(pCanComponent->lambda2);
#endif

#ifdef GAUGE_COMBINATION_ALARM  
  int temperature = pCanComponent->temperature;
  int pressure = pCanComponent->pressure;
  int knock = pCanComponent->knock;

  int knockIncreased = (knock > lastKnock);
  lastKnock = knock;
  if (ConsiderAlarm(knockIncreased, 100, knockDisplayCount, knock, "Knock", WTF_BLACK, WTF_WHITE))
  {
    return;
  }

  int temperatureAlarm = (temperature > 270);
  if (ConsiderAlarm(temperatureAlarm, 37, temperatureDisplayCount, temperature, "Oil Temp.", WTF_WHITE, WTF_RED))
  {
    return;
  }

  int pressureAlarm = 0; // (pressure < 56);
  if (ConsiderAlarm(pressureAlarm, 182, pressureDisplayCount, pressure, "Fuel Press.", WTF_WHITE, WTF_BLUE))
  {
    return;
  }

  pDisplayComponent->draw(pLeftHistory, pRightHistory);
#endif

#ifdef GAUGE_DUAL_AFR
  pCanComponent->loop();
  pLeftHistory->push(pCanComponent->lambda1);
  pRightHistory->push(pCanComponent->lambda2);
  pDisplayComponent->draw(pLeftHistory, pRightHistory);
#endif
}