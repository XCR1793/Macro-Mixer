# Macro Mixer - Software
The software is relatively easy to configure, all you have to do is modify the [Serial_Array](/Software/src/main.cpp#L34) and replace one of the lines with your own custom key. The array must be of size 15 as there are 15 keys, note that the keys are maped from Top Left to Top Right is 1-5, Middle Left to Middle Right is 6-10, Bottom Left to Bottom Right is 11-15. If your not using a key, simpley do:
```cpp
"" // Make sure there is nothing inside it
```

To do Key combination, you have to do:
```cpp
"ctrl+c" // An example of the copy command
```

The software CURRENTLY DOES NOT SUPPORT multi key macros that include sets of multiple keys, however regular combinations such as control, alt or shift are available (Note that the FN key is not supported with the libraries I am using). Multi key macros like (w+d+s+s+s) will be implemented in the future.


Note: This is the KeyAssignment array that you need to modify.

![Serial_Array](/.assets/Macro%20Mixer%20Software.png)