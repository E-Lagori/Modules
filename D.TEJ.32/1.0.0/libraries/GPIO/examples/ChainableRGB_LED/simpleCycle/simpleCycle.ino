/*
 @file simpleCycle.ino
 @brief Example of using the ChainableRGB library for controlling a Grove RGB.
 @detail This code puts a red dot (led) moving along a strip of blue dots.

 * Reference Links:
 * VEGA ARIES Boards: https://vegaprocessors.in/devboards/
 * VEGA Processors: https://vegaprocessors.in/
 
 * Library Name : VEGA_ChainableLED (by VEGA_Processor)
 
 * Grove Chianable RGB LED v2.0 
 * Connections:
 * RGB LED     Aries Board
 * VCC      -   3.3V
 * GND      -   GND
 * CIN      -   GPIO7
 * DIN      -   GPIO8
*/

#include <ChainableLED.h>

#define NUM_LEDS  5

ChainableLED leds(7, 8, NUM_LEDS); // CLK, DIN

void setup()
{
  leds.init();
}

byte pos = 0;

void loop()
{
  for (byte i=0; i<NUM_LEDS; i++)
  {
    if (i==pos)
      leds.setColorRGB(i, 255, 0, 0);  
    else
      leds.setColorRGB(i, 0, 0, 255); 
  }
  delay(250);
  
  pos = (pos+1) % NUM_LEDS;
}
