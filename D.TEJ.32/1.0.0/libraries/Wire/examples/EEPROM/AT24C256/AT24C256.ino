/*
 @file AT24C256.ino
 @brief Interfacing AT24C256 with Aries V2
 @detail This program interacts with an I2C EEPROM (AT24C256) to write and read data from specific memory locations. 

 * Reference arduino code: https://www.electroschematics.com/arduino/
 * Refrence aries board: https://vegaprocessors.in/blog/eeprom-with-aries-v2-0-board/
 * 
 * AT24C256 EEPROM
 * Device address -0x50
 * 
 * Connections:
 * AT24C256     Aries Board
 * VCC      -   3.3V
 * GND      -   GND
 * SDA      -   SDA0
 * SCL      -   SCL0
 * For connecting to port 1 (SCL 1 and SDA 1) of aries board use the default variable TwoWire Wire(1) instead of TwoWire Wire(0);
*/


#include <Wire.h>

TwoWire Wire(0);

#define M1 0x50 // Device Address

void setup() {
  delay(2000);
  Serial.begin(115200);
  Wire.begin();
  unsigned int address = 1;
  writeEEPROM(M1, address, 0x18);
  readEEPROM(M1, address);
} 

void loop()
{}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); //LSB
  Wire.write(data);
  Serial.println(Wire.endTransmission()); 
  delay(20);
}

void readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));   // MSB
  Wire.write((int)(eeaddress & 0xFF)); //LSB
  Serial.println(Wire.endTransmission());
  delay(5);
  Wire.requestFrom(deviceaddress, 1);

  if (Wire.available() > 0) {
    Serial.println(Wire.read(), HEX);
  } else {
    Serial.println("NO DATA!");
  }
}
