#include <Arduino.h>
#include <mcp_can.h> // https://github.com/limengdu/Arduino_CAN_BUS_MCP2515
#include "Constants.h"
#include "CanComponent.h"

// Xiao can expansion board uses D7 for chip select
#define SPI_CS_PIN  D7
MCP_CAN* CAN = nullptr;

uint32_t AEM_FLUID_TEMPERATURE_CAN_ID = 0x000A0302;
uint32_t AEM_FLUID_PRESSURE_CAN_ID = 0x000A0301;
uint32_t AEM_WIDEBAND_1_CAN_ID = 0x00000180;
uint32_t AEM_WIDEBAND_2_CAN_ID = 0x00000181;

void CanComponent::initialize()
{
  // Initialize CAN object
  CAN = new MCP_CAN(SPI_CS_PIN);
  
  while (CAN_OK != CAN->begin(CAN_500KBPS))    // init can bus : baudrate = 500k
  {
    Serial.println("CAN initialization failed, will retry.");
  }

  CAN->init_Filt(0, 1, AEM_FLUID_TEMPERATURE_CAN_ID);
  CAN->init_Mask(0, 1, AEM_FLUID_TEMPERATURE_CAN_ID);

  Serial.println("CAN initialization succeeded.");
}

void CanComponent::loop()
{
  byte canState = CAN->checkReceive();
  if (CAN_MSGAVAIL == canState)            // check if data coming
  {
      unsigned long canId = 0;
      unsigned char len = 0;
      unsigned char buf[8];
        
      CAN->readMsgBufID(&canId, &len, buf);    // read data,  len: data length, buf: data buf
      
      if (canId == AEM_FLUID_TEMPERATURE_CAN_ID)
      {
        temperature = (((int)buf[1] * 9) / 5) + 32;
      }

      // .0001 Lambda/bit, or 0 to 6.5535 Lambda
      if (canId == AEM_WIDEBAND_1_CAN_ID)
      {
        lambda1 = (buf[0] << 8 | buf[1]);
      }

      if (canId == AEM_WIDEBAND_2_CAN_ID)
      {
        lambda2 = (buf[0] << 8 | buf[1]);
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
