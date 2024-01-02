/*
  @file LEDMatrix_MAX7219.ino
  @brief Interfacing 8×8 LED DOT Matrix to ARIES V2 Board
  @detail to display "Hello World" on LED Matrix using Aries Board

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/8x8-led-matrix-max7219-tutorial-with-scrolling-text/
  
  Library Name : MD_MAX72XX (by marco_c)
   
  *** 8×8 LED DOT Matrix(MAX7219) ***
  Connections:
   Dot Matrix     Aries Board
   VCC          -   3.3V
   GND          -   GND
   DIN          -   MOSI0
   CS           -   GPIO-10
   CLK          -   SCLK0
*/

#include <MD_MAX72xx.h>
SPIClass SPI(0);

// Define the number of devices we have in the chain and the hardware interface
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN    10  // connect CS pin to GPIO-10

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// We always wait a bit between updates of the display
#define  DELAYTIME  100  // in milliseconds

void scrollText(const char *p) {
  uint8_t charWidth;
  uint8_t cBuf[8];  // this should be ok for all built-in fonts

  mx.clear();

  while (*p != '\0')
  {
    charWidth = mx.getChar(*p++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);

    for (uint8_t i=0; i<=charWidth; i++)  // allow space between characters
    {
      mx.transform(MD_MAX72XX::TSL);
      if (i < charWidth)
        mx.setColumn(0, cBuf[i]);
      delay(DELAYTIME);
    }
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize 8x8 LED matrix
  mx.begin();
}

// the loop function runs over and over again forever
void loop() {
  // replace the string to change output on 8x8 LED Matrix
  scrollText("Hello World");
}
