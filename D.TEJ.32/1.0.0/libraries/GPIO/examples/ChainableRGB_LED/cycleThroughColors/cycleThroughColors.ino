/*
 @file cycleThroughColors.ino
 @brief Example of using the ChainableRGB library for controlling a Grove RGB.
 @detail This code cycles through all the colors in an uniform way. This is accomplished using a HSL color space.

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

float hue = 0.0;
boolean up = true;

void loop()
{
  for (byte i=0; i<NUM_LEDS; i++)
    leds.setColorHSL(i, hue, 1.0, 0.5);
    
  delay(50);
    
  if (up)
    hue+= 0.025;
  else
    hue-= 0.025;
    
  if (hue>=1.0 && up)
    up = false;
  else if (hue<=0.0 && !up)
    up = true;
}
