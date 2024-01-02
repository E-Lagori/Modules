/*
  @file Max485_Master.ino
  @brief Communication between 2 aries boards using Max485 
  @detail When push button connected in Master Aries board is pressed. LED connected to slave Aries board will blink.

   Reference arduino code: https://embeddedthere.com/how-to-interface-arduino-with-rs485-modbus-protocol-using-max485-module/

   **Components Required : Aries Boards(2), MAX485(2), Pushbutton, LED, 10K resistor,100K resistor
   
   **MAX485**
  Connections:-Aries Board(1st Aries Board - to be configures as Master)
  MAX485               Aries Board(1st Aries Board - to be configures as Master)
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

bool button_state=0; //  Initialize the button state

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
  maxsensor.begin(9600); // arduino default baud rate for serial communication
  pinMode(7, OUTPUT); // DE,RE Controling pin of RS-485
  pinMode(2, INPUT); // pin 2 set as input with PULL-UP for button
  digitalWrite(7,HIGH); // DE,RE = HIGH, RS485 Transmit Enabled
  
}

void loop() {
  

  // put your main code here, to run repeatedly:
  if(digitalRead(2) == 0){ // check if button is prasssed or not. If digitalRead() function return 0 than the button is pressed because we use input pull-up for pin 2
      
      delay(300); // wait 300ms to prevent debouncing
      button_state = !button_state; // evry time when button pressed button state will reverse it value from 0 to 1 or 1 to 0
      //Serial.println(button_state);
      if(button_state==0){
      //button_state = 1; 
      maxsensor.write("0"); 
      Serial.println("0");    // print the value in serial monitor
      }
      
      else{
      maxsensor.write("1");
      Serial.println("1");
      }
      //delay(300); 
   }
  // delay(1000);
  //  Serial.println(digitalRead(2));

}
