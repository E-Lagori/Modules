/*
 @file ReadWrite.ino
 @brief Interfacing AT24C256 with Aries V2
 @detail This program interacts with an I2C EEPROM (AT24C256) to write and read data from specific memory locations. 

 * Reference arduino code: https://www.electroschematics.com/arduino/
 * Refrence aries board: https://vegaprocessors.in/blog/eeprom-with-aries-v2-0-board/
 * 
 * Required Libraries:
 * Library Name: AT24C256 Version 1.0.0 by Paul Gaudre
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


#include <Wire.h>                   //I2C library
#include "AT24C256.h"

TwoWire Wire(0);

//Create Object
AT24C256 eeprom = AT24C256();

//this val will be wrote the the chip. An int is used here.
int val = 24;

//The address on wich val will be wrote
int Add = 0;

void setup() 
{
  delay(2000);
  //Start Serial and i2c
  Serial.begin(115200);
  Wire.begin();
 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() 
{
  //Write val to the address
  Serial.print("Writing of "); 
  Serial.print(val); 
  Serial.print(" on ");  
  Serial.println(Add);
  eeprom.write(val, Add);

  //print the val read in the address specified and print it to serial
  Serial.println(eeprom.read(Add));

  //Stop
   while(1);
} 
