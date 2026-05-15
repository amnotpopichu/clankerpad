---
title: "Clankerpad"
author: "Leo Hsia"
description: "Clankerpad is a bluetooth macropad based on a XIAO nRF52840. It will contain 8 Glorious Panda switches with a EC11 rotary encoder. The keycaps will be taken from a set of GMK Samarais, with a custom PCB and a 3d printed case."
created_at: "2026-04-28"
---

# Disclaimer/Notes
I am importing most of this journal from a previous google doc that I had running for it. Times to do things may look crazy but i swear im not commiting fraud im just a bit stupid and this is my first project. If verb tense look weird, sorry, I am rewriting some entries to make it more clear (my old ones kinda sucked).



# May 1: Did a quick demo
Today I worked on my demo, where I concluded that connecting a GPIO pin to the switch to GND would work. While I was almost certain it would work, I double checked. I also used Claude for firmware, to test out the BLE functionality. 

**Total time spent: 0.25 hours**


# April 28: Looked into parts 

Spent far too much time looking through guides and past projects (along with hackpad) to figure out what I was going to do for my macropad. I wanted it to stand out with bluetooth functionality, and knew that which keycaps and switches I would use (which I already had from building a custom keyboard previously). From there, I had just learned about ESP32s, and wanted to use it (Because I had learned about their bluetooth functionality). 

During this time, the main thing I learned was I would have to use a lipo battery, and then find a way to charge the lipo battery. A concern of mine is that I will fry the ESP if I power it (while flashing code) while also using the TP4056 for battery power.

- TP4056 - to power ESP 32 (be able to recharge and discharge from battery)
- 1000–2000mAh single cell 3.7V LiPo - actual battery
- ESP 32 
- PCB
- Switches 
- Rotary knob (EC11)

**Total time spent: 0.75 hours**
