/*
  @file ReadWrite.ino
  @brief SD card read/write
  @detail This example shows how to read and write data to and from an SD card file

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

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(SS)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  // nothing happens after setup
}
