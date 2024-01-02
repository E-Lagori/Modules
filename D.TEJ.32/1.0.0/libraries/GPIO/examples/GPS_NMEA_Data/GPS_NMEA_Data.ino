/*
  @file GPS_NMEA_Data.ino
  @brief Simple GPS Application
  @detail This code will display GPS output in NMEA sentences

   Aries Board pinout: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf
   Arduino code Reference: https://randomnerdtutorials.com/guide-to-neo-6m-gps-module-with-arduino/
   Library Name: VEGA_SoftwareSerial
   Library Download link: https://gitlab.com/riscv-vega/vega-sensor-libraries/communication/vega_softwareserial

   
   *** UBLOX NEO-6M-GPS ***
   Connections:
   GPS        Aries Board
   GND      -   GND
   TX       -   GPIO-4
   RX       -   GPIO-3
   VCC      -   3.3V


   Example for Understanding NMEA Sentences:
   There are different types of NMEA sentences. The type of message is indicated by the characters before the first comma.
   In the following sentence:
   $GPGGA,110617.00,41XX.XXXXX,N,00831.54761,W,1,05,2.68,129.0,M,50.1,M,,*42

    The GP after the $ indicates it is a GPS position.  
    The $GPGGA is the basic GPS NMEA message, that provides 3D location and accuracy data.
    110617 – represents the time at which the fix location was taken, 11:06:17 UTC
    41XX.XXXXX,N – latitude 41 deg XX.XXXXX’ N
    00831.54761,W – Longitude 008 deg 31.54761′ W
    1 – fix quality (0 = invalid; 1= GPS fix; 2 = DGPS fix; 3 = PPS fix; 4 = Real Time Kinematic; 5 = Float RTK; 6 = estimated (dead reckoning); 7 = Manual input mode; 8 = Simulation mode)
    05 – number of satellites being tracked
    2.68 – Horizontal dilution of position
    129.0, M – Altitude, in meters above the sea level
    50.1, M – Height of geoid (mean sea level) above WGS84 ellipsoid
    empty field – time in seconds since last DGPS update
    empty field – DGPS station ID number
    *42 – the checksum data, always begins with *
    
    *The other NMEA sentences provide additional information:
    $GPGSA – GPS DOP and active satellites
    $GPGSV – Detailed GPS satellite information
    $GPGLL – Geographic Latitude and Longitude
    $GPRMC – Essential GPS pvt (position, velocity, time) data
    $GPVTG – Velocity made good 
*/
 
#include <SoftwareSerial.h>

// The serial connection to the GPS module
SoftwareSerial ss(4, 3); //TX-GPIO-4 and  RX-GPIO-3

void setup(){
  Serial.begin(115200);
  ss.begin(9600);
}

void loop(){
  while (ss.available() > 0){
    // get the byte data from the GPS
    byte gpsData = ss.read();
    Serial.write(gpsData);
    
  }
}
