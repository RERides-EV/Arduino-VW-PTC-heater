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

#include "arduino_vw_heat.h"

// Global variable to store the last stage
int lastStage = -1; // Initialize to an invalid stage (-1) to ensure the relays are set on the first run

// Define the actual range of the potentiometer. These values are for FrontiEV build by RERides
const int minValue = 0; // Replace with the actual minimum value
const int maxValue = 608; // Replace with the actual maximum value

// Initializes the heater system
void initializeVWHeater(int relay1Pin, int relay2Pin, int relay3Pin) {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set relay pins as outputs
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);

  // Ensure all relays are off initially
  digitalWrite(relay1Pin, HIGH); // Relays are active LOW
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);

  Serial.println("VW Heater system initialized. Waiting for potentiometer input...");
}

// Reads the potentiometer and controls the relays
void controlVWHeater(int potPin, int relay1Pin, int relay2Pin, int relay3Pin) {
// Read the potentiometer value
  int rawPotValue = analogRead(potPin);

  // Map the raw potentiometer value to the full range (0 to 1023)
  int potValue = map(rawPotValue, minValue, maxValue, 0, 1023);

  // Constrain the mapped value to ensure it stays within 0 to 1023
  potValue = constrain(potValue, 0, 1023);

  // Print the raw and mapped potentiometer values for debugging
  Serial.print("Raw Potentiometer Value: ");
  Serial.print(rawPotValue);
  Serial.print(" | Mapped Potentiometer Value: ");
  Serial.println(potValue);

  // Determine the stage based on the potentiometer value
  int currentStage;
  if (potValue < STAGE_0_THRESHOLD) {
    currentStage = 0; // Stage 0: All elements off
  } else if (potValue < STAGE_1_THRESHOLD) {
    currentStage = 1; // Stage 1: 1 element on
  } else if (potValue < STAGE_2_THRESHOLD) {
    currentStage = 2; // Stage 2: 2 elements on
  } else {
    currentStage = 3; // Stage 3: 3 elements on
  }

  // Only update the relays if the stage has changed
  if (currentStage != lastStage) {
    setRelays(currentStage, relay1Pin, relay2Pin, relay3Pin);
    lastStage = currentStage; // Update the last stage
  }

  // Small delay to stabilize readings
  delay(100);
}

// Sets the relays based on the stage
void setRelays(int stage, int relay1Pin, int relay2Pin, int relay3Pin) {
  // Turn off all relays initially
  digitalWrite(relay1Pin, HIGH); // Relays are active LOW
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);

  // Turn on relays based on the stage
  if (stage >= 1) {
    digitalWrite(relay1Pin, LOW); // Turn on Relay 1
  }
  if (stage >= 2) {
    digitalWrite(relay2Pin, LOW); // Turn on Relay 2
  }
  if (stage >= 3) {
    digitalWrite(relay3Pin, LOW); // Turn on Relay 3
  }

  // Print the current stage for debugging
  Serial.print("Current Stage: ");
  Serial.println(stage);
}