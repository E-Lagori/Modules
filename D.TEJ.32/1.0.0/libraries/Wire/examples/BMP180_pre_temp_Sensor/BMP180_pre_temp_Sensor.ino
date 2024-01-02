/*
  @file bmp180_pre_temp_sensor.ino
  @brief contains routines for I2C Wire BMP180 sensor interface
  @detail Includes software functions declarations to initialize,configure, write and read BMP180 over I2C interface

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-bmp180-digital-pressure-sensor-with-vega-aries-boards/

  Library Name : Adafruit BMP085 Library
 
  *** BMP180 pressure temeperature sensor ***
  Device address -0x77
 
  Connections:
   BMP180     Aries Board
   VIN      -   3.3V
   GND      -   GND
   SDA      -   SDA1
   SCL      -   SCL1
  
  Note: For connecting to port 0 (SCL 0 and SDA0) of aries board use the default variable TwoWire Wire(0) instead of TwoWire Wire(1);
*/

#include <Wire.h>
#include <Adafruit_BMP085.h>

#define seaLevelPressure_hPa 1013.25

TwoWire Wire(1); // I2C-1
Adafruit_BMP085 bmp;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  delay(1000);
  
  // Initialize I2C 
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
}
  
// the loop function runs over and over again forever
void loop() {
  // Display data on serial monitor
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");

  Serial.print("Altitude = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

  Serial.print("Real altitude = ");
  Serial.print(bmp.readAltitude(seaLevelPressure_hPa * 100));
  Serial.println(" meters");
  
  Serial.println();
  delay(500);
}
