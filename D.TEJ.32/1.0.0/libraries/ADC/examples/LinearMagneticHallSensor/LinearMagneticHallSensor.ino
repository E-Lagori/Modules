/*
  @file LinearMagneticHallSensor.ino
  @brief Interfacing Linear Magnetic Hall sensor with ARIES v2 
  @detail This demo reads values from both digital and analog interfaces on the Hall Sensor module.
  The digital interface will turn on the Arduino’s LED when a magnetic field is detected.

   Refrence aries board: https://arduinomodules.info/ky-024-linear-magnetic-hall-module/
   
   *** Linear Magnetic Hall sensor  ***
   Connections:
   Hall Sensor       Aries Board
   VCC (+)        -   3.3V
   GND (G)        -   GND
   A0             -   A0
   D0             -   GPIO-3
*/


int led = 22 ; // LED on Aries
int digitalPin = 3; // linear Hall magnetic sensor digital interface
int analogPin = A0; // linear Hall magnetic sensor analog interface
int digitalVal ; // digital readings
int analogVal; // analog readings
void setup ()
{
  pinMode (led, OUTPUT); 
  pinMode (digitalPin, INPUT); 
  Serial.begin(115200);
}
void loop ()
{
  // Read the digital interface
  digitalVal = digitalRead(digitalPin) ; 
  if (digitalVal == HIGH) // When magnetic field is present, Aries LED is on
  {
    digitalWrite (led, LOW);
  }
  else
  {
    digitalWrite (led, HIGH);
  }
  
  // Read the analog interface
  analogVal = analogRead(analogPin);
  Serial.println(analogVal); // print analog value
  delay(100);
}
