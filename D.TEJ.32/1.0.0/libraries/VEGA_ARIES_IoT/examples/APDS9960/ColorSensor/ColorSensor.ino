/*
 @file   ColorSensor.ino
 @brief  This is the test code for the APDS9960 Color sensor
 @detail This example reads color data from the on-board APDS-9960 sensor  
          and prints the color RGB (red, green, blue) values to the Serial Monitor once a second.

 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Required Libraries : Arduino_APDS9960 (Version 1.0.4)
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1
*/

#include <Arduino_APDS9960.h>

TwoWire Wire(8);    //I2C connection  

void setup() {
  delay(2000);
  Serial.begin(115200);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }
}

void loop() {
  #if defined (VEGA_ARIES_IOT)
  
  // check if a color reading is available
  while (! APDS.colorAvailable()) {
    delay(5);
  }
  int r, g, b;

  // read the color
  APDS.readColor(r, g, b);

  // print the values
  Serial.print("r = ");
  Serial.println(r);
  Serial.print("g = ");
  Serial.println(g);
  Serial.print("b = ");
  Serial.println(b);
  Serial.println();

  // wait a bit before reading again
  delay(1000);

  #else
  Serial.println("Choose the correct board! " );
  #endif  
}
