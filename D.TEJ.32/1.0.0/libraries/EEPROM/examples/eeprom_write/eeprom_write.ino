/*
 @file   eeprom_write.ino
 @brief  write data into internal flash via SPI 
 @detail Stores values from 0 to 255 into the EEPROM starting from addressess 0.
 *       These values will stay in the EEPROM when the board is
 *       turned off and may be retrieved later by another sketch.  

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * NOTE : - VEGA ARIES Boards have 2MB flash i.e 2000000 Bytes. From which
 *          256KB is reserved as program memory.
 *        - We can write upto 256 bytes at a time.
*/

#include <EEPROM.h>

/** the current addressess in the EEPROM (i.e. which byte we're going to write to next) **/
int address = 0;

void setup() {
  
  EEPROM.begin();
    /***
    Each byte of the EEPROM can only hold a
    value from 0 to 255.
  ***/

  Serial.println("Writing on EEPROM....");
  /***
    Write the value to the appropriate byte of the EEPROM.
    these values will remain there when the board is
    turned off.
  ***/

  for(int data = 0; data < PAGE_SIZE; data++) {
    EEPROM.write(address, data);
    address++;
  }

  // Turn on LED once we're done
  digitalWrite(LED_BUILTIN, LOW);

  delay(100);
}

void loop() {
  /** Empty setup. **/
}
