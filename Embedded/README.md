# Macro Mixer - Embedded
The Wroom32 S3 module is the core of this build as there were just enough pins to hook up all n key rollover switches along with the 6 adc potentiometers. Currently there is a boot button which can be accessed through a hole at the bottom of the case and must be pressed whilst plugging in the board for it to enter boot mode. This will be changed in the future however for it to be the first key so this hole is no longer required and is less of a hastle to enter boot mode.

![Boot_Hole](/.assets/Boot%20Hole.png)

The Addressable LEDS are reverse mounted such that the top of the pcb will remain flush other than the soldered in potentiometers. This allows easy mounting of components such as the 3D printed case and other accessories that a user may customise their build with. The design of the circuit also allows all (except the potentiometers), to be placed on the bottom side of the pcb and be hotplatted in one go.

![Component_Placement](/.assets/Macro%20Mixer%20KiCAD%20Bot.png)