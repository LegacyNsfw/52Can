# 52mm CANbus Gauge Pod

<img src="/Assets/ToucanRacer.png" alt="Toucan driving a race car" height="200" width="200"/>

# Current Situation

I've built a gauge, and it seems to work on my desk... it's in my car now. But my car's cylinder heads are at a shop across town.

# Project Goals

* Display data from CAN bus.
* Fit into standard 52mm gauge pods.
* Made from inexpensive and readily available components.
* Easy to assemble - only requires basic soldering and 3D printing.
* Easy to configure...
 * For now, you'll need to be able to edit code.
 * Eventually, this should be possible with a mobile phone app.

# Designed for the following hardware:

* Processor: Seeed Studio's [Xiao ESP32C3](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html) ([docs](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/))  (I started with the Xiao SAMD21, but its SPI is not fast enough)
* CanBus: Seeed Studio's [Xiao CanBus expansion board](https://www.seeedstudio.com/Seeed-Studio-CAN-Bus-Breakout-Board-for-XIAO-and-QT-Py-p-5702.html) ([docs](https://wiki.seeedstudio.com/xiao-can-bus-expansion/))
* Display: Adafruit's [1.8" TFT LCD + MicroSD board](https://www.adafruit.com/product/358) ([docs](https://learn.adafruit.com/1-8-tft-display))
* Voltage regulator: [Drok Adjustable Buck Regulator](https://www.amazon.com/dp/B096RC71DC?th=1) (5 for $10)
* PCB: There are a handful of custom PCB shops, I've had good luck with [Seeed Studio Fusion](https://www.seeedstudio.com/fusion_pcb.html) (10 boards shipped to the US for $20ish in 3 weeks)
* 4-pin JST JWPF connectors [https://www.amazon.com/dp/B07VTNJLY4](Knockoffs Available Here)

# Aspirations

* Better display, perhaps using OLED. The current 1.8 TFT display works, but it isn't great.
* Perhaps a touchscreen display?
* Proper circuit board. The current board is basically just a circular solderable breadboard. It would be nice to be able to order pre-populated boards that only need power, CAN, and display wiring.
* More elegant 3D model. I did this in an afternoon. It works, but it ain't pretty.
* Android app to configure display modes, alarm thresholds, etc, with configuration [https://wiki.seeedstudio.com/xiaoesp32c3-flash-storage/](stored in flash).


