/*
  @file Max485_Slave.ino
  @brief Communication between 2 aries boards using Max485 
  @detail When push button in Master Aries board is pressed. LED connected to slave Aries board will blink.

   Reference arduino code: https://embeddedthere.com/how-to-interface-arduino-with-rs485-modbus-protocol-using-max485-module/

   **Components Required : Aries Boards(2), MAX485(2), Pushbutton, LED, 10K resistor,100K resistor
   
   **MAX485**
  Connections:-Aries Board(1st Aries Board - to be configures as Master)
  MAX485 (1st one)     Aries Board(1st Aries Board - to be configures as Master)
   R0               -   RX1
   DI               -   TX1
   DE,RE            -   GPIO-7
   VCC              -   3.3V
   GND              -   GND
   A                -   pin A of another Max485
   B                -   pin B of another Max485

  Push button           Aries Board(1st Aries Board - to be configures as Master)
   One side         -   GPIO-2 of Aries board
   Other side       -   GND

  10K Resistor          
   One side         -   Push button and GPIO-2
   Other side       -   VCC(3.3V)
  

  Connections:-Aries Board(2nd Aries Board - to be configures as Slave)
  MAX485 (2nd one)     Aries Board(2nd Aries Board - to be configures as Slave)
   R0               -   RX1
   DI               -   TX1
   DE,RE            -   GPIO-7
   VCC              -   3.3V
   GND              -   GND
   A                -   pin A of another Max485
   B                -   pin B of another Max485

  LED                 Aries Board(1st Aries Board - to be configures as Master)
   +ve              -   100K Resistor
   -ve              -   GND

 100K Resistor          
   One side         -   LED +ve terminal
   Other side       -   GPIO-8 of Aries board

   
   For connecting to port 2 (RX2 and TX2) of aries board use the function UARTClass maxsensor(2) instead of UARTClass maxsensor(1);
*/

#include <UARTClass.h>

UARTClass maxsensor(1);


char led_status; //  Initialize the LED status

void setup() {
 Serial.begin(115200);
  maxsensor.begin(9600); // arduino default baud rate for serial communication
  pinMode(7, OUTPUT); //DE,RE Controling pin of RS-485
  pinMode(8, OUTPUT); //pin 8 set as output for LED
  digitalWrite(7,LOW); //DE,RE = LOW, RS485 Receive Enabled
}

void loop() {
   while(maxsensor.available() > 0){ // wait untill all the bytes receive from data buffer
    
      led_status = maxsensor.read(); 
      Serial.println(led_status);
      delay(10);
     
      //Serial.println(led_status);
      if(led_status=='0'){ // check if command 0
        digitalWrite(8,HIGH); // LED pin high means LED ON
        maxsensor.println("LED ON");
       } 
      if(led_status=='1'){ // check if command 1
        digitalWrite(8,LOW); // LED pin low means LED OFF
        maxsensor.println("LED OFF");
      }
    }
}
