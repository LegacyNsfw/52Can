# 52Can: CANbus display in a 52mm gauge pod

## Status

This is far from being usable right now. It has just reached the point where I want version control and a remote backup, and that's where github comes in.

## Ingredients

Designed for the following hardware:

* Processor: SeeedStudio's [Xiao SAMD21](https://www.seeedstudio.com/Seeeduino-XIAO-Arduino-Microcontroller-SAMD21-Cortex-M0+-p-4426.html) ([docs](https://wiki.seeedstudio.com/Seeeduino-XIAO/)) or maybe [Xiao ESP32C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html?srsltid=AfmBOop_YKQCcigSS8mZArUKnlremVAYbcV85Hv6Z_S4PDStP-GIQizw) ([docs](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/))
* CanBus: SeeedStudio's [Xiao CanBus expansion board](https://www.seeedstudio.com/Seeed-Studio-CAN-Bus-Breakout-Board-for-XIAO-and-QT-Py-p-5702.html) ([docs](https://wiki.seeedstudio.com/xiao-can-bus-expansion/))
* Display: Adafruit's [1.8" TFT LCD + MicroSD board](https://www.adafruit.com/product/358) ([docs](https://learn.adafruit.com/1-8-tft-display))
* 3D printed parts: See the Hardware/GaugePod directory
* Simple PCB: See the Hardware/CircuitBoard directory
* And the Arduino project in the Software directory.
  
As I write this I've got the parts plugged into a breadboard and I'm waiting for PCBs from Aisler that will hopefully make it pretty simple to assemble everything.

The software basically worked on the SAMD21 Xiao, but the frame rate is just barely tolerable, so I'm trying to get it to work on the ESP32C3 Xiao now.
