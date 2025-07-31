#include "Constants.h"
#include "History.h"
#include "DisplayComponent.h"
//#include "CanComponent.h"


void wait() {
  delay(250);
  yield();
}

int value;
int rise;
int drawMax;
long iteration;

DisplayComponent* displayComponent;
//CanComponent* canComponent;
History* history;

void setup() 
{
  // Wait for the serial port to be available, then announce startup.
  Serial.begin(115200);
  while(!Serial);
  wait();
  wait();
  Serial.println();
  Serial.println(F("CAN Display starting. #####################################"));
  
  Serial.println(F("Step 1: Initializing variables..."));

  // Initialize variables that depend on width/height
  value = height / 2;
  drawMax = height / 2;
  rise = 1;
  Serial.println(F("Variables initialized."));
  
  Serial.println(F("Step 2: Creating DisplayComponent..."));
  displayComponent = new DisplayComponent();
  Serial.println(F("DisplayComponent created."));
  
  //Serial.println(F("Step 3: Creating CanComponent..."));
  //canComponent = new CanComponent();
  //Serial.println(F("CanComponent created."));
  
  Serial.println(F("Step 4: Creating History..."));
  Serial.print(F("Free heap before History creation: "));
  Serial.println(ESP.getFreeHeap());
  
  history = new History(width);
  Serial.println(F("History created."));
  
  Serial.print(F("Free heap after History creation: "));
  Serial.println(ESP.getFreeHeap());

  /*
  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);
  */  

  //canComponent->initialize();

  Serial.println(F("Step 5: Initializing DisplayComponent..."));
  displayComponent->initialize();
  Serial.println(F("DisplayComponent initialized."));

  Serial.println("Empty history:");
  history->debug();
  Serial.println("Initializing history.");
  Serial.print(F("About to fill buffer with "));
  Serial.print(width);
  Serial.println(F(" values..."));
  
  // Fill the history buffer with fake data.
  for (int i = 0; i < width; i++)
  {
    if (i % 32 == 0) {  // Print progress every 32 iterations
      Serial.print(F("Filling index "));
      Serial.print(i);
      Serial.print(F(", free heap: "));
      Serial.println(ESP.getFreeHeap());
    }
    history->push(height / 2);
  }

  Serial.println(F("Initialized history:"));
  history->debug();
  
  Serial.println(F("Setup complete. #############################################"));
}

void loop() {
  Serial.print(F("Start "));
  Serial.print(iteration++);
  Serial.println();

  Serial.println(F("Update state."));
  wait();
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
    value+=1;
  }
  else 
  {
    value-=1;
  }

  Serial.println(F("B"));
  wait();

  history->push(value); // This causes the CPU to crash.
  history->debug();

  Serial.println(F("C"));
  wait();
  
  displayComponent->draw(history, 0); // canComponent.temperature);
  //canComponent->loop();
  Serial.println(F("Z"));
  
  wait();
}


