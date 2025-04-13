/*  Controlling VW Heater from Arduino

    Created by David Durazzo
    for RERides EV
    FrontiEV build

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

This code is in the Public Domain
*/

/* The proper pins need to be assigned in the INO file. This is an example.
const int POTENTIOMETER_PIN = A0;       // Analog pin for the potentiometer
const int RELAY_CHANNEL1_PIN = 5;       // Relay 1 connected to digital pin 5
const int RELAY_CHANNEL2_PIN = 6;       // Relay 2 connected to digital pin 6
const int RELAY_CHANNEL3_PIN = 7;       // Relay 3 connected to digital pin 7
*/

#ifndef ARDUINO_VW_HEAT_H
#define ARDUINO_VW_HEAT_H

#include <Arduino.h>

// Function declarations
void initializeVWHeater(int relay1Pin, int relay2Pin, int relay3Pin); // Initializes the heater system
void updateVWHeater(int potPin, int relay1Pin, int relay2Pin, int relay3Pin); // Reads the potentiometer and controls the relays
void setRelays(int stage, int relay1Pin, int relay2Pin, int relay3Pin); // Sets the relays based on the stage

#endif // ARDUINO_VW_HEAT_H
