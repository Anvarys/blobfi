<div align="center">
  <img src="https://github.com/Anvarys/blobfi/blob/master/images/top-view.png?raw=true" alt="Blobfi" width="300">
</div>

<h2 align="center">Blobfi</h2>
<p align="center">
A custom PCB-based Tamagotchi virtual pet called Blobfi
</p>

## About the project

A custom PCB-based Tamagotchi-like virtual pet built the XIAO-ESP32-C6 MCU, featuring a 0.96" OLED display, 500mah battery with USB-C charging (via the esp32), 3 buttons, a temperature sensor and a vibration motor.

I made this project to have my own custom tamagotchi pet called Blobfi, which is a blobfish, because I love blobfishes!!

I used [Tanishq's tamagotchi](https://github.com/TaniWanKenobi/tamagotchi/) as insiration & reference.

To use this project first you need to 3d print the top and bottom parts ([link to the folder with 3d models](https://github.com/Anvarys/blobfi/tree/master/CAD)), then you need to buy all the [parts](https://github.com/Anvarys/blobfi/blob/master/BOM.csv) and the [PCB](https://github.com/Anvarys/blobfi/blob/master/blobfi_gerber.zip) and then assemple it all together as shown on the picture below (also you need to screw the PCB and the top to the bottom enclosure in using 3 M3x8mm screws each):
![](https://github.com/Anvarys/blobfi/blob/master/images/assembly.png?raw=true)

And then you need to flash the ESP32 using my [blobfi_firmware](https://github.com/Anvarys/blobfi/tree/master/blobfi_firmware) sketch in Arduino IDE, also you need to install Adafruit SSD1306 library first.

## Tools I used

For PCB & schematic design I used [KiCAD](https://kicad.org), for 3D design I used [Autodesk Fusion](https://www.autodesk.com/products/fusion-360/overview) (free version), for coding the firmware I used [VS Code](https://code.visualstudio.com/) with [PlatformIO](https://platformio.org/) plugin, for testing the firmware I used [Wowki](https://wokwi.com/) hardware simulator and for general design (Edge.Cuts & the Zine) I used [Figma](https://figma.com)

## PCB design

![pcb](https://github.com/Anvarys/blobfi/blob/master/images/pcb.png?raw=true)

## Schematic

![schematic](https://github.com/Anvarys/blobfi/blob/master/images/schematic.png?raw=true)

## 3D model

![3d model](https://github.com/Anvarys/blobfi/blob/master/images/sideview.png?raw=true)

## Firmware

Blobfi has 3 stats which decrease by 1 each 5 minutes:
- Hunger
- Happiness
- Energy

And if the temperature of Blobfi goes above 40C or below 5C happiness will decrease at 2x rate.

Depending on these stats you will have a different image of a blobfish on your main screen, here is an example of a happy Blobfi:

![main_screen](https://github.com/Anvarys/blobfi/blob/master/images/main_screen.png?raw=true)

If any of the stats will go below 0 it will be set to 0 and the vibration motor will shake your Blobfi as it wants to eat/sleep/play.

Also if any stat is below 10 then the bar will blink on the screen.

Actions buttons do:
- Left button: Feed Blobfi, +15 hunger and +5 energy
- Middle button: Play with Blobfi, +15 happiness and -5 energy
- Right button: Put Blobfi to sleep, +15 energy
- Left and right buttons at the same time: Put the device into deep sleep (basically turning it off, you can wake it up by pressing any button)

And here is an example of an action animation (duration - 3s):

![playing animation](https://github.com/Anvarys/blobfi/blob/master/images/playing.gif?raw=true)

#### Deep sleep

Also my firmware uses ESP32 deep sleep feature, which allows it to go into a very low power use mode. After 30 seconds of inactivity (not pressing any buttons) the device will go into deep sleep.

When the device goes into deep sleep it will disable the display, but it will start an internal timer for the next update of Blobfi (5 minutes minus the time from the last update that had already passed) and it will still listen to any button inputs, and if you press any button it will wake up to the normal state.

This allows to reduce ESP32C6 and display's total current from about **50mA** to about **17µA** which is around **2941 times less current**. This allows for the device to actually work for longer than some 10-15 hours, now it can do multiple weeks (theoretically, has not tested that in practice yet).

## BOM

|Name                    |Qty|Price (Total)|Link                                                                        |Note                                                                                         |
|------------------------|---|-------------|----------------------------------------------------------------------------|---------------------------------------------------------------------------------------------|
|Lithium battery 500mah  |1  |US$8.48      |https://fr.aliexpress.com/item/1005009540712263.html                        |                                                                                             |
|XIAO ESP32 C6           |1  |US$6.68      |https://fr.aliexpress.com/item/1005006987272421.html                        |                                                                                             |
|Aliexpress shipping     |1  |US$5.07      |-                                                                           |XIAO ESP32 C6                                                                                |
|JLCPCB PCB              |1  |US$2.00      |https://jlcpcb.com                                                          |free because of the new user coupon                                                          |
|M3 8mm screws           |6  |US$0.06      |https://jlcmc.com/product/s/E02/EDLF/din-7984-hex-socket-thin-head-cap-screw|                                                                                             |
|JLCPCB shipping         |1  |US$8.36      |-                                                                           |                                                                                             |
|JLCPCB New user coupon  |1  |-US$10.00    |-                                                                           |                                                                                             |
|4K7 Resistor            |2  |US$0.58      |https://www.lcsc.com/product-detail/C119339.html                            |                                                                                             |
|MY18B20L temp sensor    |1  |US$1.94      |https://www.lcsc.com/product-detail/C5259249.html                           |                                                                                             |
|0.96'' OLED display     |1  |US$2.92      |https://www.lcsc.com/product-detail/C5248080.html                           |might be cheaper, rn out of stock on lcsc, so this is from "other suppliers" on their website|
|Tactile button          |3  |US$0.51      |https://www.lcsc.com/product-detail/C2888493.html                           |                                                                                             |
|Vibration motor         |1  |US$0.52      |https://www.lcsc.com/product-detail/C2759982.html                           |                                                                                             |
|Male pin headers (20pcs)|1  |US$0.62      |https://www.lcsc.com/product-detail/C49261205.html                          |for the display                                                                              |
|2N2222A transistor      |1  |US$0.91      |https://www.lcsc.com/product-detail/C5330385.html                           |                                                                                             |
|0.1uF capacitor         |1  |US$0.61      |https://www.lcsc.com/product-detail/C5632427.html                           |                                                                                             |
|LCSC shipping & handling|1  |US$12.14     |-                                                                           |                                                                                             |
|3D printed parts        |2  |US$0.00      |i will print myself                                                                |                                                                                             |
|                        |   |             |                                                                            |                                                                                             |
|Total                   |   |US$41.40     |                                                                            |                                                                                             |


## My zine for this project

![Zine](https://github.com/Anvarys/blobfi/blob/master/images/zine.png?raw=true)