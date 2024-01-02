/*
 @file   writeMultipleBytes.ino
 @brief  The demo to write multiple bytes of data on EEPROM. 
 @detail In this example, we are writing 256 bytes of data on EEPROM. 

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * Note: VEGA ARIES Board has in-built flash of 2MB, we can write 
 *       upto 256 bytes at a time.
*/

#include <EEPROM.h>
#define WRITE_LENGTH 256

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  EEPROM.begin();

  uint8_t buffer[WRITE_LENGTH];
  
  for(int i=0; i<WRITE_LENGTH; i++) {
    buffer[i] = i;
  }
  
  // we can write 256 bytes of data at a time
  EEPROM.write(buffer, WRITE_LENGTH, 0); // writebuffer, length, starting address
  
  // turn the LED on when we're done
  if(WRITE_LENGTH <= 256)
    digitalWrite(LED_BUILTIN, LOW);
  else
    digitalWrite(24, LOW);
}

void loop() {
  /** Empty loop. **/
}
