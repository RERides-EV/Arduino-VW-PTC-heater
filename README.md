# Arduino-VW-PTC-heater
Arduino Code to control relays for three heating elements

Code developed for FrontiEV electric conversion. Relays driven by Arduino control 80amp relays for each heating element in the VW 12v heater (1K0963235F).

Potentiometer has 5V and GND from Arduino board.

arduino_vw_heat.h and arduino_vw_heat.cpp files should be placed in the Arduino sketch folder.

arduino_vw_heat.h should be included in the .ino file of your build

    #include "arduino_vw_heat.h"

Code uses a potentiometer for input and divides the range into 4 different stages
    Stage 0 has no relays on
    Stage 1 has 1 relay on
    Stage 2 has 2 relays on
    Stage 3 has 3 relays on

A header file might be better, but right now pins are being assigned in the main .INO file.

```
#include "arduino_vw_heat.h"

const int POTENTIOMETER_PIN = A0; // Analog pin for the potentiometer
const int RELAY_CHANNEL1_PIN = 5;       // Relay 1 connected to digital pin 5
const int RELAY_CHANNEL2_PIN = 6;       // Relay 2 connected to digital pin 6
const int RELAY_CHANNEL3_PIN = 7;       // Relay 3 connected to digital pin 7

void setup() {
  // Initialize the heater system with the defined pins
  initializeVWHeater(RELAY_CHANNEL1_PIN, RELAY_CHANNEL2_PIN, RELAY_CHANNEL3_PIN);
}

void loop() {
  // Continuously control the heater based on the potentiometer input
  controlVWHeater(POTENTIOMETER_PIN, RELAY_CHANNEL1_PIN, RELAY_CHANNEL2_PIN, RELAY_CHANNEL3_PIN);
}
```
