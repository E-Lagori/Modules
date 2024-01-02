/*
 @file   eeprom_put.ino
 @brief  This demo shows how to use the EEPROM.put() method. 
 @detail The purpose of this example is to show how the put and get methods 
 *       provide a different behaviour than write and read, that work on 
 *       single bytes. Getting different variables from EEPROM retrieve a 
 *       number of bytes that is related to the variable datatype.  

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * Note: This sketch will pre-set the EEPROM data for the
 *       example sketch eeprom_get.
*/

#include <EEPROM.h>

struct MyObject {
  float field1;
  byte field2;
  char name[10];
};

void setup() {

  Serial.begin(115200);
  EEPROM.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  float f = 123.456f;  //Variable to store in EEPROM.
  int eeAddress = 0;   //Location we want the data to be put.

  //One simple call, with the address first and the object second.
  EEPROM.put(eeAddress, f);
  Serial.println("Written float data type!");

  /** Put is designed for use with custom structures also. **/
  // Data to store.
  MyObject customVar = {
    3.14f,
    65,
    "Working!"
};

  eeAddress += sizeof(float); //Move address to the next byte after float 'f'.
  EEPROM.put(eeAddress, customVar);
  Serial.print("Written custom data type! \n\nView the example sketch eeprom_get to see how you can retrieve the values!");
}

void loop() {

  /* Empty loop */
}
