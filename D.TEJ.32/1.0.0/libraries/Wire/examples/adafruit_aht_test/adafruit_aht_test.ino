/*
  @file adafruit_aht25_test.ino
  @brief AHT25 is a quick-response, calibrated, reliable temperature and humidity sensor.
  @detail This demo will give weather reading of the environment.

   
  * About ARIES Development Boards: https://vegaprocessors.in/devboards/
  * Library Required: Adafruit AHTX0
   
  *** AHT25 Humidity and Temperature Module ***
   
  * Connections:
  * AHT25 pinout: https://www.smart-prototyping.com/image/data/2020/09/102061%20AHT15%20Temperature%20and%20Humidity%20Sensor%20Module/AHT15%20Technical%20Manual.pdf
  ---------------------------------
  |     AHT25     |  Aries Board  |
  ---------------------------------
  |      VDD      |     3.3V      |
  |      SDA      |     SDA0      |
  |      GND      |     GND       |
  |      SCL      |     SCL0      |
  ---------------------------------
  NOTE :: 4.7 KOhms pull-ups are required on SDA and SCL lines. 
*/

#include <Adafruit_AHTX0.h>
TwoWire Wire(0);  // I2C-0
Adafruit_AHTX0 aht;

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  delay(500);
}
