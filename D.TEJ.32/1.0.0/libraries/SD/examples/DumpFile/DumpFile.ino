/*
  @file DumpFile.ino
  @brief SD card file dump
  @detail This example shows how to read a file from the SD card using the
          SD library and send it over the serial port.

  Useful links:
   
  * About VEGA Processors: https://vegaprocessors.in/
  * About Development board: https://vegaprocessors.in/devboards/
  * Blogs : https://vegaprocessors.in/blog/
  
   
  *** Catalex MicroSD Card Adapter v1.0 ***
  Connections:
  SD-Card Module     Aries Board
  VCC             -   5V
  GND             -   GND
  MISO            -   MISO-1
  MOSI            -   MOSI-1
  SCK             -   SCLK-1
  CS              -   GPIO-10
*/

#include <SPI.h>
#include <SD.h>

SPIClass SPI(1);

const int chipSelect = SS;

void setup() {
  // Open serial communications and wait for port to open:
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt");

  // if the file is available, write to it:
  if (dataFile) {
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    dataFile.close();
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

void loop() {
}
