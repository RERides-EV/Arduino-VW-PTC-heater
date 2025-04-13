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

// Struct to hold the thresholds for potentiometer stages
struct Thresholds {
  const int stage0 = 8;   // 0-7: 0 elements on
  const int stage1 = 400; // 8-399: 1 element on
  const int stage2 = 930; // 400-929: 2 elements on
  const int stage3 = 1023; // 930-1023: 3 elements on
} thresholds;

// Struct to hold the potentiometer calibration values (3.3V in FrontiEV)
struct PotentiometerRange {
  const int min = 0;   // Minimum potentiometer value
  const int max = 425; // Maximum potentiometer value
} potRange;

// Global variable to store the last stage
int lastStage = -1; // Initialize to an invalid stage (-1) to ensure the relays are set on the first run

// Initializes the heater system
void initializeVWHeater(int relay1Pin, int relay2Pin, int relay3Pin) {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set relay pins as outputs
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);
  pinMode(relay3Pin, OUTPUT);

  // Ensure all relays are off initially (active LOW)
  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);
  digitalWrite(relay3Pin, HIGH);

  Serial.println("VW Heater system initialized. Waiting for potentiometer input...");
}

// Helper function to determine the stage based on the potentiometer value
static int getStage(int potValue) {
  if (potValue < thresholds.stage0) return 0; // Stage 0: All elements off
  if (potValue < thresholds.stage1) return 1; // Stage 1: 1 element on
  if (potValue < thresholds.stage2) return 2; // Stage 2: 2 elements on
  return 3;                                   // Stage 3: 3 elements on
}

// Reads the potentiometer and controls the relays
void updateVWHeater(int potPin, int relay1Pin, int relay2Pin, int relay3Pin) {
  // Read the potentiometer value
  int rawPotValue = analogRead(potPin);

  // Map the raw potentiometer value to the full range (0 to 1023)
  int potValue = map(rawPotValue, potRange.min, potRange.max, 0, 1023);

  // Constrain the mapped value to ensure it stays within 0 to 1023
  potValue = constrain(potValue, 0, 1023);

  // Print the raw and mapped potentiometer values for debugging
  Serial.print("Raw Potentiometer Value: ");
  Serial.print(rawPotValue);
  Serial.print(" | Mapped Potentiometer Value: ");
  Serial.println(potValue);

  // Determine the current stage
  int currentStage = getStage(potValue);

  // Only update the relays if the stage has changed
  if (currentStage != lastStage) {
    setRelays(currentStage, relay1Pin, relay2Pin, relay3Pin);
    lastStage = currentStage; // Update the last stage
  }

  // Small delay to stabilize readings
  delay(200);
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
