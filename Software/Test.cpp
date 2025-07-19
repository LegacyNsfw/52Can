#include <Arduino.h>

char scratch[15];

void Assert(char *message, int actual, int expected)
{
  if (actual == expected)
  {
    Serial.print("PASS");
    Serial.print(F(" - "));  
    Serial.println(message); 
  }
  else
  {
    Serial.print("FAIL");
    Serial.print(F(" - "));  
    Serial.println(message); 

    Serial.print(F(" - Expected: "));  
    itoa(expected, scratch, 10);
    Serial.println(scratch);  

    Serial.print(F(" - Actual: "));  
    itoa(actual, scratch, 10);
    Serial.print(scratch);  
    Serial.println(F("\n"));  
  }
}