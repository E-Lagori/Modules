// ---------------------------------------------------------------- /
// Aries I2C Scanner
// Using Arduino IDE 1.8.19
// Using BMP-180 module for the target
// Tested on 30 June 2023
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
// ---------------------------------------------------------------- /

#include <Wire.h> //include Wire.h library

TwoWire Wire(0);    //Connect sensor to I2C-0 in Aries v2

void setup()
{
  delay(2000);
  Wire.begin();           // Wire communication begin
  Serial.begin(115200);   // The baudrate of Serial monitor is set in 9600
  while (!Serial);        // Waiting for Serial Monitor
  Serial.println("\nI2C Scanner");
  Wire.setClock(400000);
}

void loop()
{
  byte error, address; //variable for error and I2C address
  int nDevices;

  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    delay(10);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // wait 5 seconds for the next I2C scan
}
