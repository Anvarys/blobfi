> [!WARNING]
> This project is currently in developement, so some of the design is out of date

<div align="center">
  <img src="https://github.com/Anvarys/blobfi/blob/master/images/front.png?raw=true" alt="Blobfi" width="300">
</div>

<h2 align="center">Blobfi</h2>
<p align="center">
A custom PCB-based Tamagotchi virtual pet called Blobfi
</p>

## About the project

A custom PCB-based Tamagotchi-like virtual pet built the XIAO-ESP32-C6 MCU, featuring a 0.96" OLED display, 500mah battery with USB-C charging (via the esp32), 3 buttons and a buzzer.

I made this project to have my own custom tamagotchi pet called Blobfi, which is a blobfish, because I love blobfishes!!

I used [Tanishq's tamagotchi](https://github.com/TaniWanKenobi/tamagotchi/) as insiration & reference.

To use this project first you need to print the top and bottom parts ([link to the folder with 3d models](https://github.com/Anvarys/blobfi/tree/master/CAD)), then you need to buy all the [parts](https://github.com/Anvarys/blobfi/blob/master/BOM.csv) and the [PCB](https://github.com/Anvarys/blobfi/blob/master/blobfi_gerber.zip) and then assemple it all together as shown on the picture below (also you need to screw the PCB and the top to the bottom enclosure in using 3 M3x8mm screws each):
![](https://github.com/Anvarys/blobfi/blob/master/images/assembly.png?raw=true)

And then you need to flash the ESP32 using my [firmware](https://github.com/Anvarys/blobfi/tree/master/firmware) via [PlatformIO](https://platformio.org/)

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
- Hunger (can be increased by 10 if you feed Blobfi by pressing the left button)
- Happiness (can be increased by 10 if you play with Blobfi by pressing the middle button)
- Energy (can be increased by 10 if you put Blobfi to sleep by pressing the right button)

Depending on these stats you will have a different image of a blobfish on your main screen, here is an example of a happy Blobfi:

![main_screen](https://github.com/Anvarys/blobfi/blob/master/images/main_screen.png?raw=true)

And here is an example of an action animation (duration - 5s):

![playing animation](https://github.com/Anvarys/blobfi/blob/master/images/playing.gif?raw=true)

## BOM

|Name                    |Qty|Price (USD)|Link                                                             |Note                               |
|------------------------|---|-----------|-----------------------------------------------------------------|-----------------------------------|
|Lithium battery 500mah  |1  |US$4.75    |https://fr.aliexpress.com/item/1005010430419655.html             |                                   |
|M3 screws (20pcs) 8mm   |1  |US$2.78    |https://fr.aliexpress.com/item/1005010018023551.html             |                                   |
|Aliexpress shipping     |1  |US$3.65    |-                                                                |                                   |
|0.96'' OLED display     |1  |US$2.16    |https://www.lcsc.com/product-detail/C5248080.html                |                                   |
|Tactile button          |3  |US$0.51    |https://www.lcsc.com/product-detail/C2888493.html                |                                   |
|Buzzer                  |1  |US$0.31    |https://www.lcsc.com/product-detail/C49246964.html               |                                   |
|Male pin headers (20pcs)|1  |US$0.62    |https://www.lcsc.com/product-detail/C49261205.html               |                                   |
|LCSC shipping & handling|1  |US$9.06    |-                                                                |                                   |
|JLCPCB PCB              |1  |US$0.00    |https://jlcpcb.com                                               |free because of the new user coupon|
|JLCPCB shipping         |1  |US$1.50    |-                                                                |                                   |
|XIAO-ESP32-C6           |1  |US$5.20    |https://www.seeedstudio.com/Seeed-Studio-XIAO-ESP32C6-p-5884.html|                                   |
|Seeed Studio shipping   |1  |US$5.44    |-                                                                |                                   |
|Total                   |   |US$35.98   |                                                                 |                                   |

_P.S. I did not include the price of printing since I already have a 3d printer & filament _

## My zine for this project

![Zine](https://github.com/Anvarys/blobfi/blob/master/images/zine.png?raw=true)

#### For fallout reviewers

Currently I'm working on the project so if you are reviewing it right now then please return it or postpone the review until early May