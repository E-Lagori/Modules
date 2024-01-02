/*
 @file Four_Digit_Display_TM1637.ino
 @brief contains routines for TM1637 interface
 @detail Includes software functions declarations to initialize,configure, write and read TSM1637

 Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-tm1637-four-digit-7-segment-display-with-vega-aries-boards/

 Library Name : Grove 4-Digit Display (by Seeed Studio)
 
 *** TM1637 4 Digit 7-Segment Display ***
 Connections:
   TM1637     Aries Board
   VCC      -   3.3V
   GND      -   GND
   CLK      -   GPIO1
   DIO      -   GPIO0
*/

#include <TM1637.h>

int CLK = 1; //CLK of TM1637 is connected to GPIO-1 pin of Aries Board
int DIO = 0;  //DI0 of TM1637 is connected to GPIO-0 pin of Aries Board

TM1637 tm(CLK,DIO);

void setup() {
  // put your setup code here, to run once:
  tm.init();

  //set brightness; 0-7
  tm.set(2);
}

void loop() {
  // put your main code here, to run repeatedly:

  // example: "12:ab"
  // tm.display(position, character);
  tm.display(0,10);
  tm.display(1,11);
  tm.point(1);
  tm.display(2,12);
  tm.display(3,13);

  delay(1000);

  // example: "1234"
  displayNumber(1234);

  delay(1000);
}

void displayNumber(int num){   
    tm.display(3, num % 10);   
    tm.display(2, num / 10 % 10);   
    tm.display(1, num / 100 % 10);   
    tm.display(0, num / 1000 % 10);
}
