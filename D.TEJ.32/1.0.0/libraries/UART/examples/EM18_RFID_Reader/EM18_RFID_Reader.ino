/*
  @file EM18_RFID_Reader.ino
  @brief EM-18 is a RFID reader which is used to read RFID tags of frequency 125 kHz.
  @detail Whenever RFID tags comes in range, RFID reader reads its unique ID and transmits it serially to the microcontroller

   Reference arduino code: https://youtu.be/8B14w5t9-MI
   Refrence EM18: https://www.electronicwings.com/sensors-modules/rfid-reader-em18
   EM-18 Reader module pinout: https://components101.com/modules/em18-rfid-reader-module 
   
   **EM-18 Reader Module**
   Connections:
   EM-18     Aries Board
   VCC      -   3.3V
   GND      -   GND
   TX       -   RX1
   For connecting to port 2 (RX2 and TX2) of aries board use the function UARTClass em(2) instead of UARTClass em(1);
*/

#include <UARTClass.h>
UARTClass em(1);

int count=0;
char buffers[12];

void setup(){  
Serial.begin(115200);
em.begin(9600);
}

void loop(){
if(count==12){
count =0;
Serial.print("\n");
}
if(em.available()){
  char input = (char)em.read();
  Serial.print(input);
  count++;
}
}
