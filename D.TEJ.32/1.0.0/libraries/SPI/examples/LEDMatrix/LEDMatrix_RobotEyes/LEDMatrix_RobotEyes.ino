/*
  @file LEDMatrix_RobotEyes.ino
  @brief Interfacing 8×8 LED DOT Matrix to ARIES V2 Board
  @detail Uses a sequence of bitmaps defined as a font to display animations of eyes to convey emotion. Eyes are coordinated to work together.

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/robot-eyes-using-8x8-led-dot-matrix-with-vega-aries-boards/
  
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
#include <SPI.h>
#include "MD_RobotEyes.h"

// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1

#define CLK_PIN   13  // not required
#define DATA_PIN  11  // not required

#define CS_PIN    10  // connect CS pin to GPIO-10

SPIClass SPI(0);

// SPI hardware interface
MD_MAX72XX M = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX M = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

MD_RobotEyes E;

typedef struct
{
  char name[7];
  MD_RobotEyes::emotion_t e;
  uint16_t timePause;  // in milliseconds
} sampleItem_t;

const sampleItem_t eSeq[] =
{
  { "Nutral", MD_RobotEyes::E_NEUTRAL, 20000 },
  { "Blink" , MD_RobotEyes::E_BLINK, 1000 },
  { "Wink"  , MD_RobotEyes::E_WINK, 1000 },
  { "Left"  , MD_RobotEyes::E_LOOK_L, 1000 },
  { "Right" , MD_RobotEyes::E_LOOK_R, 1000 },
  { "Up"    , MD_RobotEyes::E_LOOK_U, 1000 },
  { "Down"  , MD_RobotEyes::E_LOOK_D, 1000 },
  { "Angry" , MD_RobotEyes::E_ANGRY, 1000 },
  { "Sad"   , MD_RobotEyes::E_SAD, 1000 },
  { "Evil"  , MD_RobotEyes::E_EVIL, 1000 },
  { "Evil2" , MD_RobotEyes::E_EVIL2, 1000 },
  { "Squint", MD_RobotEyes::E_SQUINT, 1000 },
  { "Dead"  , MD_RobotEyes::E_DEAD, 1000 },
  { "ScanV" , MD_RobotEyes::E_SCAN_UD, 1000 },
  { "ScanH" , MD_RobotEyes::E_SCAN_LR, 1000 },
};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize 8x8 LED matrix
  M.begin();
  E.begin(&M);
  E.setText("RobotEyes");
  do { } while (!E.runAnimation()); // wait for the text to finish
}

// the loop function runs over and over again forever
void loop() {
  static uint32_t timeStartDelay;
  static uint8_t index = ARRAY_SIZE(eSeq);
  static enum { S_IDLE, S_TEXT, S_ANIM, S_PAUSE } state = S_IDLE;

  bool b = E.runAnimation();    // always run the animation

  switch (state)
  {
  case S_IDLE:
    index++;
    if (index >= ARRAY_SIZE(eSeq)) 
      index = 0;
    E.setText(eSeq[index].name);
    state = S_TEXT;
    break;

  case S_TEXT: // wait for the text to finish
    if (b)  // text animation is finished
    {
      E.setAnimation(eSeq[index].e, true);
      state = S_ANIM;
    }
    break;

  case S_ANIM:  // checking animation is completed
    if (b)  // animation is finished
    {
      timeStartDelay = millis();
      state = S_PAUSE;
    }
    break;
  
  case S_PAUSE: // non blocking waiting for a period between animations
    if (millis() - timeStartDelay >= eSeq[index].timePause)
      state = S_IDLE;
    break;

  default:
    state = S_IDLE;
    break;
  }
  delay(50);
}
