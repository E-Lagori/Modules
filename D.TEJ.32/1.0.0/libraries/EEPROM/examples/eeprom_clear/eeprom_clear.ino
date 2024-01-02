/*
 @file   eeprom_clear.ino
 @brief  clear internal flash 
 @detail The EEPROM.clear() function erase 4KB memory starting from address 0.

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * NOTE : - VEGA ARIES Boards have 2MB flash i.e 2000000 Bytes. From which
 *          256KB is reserved as program memory.
*/

#include <EEPROM.h>

void setup() {
  /***
   * passing 1 in parameter to EEPROM.clear() function
   * (i,e. EEPROM.clear(1)) erase complete flash memory. 
  ***/
  
  EEPROM.clear(); // erase 4KB flash
  
  // turn the LED on when we're done
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  /** Empty loop. **/
}
