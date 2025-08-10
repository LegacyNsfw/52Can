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
uint32_t PLEX_KNOCK_COUNT_CAN_ID = 0x00000000; // Placeholder, replace with actual ID

void CanComponent::initialize()
{
#ifndef GAUGE_DUAL_AFR_MOCK_DATA
  // Initialize CAN object
  CAN = new MCP_CAN(SPI_CS_PIN);
  
  while (CAN_OK != CAN->begin(CAN_500KBPS))    // init can bus : baudrate = 500k
  {
    Serial.println("CAN initialization failed, will retry.");
  }
#endif
#ifdef GAUGE_COMBINATION_ALARM
  CAN->init_Filt(0, 1, AEM_FLUID_TEMPERATURE_CAN_ID);
  CAN->init_Mask(0, 1, AEM_FLUID_TEMPERATURE_CAN_ID);

  CAN->init_Filt(0, 1, AEM_FLUID_PRESSURE_CAN_ID);
  CAN->init_Mask(0, 1, AEM_FLUID_PRESSURE`_CAN_ID);

  CAN->init_Filt(0, 1, PLEX_KNOCK_COUNT_CAN_ID);
  CAN->init_Mask(0, 1, PLEX_KNOCK_COUNT_CAN_ID);
#endif

#ifdef GAUGE_DUAL_AFR
  CAN->init_Filt(0, 1, AEM_WIDEBAND_1_CAN_ID);
  CAN->init_Mask(0, 1, AEM_WIDEBAND_1_CAN_ID);

  CAN->init_Filt(0, 1, AEM_WIDEBAND_2_CAN_ID);
  CAN->init_Mask(0, 1, AEM_WIDEBAND_2_CAN_ID);
#endif

  Serial.println("CAN initialization succeeded.");
}

void CanComponent::loop()
{
  // Read up to 4 messages
  for (int i = 0; i < 4; i++) {

    // If no messages are available, break out of the loop
    byte canState = CAN->checkReceive();
    if (CAN_MSGAVAIL != canState) {
      break;
    }

    // Process whatever message is available
    unsigned long canId = 0;
    unsigned char len = 0;
    unsigned char buf[8];
      
    CAN->readMsgBufID(&canId, &len, buf);    // read data,  len: data length, buf: data buf
    
    if (canId == AEM_FLUID_TEMPERATURE_CAN_ID)
    {
      temperature = (((int)buf[1] * 9) / 5) + 32;
    }

    // 0.01 bar/bit = 0 to 655.35 bar
    if (canId == AEM_FLUID_PRESSURE_CAN_ID)
    {
      pressure = (buf[0] << 8 | buf[1]);
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
  }
}
