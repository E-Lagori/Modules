/*
 @file ClockDisplay_TM1637.ino
 @brief contains routines for TM1637 interface
 @detail Includes software functions for working of TM1637 4 Digit 7-Segment Display with ARIES v2.0 Board

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
 
#include <Timer.h>
#include "TM1637.h"

#define ON 1
#define OFF 0

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char halfsecond = 0;
unsigned char second;
unsigned char minute = 0;
unsigned char hour = 12;

#define CLK 1 // pins definitions for TM1637 and can be changed to other ports // CLK = GPIO-1
#define DIO 0 // connect DIO pin to GPIO-0

TM1637 tm1637(CLK,DIO);
Timer Timer(2);

// the setup function runs once when you press reset or power the board
void setup() {
  tm1637.set();
  tm1637.init();
   
  Timer.initialize(500000);//timing for 500ms
  Timer.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR  
}

// the loop function runs over and over again forever
void loop() {
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  }
}

void TimingISR() {
  halfsecond ++;
  Update = ON;
  if(halfsecond == 2){
    second ++;
    if(second == 60)
    {
      minute ++;
      if(minute == 60)
      {
        hour ++;
        if(hour == 24)hour = 0;
        minute = 0;
      }
      second = 0;
    }
    halfsecond = 0;
  }
  ClockPoint = (~ClockPoint) & 0x01;
}

void TimeUpdate(void) {
  if(ClockPoint)tm1637.point(POINT_ON);
  else tm1637.point(POINT_OFF);
  TimeDisp[0] = hour / 10;
  TimeDisp[1] = hour % 10;
  TimeDisp[2] = minute / 10;
  TimeDisp[3] = minute % 10;
  Update = OFF;
}
