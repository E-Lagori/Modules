/*
 @file   ProximitySensor.ino
 @brief  This is the test code for the APDS9960 Proximity sensor
 @detail This example reads proximity data from the on-board APDS-9960 sensor of the Nano 33 BLE Sense 
          and prints the proximity value to the Serial Monitor every 100 ms.

 * Reference aries IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference aries IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Required Libraries : Arduino_APDS9960 (Version 1.0.4)
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1
*/

#include <Wire.h>
#include <Arduino_APDS9960.h>

TwoWire Wire(8);    //I2C connection  

void setup() {
  delay(2000);
  Serial.begin(115200);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  }
}

void loop() {
  #if defined (VEGA_ARIES_IOT)
  
  // check if a proximity reading is available
  if (APDS.proximityAvailable()) {
    // read the proximity
    // - 0   => close
    // - 255 => far
    // - -1  => error
    int proximity = APDS.readProximity();

    // print value to the Serial Monitor
    Serial.println(proximity);
  }

  // wait a bit before reading again
  delay(100);

  #else
  Serial.println("Choose the correct board! " );
  #endif 
}
