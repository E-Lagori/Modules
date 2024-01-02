/*
  @file RTC_SetTime.ino
  @brief contains routines for I2C Wire RTC interface
  @detail Includes software functions declarations to initialize,configure, write and read RTC over I2C interface

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-rtc-with-vega-aries-boards/

  Libraries used: DS1307RTC (by Paul Stoffregen),
                  Time (by Paul Stoffregen)
                  

  *** DS1307 RTC ***

  Device address -0x77 & 0x68

  Connections:
  DS1307     Aries Board
  VCC      -   3.3V
  GND      -   GND
  SDA      -   SDA0
  SCL      -   SCL0

  Note: For connecting to port 1 (SCL1 and SDA1) of aries board use the default variable TwoWire Wire(1) instead of TwoWire Wire(0);
*/

#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

TwoWire Wire(0); // I2C-0

 bool parse=false;
 bool config=false;
  
const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  delay(1000);
  char timeString[9];
  char dateString[12];
  strcpy(timeString, __TIME__);
  strcpy(dateString, __DATE__);
  
  // get the date and time the compiler was run
  if (getDate(dateString) && getTime(timeString)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

}

// the loop function runs over and over again forever
void loop() {
  delay(200);
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
}

bool getTime(char *str) {
  // get the time by seperating the string:
  char* time[3];
  int count = 0;
  char* token = strtok(str, ":");
  while (token != NULL) {
    time[count] = token;
    count++;
    token = strtok(NULL, ":");
  }
  
  if(count == 3) {
    tm.Hour = atoi(time[0]);
    tm.Minute = atoi(time[1]);
    tm.Second = atoi(time[2]); 
    return true;
  }
  return false;
}

bool getDate(char *str) {
  // get the date by seperating the string:
  char* date[3];
  uint8_t monthIndex;

  int count = 0;
  char* token = strtok(str, " ");
  while (token != NULL) {
    date[count] = token;
    count++; 
    token = strtok(NULL, " ");
  }
  if(count != 3) return false;
  
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(date[0], monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = atoi(date[1]);
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(atoi(date[2]));
  return true;
}