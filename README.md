![image](images/microchip.jpg) 

## dspic33c curiosity nano oob demo

![image] (dspic33c-curiosity-nano-oob-demo\images\220920-MC16-PHOTO-EV88G73A-Front-Transparent.png)

## Summary
Initial message is displayed to serial terminal on power up when board is connected to PC via USB port, "dsPIC33CK64MC105 Curiosity Nano Demo. Please press on-board button to initiate demo."
After initial button press, LED on board will flash and "Button pressed! Enjoy the blink." will be printed to the screen when button is held. When button is not pressed, "Button not pressed... please press to observe blink." will be printed to serial terminal screen.

## Related Documentation
https://www.microchip.com/en-us/product/dsPIC33CK64MC105

## Software Used 
- A terminal program

## Hardware Used
- dsPIC33CK64MC105 Curiosity Nano Development Board
- Micro-USB cable

## Setup
For programming/debugging and to run the demo, connect a USB cable to the USB connector and connect other end to a PC. 


## Operation
On power-up, the below message will print to the terminal. Press button once to initiate demo. 
![image] (dspic33c-curiosity-nano-oob-demo\images\welcome-33CK-c-nano.png)

While button is pressed, demo begins and below message will print:
![image] (dspic33c-curiosity-nano-oob-demo\images\button-press-33CK-c-nano.png)

And when button is not pressed, below message will print to the terminal:
![image] (dspic33c-curiosity-nano-oob-demo\images\no-press-33CK-c-nano.png)


