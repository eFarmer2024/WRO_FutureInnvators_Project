#include <Wire.h>
#include "HUSKYLENS.h"

HUSKYLENS huskylens;


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  // Initialize Serial1 at 9600 baud

  // Initialize I2C communication as Master
  Wire.begin();

  // Initialize HUSKYLENS
  if (!huskylens.begin(Serial1)) {
    Serial.println("HUSKYLENS initialization failed!");
    while (1); // Halt execution if initialization fails
  } else {
    Serial.println("HUSKYLENS ready!");
  }

  // Set the algorithm to tag recognition
  huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);
}

void loop() {
  // Request data from HUSKYLENS
  if (huskylens.request()) {
    // Check if any tag is detected
    if (huskylens.available()) {
      Serial.println("Tag detected!");
      
      // Send signal to Arduino Uno (Slave) to start its loop
      Wire.beginTransmission(8);  // Address of the Arduino Uno
      Wire.write(1);              // Send a byte (signal)
      Wire.endTransmission();
    }
  } else {
    Serial.println("Request data failed!");
  }

  delay(100);  // Small delay to avoid overwhelming the bus
}
