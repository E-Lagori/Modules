/*
 @file ReadWrite_String.ino
 @brief Interfacing AT24C256 with Aries V2
 @detail This program interacts with an I2C EEPROM (AT24C256) to write and read data from specific memory locations. 

 * Reference arduino code: https://www.electroschematics.com/arduino/
 * Refrence aries board: https://vegaprocessors.in/blog/eeprom-with-aries-v2-0-board/
 * 
 * Required Libraries:
 * Library Name: AT24C256_library Version 1.0.0 by Dan Tudose
 * 
 * AT24C256 EEPROM
 * Device address -0x50
 * The i2c address can be modified in AT24C256.h
 * 
 * Connections:
 * AT24C256     Aries Board
 * VCC      -   3.3V
 * GND      -   GND
 * SDA      -   SDA0
 * SCL      -   SCL0
 * For connecting to port 1 (SCL 1 and SDA 1) of aries board use the default variable TwoWire Wire(1) instead of TwoWire Wire(0);
*/


#include <AT24C256.h>
#include <Wire.h>
TwoWire Wire(0);
AT24C256 eeprom= AT24C256(0x50);

void setup() {
  delay(2000);
  char message[6];
  char writemessage[] = "Hello";
  delay(1000);
  Serial.begin(115200);
  Serial.println("reading eeprom");
  eeprom.read(0, (uint8_t*) message, sizeof(message));
  Serial.println(message);

  eeprom.write(0, (uint8_t*)writemessage, sizeof(message));
  Serial.println("wrote eeprom");
  
  Serial.println("reading eeprom");
  eeprom.read(0, (uint8_t*) message, sizeof(message));
  Serial.println(message);
}

void loop() {
  // put your main code here, to run repeatedly:

}
