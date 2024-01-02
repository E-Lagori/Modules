/*
 * @file readDHT11.ino
 * @brief DHT11 is used to read the temperature and humidity of the current environment. 
 *
 * Reference aries board: https://vegaprocessors.in/blog/dht11-temperature-humidity-sensor-with-aries-v2-board/
 * Reference arduino board:  https://github.com/DFRobot/DFRobot_DHT11
 * Arduino Library used: DFRobot_DHT11  
 * 
 * ***DHT11 Temperature Humidity Sensor***
   Connections:
   DHT11        Aries Board
   VCC      -   3.3V
   GND      -   GND
   DATA     -   GPIO-10
 */

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 10    // Connect DATA pin to GPIO-10

void setup(){
  Serial.begin(115200);
}

void loop(){
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  delay(1000);
}
