# Macro Mixer
A DIY Streamdeck alternative for a custom configurable macro board with dials, compatible with commercially available switches (Cherry MX Hotswappable). Reverse mounted under key lighting is also added for both debugging and aesthetics whilst allowing the top side of the board to remain clean and flush.

![Project_Image](.assets/Macro%20Mixer.JPG)

## Features
* 15x Individually addressable n key rollover switches 
* 6x 12 bit resolution dials
* Addressable underglow lighting for every key and dial
* Easy Key assignment via the software

## [Hardware](/Hardware/README.md)
The case is 3D printed in white PLA plastic however other colour work too. The STLs and Steps are provided in the hardware folder.

![Hardware](.assets/Macro%20Mixer%20Case%20A.JPG)

## [Software](/Software/README.md)
Using PlatformIO and buildin ESP32 libraries, I have made an easy way to configure what keys are assigned to what key-combo.

![Software](.assets/Macro%20Mixer%20Software.png)

## [Embedded](/Embedded/README.md)
Although the currently fabricated PCB has some mistakes, I have modified the KiCAD files to account for this. The embedded circuit is a relatively dense board requiring a steady hand and hotplate.

![Embedded](.assets/Macro%20Mixer%20KiCAD%20Top.png)

## Roadmap
* Milestones: Completed Version 1.0
* Work In Progress: Easier software configuration
* Work In Progress: Potentiometers configuration
* Planned: Removing the boot button and using the switch as the the boot switch