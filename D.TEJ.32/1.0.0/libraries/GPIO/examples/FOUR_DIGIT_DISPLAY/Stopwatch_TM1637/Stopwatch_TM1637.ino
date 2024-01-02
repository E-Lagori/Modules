/*
 @file Stopwatch_TM1637.ino
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

#include "Timer.h"
#include <avr/pgmspace.h>
#include "TM1637.h"

#define ON 1
#define OFF 0

int8_t TimeDisp[] = {0x00,0x00,0x00,0x00};
unsigned char ClockPoint = 1;
unsigned char Update;
unsigned char microsecond_10 = 0;
unsigned char second;
unsigned char _microsecond_10 = 0;
unsigned char _second;
unsigned int eepromaddr;
boolean Flag_ReadTime;

#define CLK 1 //pins definitions for TM1637 and can be changed to other ports
#define DIO 0

TM1637 tm1637(CLK,DIO);
Timer Timer(0);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.init();
  Timer.initialize(10000);//timing for 10ms
  Timer.stop();
  Timer.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR
  Serial.println("Please send command to control the stopwatch:");
  Serial.println("S - start");
  Serial.println("P - pause");
  Serial.println("R - reset");
}

// the loop function runs over and over again forever
void loop() {
  char command;
  command = Serial.read();
  switch(command)
  {
    case 'S':
    case 's':stopwatchStart();Serial.println("Start timing...");break;
    case 'P':
    case 'p':stopwatchPause();Serial.println("Stopwatch was paused");break;
    case 'R':
    case 'r':stopwatchReset();Serial.println("Stopwatch was reset");break;
    default:break;
  }
  if(Update == ON)
  {
    TimeUpdate();
    tm1637.display(TimeDisp);
  }

}
//************************************************
void TimingISR() {
  microsecond_10 ++;
  Update = ON;
  if(microsecond_10 == 100){
    second ++;
    if(second == 60)
    {
      second = 0;
    }
    microsecond_10 = 0;
  }
  ClockPoint = (~ClockPoint) & 0x01;
  if(Flag_ReadTime == 0)
  {
    _microsecond_10 = microsecond_10;
    _second = second;
  }
}

void TimeUpdate(void) {
  if(ClockPoint)tm1637.point(POINT_ON);//POINT_ON = 1,POINT_OFF = 0;
  else tm1637.point(POINT_ON);
  TimeDisp[2] = _microsecond_10 / 10;
  TimeDisp[3] = _microsecond_10 % 10;
  TimeDisp[0] = _second / 10;
  TimeDisp[1] = _second % 10;
  Update = OFF;
}

void stopwatchStart() {//timer1 on
  Flag_ReadTime = 0;
  Timer.start();
}

void stopwatchPause() {//to pause stopwatch

  Timer.stop();
}

void stopwatchReset() {
  stopwatchPause();
  Flag_ReadTime = 0;
  _microsecond_10 = 0;
  _second = 0;
  microsecond_10 = 0;
  second = 0;
  Update = ON;
}
