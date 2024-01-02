/*
  @file Datalogger.ino
  @brief SD card datalogger
  @detail This example shows how to log data from three analog sensors
          to an SD card using the SD library.

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

void setup() {
  // Open serial communications and wait for port to open:
  delay(1000);
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(SS)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  // make a string for assembling the data to log:
  char dataString[32] = { 0, };
  int sensor[3];
  
  for (int analogPin = 0; analogPin < 3; analogPin++) {
    sensor[analogPin] = analogRead(analogPin);
  }
  sprintf(dataString, "%d, %d, %d", sensor[0], sensor[1], sensor[2]);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
