#include <Arduino.h>
#include <mcp_can.h> // https://github.com/limengdu/Arduino_CAN_BUS_MCP2515
#include "CanComponent.h"

// Xiao can expansion board uses D7 for chip select
#define SPI_CS_PIN  D7
MCP_CAN CAN(SPI_CS_PIN);

void CanComponent::initialize()
{
  while (CAN_OK != CAN.begin(CAN_500KBPS))    // init can bus : baudrate = 500k
  {
    Serial.println("CAN initialization failed, will retry.");
  }

  Serial.println("CAN initialization succeeded.");
}

void CanComponent::loop()
{
  byte canState = CAN.checkReceive();
  if (CAN_MSGAVAIL == canState)            // check if data coming
  {
      unsigned long canId = 0;
      unsigned char len = 0;
      unsigned char buf[8];
        
      CAN.readMsgBufID(&canId, &len, buf);    // read data,  len: data length, buf: data buf
      
      if (canId == 0xA0302)
      {
        temperature = (((int)buf[1] * 9) / 5) + 32;
      }

      /**
      Serial.println("-----------------------------");
      Serial.print("Get data from ID: ");
      Serial.println(canId, HEX);
      
      for(int i = 0; i<len; i++)    // print the data
      {
          Serial.print(buf[i], HEX);
          Serial.print("\t");
      }
      Serial.println();
      */
  }
  else
  {
    //Serial.print(canState, HEX); // 4
    //Serial.println(".");
  }
}
