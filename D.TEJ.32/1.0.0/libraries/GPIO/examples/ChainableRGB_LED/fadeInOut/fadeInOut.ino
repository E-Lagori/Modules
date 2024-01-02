/*
 @file fadeInOut.ino
 @brief Example of using the ChainableRGB library for controlling a Grove RGB.
 @detail This code fades in an out colors in a strip of leds.

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

byte power = 0;

void loop()
{
  for (byte i=0; i<NUM_LEDS; i++)
  {
    if (i%2 == 0)
      leds.setColorRGB(i, power, 0, 0);
    else
      leds.setColorRGB(i, 0, 255-power, 0);
  }  
  power+= 10;
  
  delay(10);
}
