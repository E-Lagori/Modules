/*
  @file LCD_20_4_Demo.ino
  @brief Simple LCD Application
  @detail Printing Hello world on 20/4 LCD Display

  Aries-LCD Connection Reference: https://create.arduino.cc/projecthub/hrsajjad844/lcd-display-without-potentiometer-and-resistor-0d1357
  LCD Pinout Reference: https://www.instructables.com/Interfacing-20x4-LCD-with-Arduino/
   
   *** LCD Display ***
   Connections:
   LCD        Aries Board
   D4         -   5
   D5        -    4
   D6        -    7
   D7        -    2
   E         -   11
   RS        -   12
   A         -   5V
   K         -   GND
   VDD       -   5V
   VSS       -   GND
   V0        -    6
   RW        -    GND
 * 10K Potentiometer:
 * ends to +5V and ground
   Connect Output of Potentiometer to V0 of LCD 
   Connect VCC of Potentiometer to 5V of Aries Board
   Connect GND of Potentiometer to GND of Aries Board  
*/

// include the library code:
#include <LiquidCrystal.h>
//int Contrast=1000;


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  
//analogWrite(6,Contrast);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("Hello");

  lcd.setCursor(2, 1);
  lcd.print("Welcome");

  // print the number of seconds since reset:
  lcd.setCursor(11, 3);
  lcd.print(millis() / 1000);
}
