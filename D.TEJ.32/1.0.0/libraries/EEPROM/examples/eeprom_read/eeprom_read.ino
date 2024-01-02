/*
 @file   eeprom_read.ino
 @brief  read internal flash via SPI 
 @detail Reads the value of each byte of the EEPROM and prints it to the computer.  

 * Reference VEGA ARIES board: https://vegaprocessors.in/devboards/
 * Reference VEGA Processors : https://vegaprocessors.in/
 * 
 * NOTE : - VEGA ARIES Boards have 2MB flash i.e 2000000 Bytes. From which
 *          256KB is reserved as program memory.
 *        - We can read upto 512 bytes at a time.
*/

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  address = address + 1;
  if (address == PAGE_SIZE) {
    address = 0;
  }

  delay(500);
}
