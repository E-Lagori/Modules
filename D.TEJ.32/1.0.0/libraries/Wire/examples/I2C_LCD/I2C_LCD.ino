/*
 @file I2C_LCD.ino
 @brief Interfacing I2C LCD with Aries V2
 @detail This program will display messages within a delay of 2 seconds in I2C LCD 

 * Reference arduino code: https://arduinogetstarted.com/tutorials/arduino-lcd-i2c
 * Refrence aries board: https://vegaprocessors.in/blog/bmp180-digital-pressure-sensor-with-aries-v2-board/
 * Library Name : LiquidCrystal I2C
 * Library Version: 1.1.2
 * 
 * I2C LCD
 * Device address -0x27
 * Connections:
 * I2C LCD     Aries Board
 * VCC      -   3.3V/5V
 * GND      -   GND
 * SDA      -   SDA1
 * SCL      -   SCL1
 * For connecting to port 0 (SCL 0 and SDA0) of aries board use the default variable TwoWire Wire(0) instead of TwoWire Wire(1);
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

TwoWire Wire(1);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
}

void loop()
{
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Aries");        // print message at (0, 0)
  lcd.setCursor(2, 1);         // move cursor to   (2, 1)
  lcd.print("GetStarted"); // print message at (2, 1)
  delay(2000);                 // display the above for two seconds

  lcd.clear();                  // clear display
  lcd.setCursor(3, 0);          // move cursor to   (3, 0)
  lcd.print("CDAC");        // print message at (3, 0)
  lcd.setCursor(0, 1);          // move cursor to   (0, 1)
  lcd.print("www.cdac.in"); // print message at (0, 1)
  delay(2000);                  // display the above for two seconds
}
