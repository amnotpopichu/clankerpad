---
title: "Clankerpad"
author: "Leo Hsia"
description: "Clankerpad is a bluetooth macropad based on a XIAO nRF52840. It will contain 8 Glorious Panda switches with a EC11 rotary encoder. The keycaps will be taken from a set of GMK Samarais, with a custom PCB and a 3d printed case."
created_at: "2026-04-28"
---


# May 5: Rotary encoders arrived!
Today I tested out rotary encoders, for volume (once again claude firmware), and button control! While I don't have a photo of it exactly, I have added a photo of the exact model I used (EC11)


![ec11](journal_imgs/EC11.png)
**Total time spent: 0.25 hours**

# May 1: Did a quick demo
Today I worked on my demo, where I concluded that connecting a GPIO pin to the switch to GND would work. While I was almost certain it would work, I double checked. I also used Claude for firmware, to test out the BLE functionality. 

The image below is not 100% accurate, but was the best I had im sorry :(

![demo](journal_imgs/demo1.png)
**Total time spent: 0.25 hours**


# April 28: Looked into parts 

Spent far too much time looking through guides and past projects (along with hackpad) to figure out what I was going to do for my macropad. I wanted it to stand out with bluetooth functionality, and knew that which keycaps and switches I would use (which I already had from building a custom keyboard previously). From there, I had just learned about ESP32s, and wanted to use it (Because I had learned about their bluetooth functionality). 

During this time, the main thing I learned was I would have to use a lipo battery, and then find a way to charge the lipo battery. A concern of mine is that I will fry the ESP if I power it (while flashing code) while also using the TP4056 for battery power.

- TP4056 - to power ESP 32 (be able to recharge and discharge from battery)
- 1000–2000mAh single cell 3.7V LiPo - actual battery
- ESP 32 
- PCB
- Switches 
- Keycaps
- Rotary knob (EC11)

![Keycap + Switch](journal_imgs/key.png)

**Total time spent: 0.75 hours**
