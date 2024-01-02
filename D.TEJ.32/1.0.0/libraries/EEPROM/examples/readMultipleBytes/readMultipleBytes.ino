/*
 @file   readMultipleBytes.ino
 @brief  The demo to read multiple bytes of data from EEPROM. 
 @detail In this example, we are reading 256 bytes of data and display
 *       it on serial monitor.  

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * Note: VEGA ARIES Board has in-built flash of 2MB, we can read 
 *       upto 512 bytes data at a time.
*/

#include <EEPROM.h>
#define READ_LENGTH 256

void setup() {
  // put your setup code here, to run once:
  delay(1000);
  Serial.begin(115200);

  uint8_t buffer[READ_LENGTH];

  // we can read maximum of 512 bytes at a time
  EEPROM.read(buffer, READ_LENGTH, 0); // readbuffer, length, starting address

  if(READ_LENGTH <= 512) {
    Serial.println("Reading data from EEPROM.....");
    for(int i=0; i<READ_LENGTH; i++) {
      if(i%8 == 0)Serial.println();
      Serial.print(buffer[i]); Serial.print("     ");
    }
  }
}

void loop() {
  /** Empty loop. **/
}
