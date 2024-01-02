/*
  @file p91_inchOledDisplay.ino
  @brief This is an example for our Monochrome OLEDs based on SSD1306 drivers
  @detail Display texts of different size on OLED display using ARIES Boards 
  
  * About ARIES Development Boards: https://vegaprocessors.in/devboards/
  
  * Library Required : Adafruit SSD1306 
  *                    Adafruit GFX Library
  *                    Adafruit BusIO
  
  *** 0.91 Inch Oled Display ***
  
  * Connections:
  ---------------------------------
  | Oled Display  |  Aries Board  |
  ---------------------------------
  |     VCC       |     3.3V      |
  |     GND       |     GND       |
  |     SDA       |     SDA0      |
  |     SCL       |     SCL0      |
  ---------------------------------
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

TwoWire Wire(0);  // I2C-0

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

#define OLED_RESET     -1 // Reset pin # not using
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...
}

void loop() {
  testdrawstyles();    // Draw 'stylized' characters
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(15,0);             // Start at top
  display.println(F("VEGA PROCESSORS"));

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Draw 'inverse' text
  display.setCursor(35,9);
  display.println(F("CDAC"));

  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(13,25);
  display.print(F("THIRUANANTAPURAM"));

  display.display();
  delay(2000);
}
