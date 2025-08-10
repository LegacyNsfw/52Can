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

#ifdef GAUGE_DUAL_AFR_MOCK_DATA || GAUGE_DUAL_AFR
  Serial.println(F("History component initializing. ##########################"));
  pLeftHistory = new History(width);
  pLeftHistory->initialize();

  pRightHistory = new History(width);
  pRightHistory->initialize();
#endif

#ifdef GAUGE_DUAL_AFR_MOCK_DATA
  Serial.println(F("Mock AFR data component initializing. ####################"));
  pMockAfrData = new MockAfrData();
  pMockAfrData->initialize();
#endif 

  Serial.println(F("Display component initializing. ##########################"));
  pDisplayComponent = new DisplayComponent();
  pDisplayComponent->initialize();

  Serial.println(F("CAN component initializing. ###############################"));
  pCanComponent = new CanComponent();
  pCanComponent->initialize();

  Serial.println(F("Initialization complete. ##################################"));
}

void loop() {

#ifdef GAUGE_DUAL_AFR_MOCK_DATA  
  pMockAfrData->loop();
#else
  canComponent->loop();
#endif

#ifdef COMBINATION_ALARM  
  pCanComponent->loop();
  int temperature = pCanComponent->temperature;
  int pressure = pCanComponent->fuelPressure;
  int knock = pCanComponent->knock;
  pDisplayComponent->draw(temperature, pressure, knock);
#endif

#ifdef GAUGE_DUAL_AFR_MOCK_DATA
  pLeftHistory->push(pMockAfrData->value1);
  pRightHistory->push(pMockAfrData->value2);
  pDisplayComponent->draw(pLeftHistory, pRightHistory);
#endif

#ifdef GAUGE_DUAL_AFR
  pCanComponent->loop();
  pLeftHistory->push(pCanComponent->lambda1);
  pRightHistory->push(pCanComponent->lambda2);
  pDisplayComponent->draw(pLeftHistory, pRightHistory);
#endif
}