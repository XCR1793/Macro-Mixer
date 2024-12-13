#include <Arduino.h>
#include <FastLED.h>
#include <USB.h>
#include <USBHIDKeyboard.h>
#include <USBHIDMouse.h>

#define led_pin 35
#define led_count 21

CRGB leds[led_count];

// L: 8, 7, 6
// R: 5, 4, 1
// Row Top: 21, 47, 48, 37, 38
// Row Mid: 14, 13, 12, 11, 10
// Row Bot: 9 , 18, 17, 16, 15
int pins[] = {1, 4, 5, 38, 37, 48, 47, 21, 8, 7, 6, 9, 18, 17, 16, 15, 10, 11, 12, 13, 14};

#define NUM_PINS (sizeof(pins) / sizeof(pins[0]))

// Create USB HID Keyboard instance
USBHIDKeyboard keyboard;

// Create USB HID Mouse instance
USBHIDMouse mouse;

/** #################################
 *  #                               #
 *  #     Key Macro Assignments     #
 *  #                               #
 *  #################################
*/

const char* KeyAssignments[NUM_PINS] = {
  "shift",
  "q",
  "w",
  "e",
  "ctrl",
  "right_click",
  "a",
  "s",
  "d",
  "",
  "left_click",
  "ctrl",
  "esc",
  "c",
  " "
};

/** #################################
 *  #                               #
 *  #     Key Macro Assignments     #
 *  #                               #
 *  #################################
*/

void sendKeyCombination(const char* combination) {
  String combStr = String(combination);
  int start = 0, idx;
  String keys[3]; // Max of 3 keys in a combination
  int keyCount = 0;

  // Check for mouse actions first
  if (combStr == "left_click") {
    mouse.click(MOUSE_LEFT);
    return;
  } else if (combStr == "right_click") {
    mouse.click(MOUSE_RIGHT);
    return;
  } else if (combStr == "middle_click") {
    mouse.click(MOUSE_MIDDLE);
    return;
  }

  // Parse keyboard combination string by '+'
  while ((idx = combStr.indexOf('+', start)) != -1 && keyCount < 3) {
    keys[keyCount++] = combStr.substring(start, idx);
    start = idx + 1;
  }
  keys[keyCount++] = combStr.substring(start);

  // Send keyboard keys
  for (int i = 0; i < keyCount; i++) {
    if (keys[i] == "ctrl") {
      keyboard.press(KEY_LEFT_CTRL);
    } else if (keys[i] == "alt") {
      keyboard.press(KEY_LEFT_ALT);
    } else if (keys[i] == "shift") {
      keyboard.press(KEY_LEFT_SHIFT);
    } else if (keys[i] == "esc") {
      keyboard.press(KEY_ESC);
    } else if (keys[i].length() == 1) { // Single character key
      keyboard.press(keys[i][0]);
    }
  }
}

void releaseKeyCombination(const char* combination) {
  String combStr = String(combination);
  int start = 0, idx;
  String keys[3];
  int keyCount = 0;

  while ((idx = combStr.indexOf('+', start)) != -1 && keyCount < 3) {
    keys[keyCount++] = combStr.substring(start, idx);
    start = idx + 1;
  }
  keys[keyCount++] = combStr.substring(start);

  for (int i = 0; i < keyCount; i++) {
    if (keys[i] == "ctrl") {
      keyboard.release(KEY_LEFT_CTRL);
    } else if (keys[i] == "alt") {
      keyboard.release(KEY_LEFT_ALT);
    } else if (keys[i] == "shift") {
      keyboard.release(KEY_LEFT_SHIFT);
    } else if (keys[i] == "esc") {
      keyboard.release(KEY_ESC);
    } else if (keys[i].length() == 1) {
      keyboard.release(keys[i][0]);
    }
  }
}


// Pin Mapper
int mapPinValue(int pin) {
  if (pin >= 0 && pin <= 4) {
    // Map 0 to 4 to 4 to 0
    return 4 - pin;
  } else if (pin >= 10 && pin <= 14) {
    // Map 10 to 14 to 5 to 9
    return 19 - pin;
  } else if (pin >= 5 && pin <= 9) {
    // Map 5 to 9 to 10 to 14
    return pin + 5;
  }
  // If the pin is out of the expected range, return the same value
  return pin;
}


// Initialise Variables
signed int internalDelay[NUM_PINS] = {};
signed int pressdelay = 25; // ################# Synchronised Timing delay in ms #################

void setup(){
  // Enable Serial
  Serial.begin(115200);

  // Initialise All Pins
  for(size_t i = 0; i < led_count; i++){
    pinMode(pins[i], INPUT);
  }

  // Begin Keyboard Library
  keyboard.begin();

  // Begin USB Library
  USB.begin();

  // Initialise Addressable LEDs
  FastLED.addLeds<WS2812, led_pin, GRB>(leds, led_count);

  // Everything Loaded Confirmation
  Serial.println("USB Keyboard Initialised");
}

void loop(){
  signed int pin = 0;
  for(size_t i = 0; i < NUM_PINS; i++){
    if((pins[i] >= 1 && pins[i] <= 5) || (pins[i] >= 6 && pins[i] <= 8)){
      pin--;
      // Read Potentiometer Values Here
    }else if(digitalRead(pins[i])){
      // if((pin <= sizeof(KeyAssignments)) && (internalDelay[i] <= 0)){ // Switch the if statment below with this one to enable synchronised timing
      if(pin <= sizeof(KeyAssignments)){ // Switch this with above to enable synchronised timing
        Serial.println(KeyAssignments[mapPinValue(pin)]);
        sendKeyCombination(KeyAssignments[mapPinValue(pin)]);
        // internalDelay[i] = pressdelay; // Enable this to Allow the keys to set timers (REQUIRED FOR SYNCHRONISED TIMING)
      }
    }else if(!digitalRead(pins[i])){
      releaseKeyCombination(KeyAssignments[mapPinValue(pin)]);
    }
    pin++;
  }
  // for(size_t i = 0; i < NUM_PINS; i++){ // This is required to count the timer for Synchronised Timing
  //   internalDelay[i] = internalDelay[i] - 1;
  //   if(internalDelay[i] <= 0){
  //     internalDelay[i] = 0;
  //   }
  // }
  delay(1);
}

