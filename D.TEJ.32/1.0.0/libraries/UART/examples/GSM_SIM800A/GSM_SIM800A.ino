/*
  @file GSM_SIM800A.ino
  @brief Learn how to interface GSM SIM800A with ARIES V.2.
  @detail A call will be generated to the given phone no. upon successfull connection
  Reference arduino code: https://www.youtube.com/watch?v=mhUClLI92Dw
  Refrence aries board: https://vegaprocessors.in/blog/
   
  **SIM 800A/SIM 900A GSM module**
  
  Connections:
  VCC      -   12V (connect VCC of SIM800A module using 12V adapter)
   
   SIM800A     Aries Board
   GND      -   GND
   RXD      -   TX1
   TXD      -   RX1
   For connecting to port 2 (RX2 and TX2) of aries board use the function UARTClass mySerial(2) instead of UARTClass mySerial(1);
*/


#include <UARTClass.h>


UARTClass mySerial(1);

void setup()
{
// Open serial communications and wait for port to open:
Serial.begin(115200);

Serial.println("Calling through GSM Modem");

// set the data rate for the SoftwareSerial port
mySerial.begin(9600);
delay(2000);
mySerial.println("ATD7034710XXX;"); // ATDXXXXXXXXXX; -- watch out here for semicolon at the end!!

Serial.println("Called 7034710XXX");
}

void loop() // run over and over
{
// print response over serial port
if (mySerial.available())
Serial.write(mySerial.read());
}
