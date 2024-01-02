/*
 @file NumberFlow_TSM1637.ino
 @brief contains routines for I2C TSM1637 interface
 @detail Includes software functions declarations to initialize,configure, write and read TSM1637 over I2C interface

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
 **/
 
#include "TM1637.h"

#define CLK 1  // pins definitions for TM1637 and can be changed to other ports
#define DIO 0

TM1637 tm1637(CLK,DIO);

// the setup function runs once when you press reset or power the board
void setup() {
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL); // BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

// the loop function runs over and over again forever
void loop() {
  int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//0~9,A,b,C,d,E,F
  int8_t ListDisp[4];
  unsigned char i = 0;
  unsigned char count = 0;
  delay(150);
  while(1)
  {
    i = count;
    count ++;
    if(count == sizeof(NumTab)) count = 0;
    for(unsigned char BitSelect = 0;BitSelect < 4;BitSelect ++)
    {
      ListDisp[BitSelect] = NumTab[i];
      i ++;
      if(i == sizeof(NumTab)) i = 0;
    }
    tm1637.display(0,ListDisp[0]);
    tm1637.display(1,ListDisp[1]);
    tm1637.display(2,ListDisp[2]);
    tm1637.display(3,ListDisp[3]);
    delay(1000);
  }
}
