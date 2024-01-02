/*
 @file bme680Test.ino
 @brief  This is a test code for the BME680 gas, humidity, temperature & pressure sensor
 @detail The values for gas, humidity, temperature & pressure from BME680 will be displayed in serial monitor and oled display if connected

 * Reference aries IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference aries IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Required Libraries : VEGAIoT_BusIO (Version 1.0.0)
 *                      Adafruit Unified Sensor (Version 1.1.9)
 *                      Adafruit SSD1306 (Version 2.5.7)
 *                      Adafruit GFX_Library (Version 1.11.5)
 *                      Adafruit BME680 Library (Version 2.0.2)
 * 
 * Device address -0x76
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT board v1
*/
/***************************************************************************
  This is a library for the BME680 gas, humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME680 Breakout
  ----> http://www.adafruit.com/products/3660

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

TwoWire Wire(8);

Adafruit_BME680 bme; // I2C
//Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

Adafruit_SSD1306 display = Adafruit_SSD1306();

void setup() {
  delay(2000);
  Serial.begin(115200);
  Serial.println(F("BME680 test"));

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop() {
  #if defined (VEGA_ARIES_IOT)
  
  display.setCursor(0,0);
  display.clearDisplay();

  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = "); Serial.print(bme.temperature); Serial.println(" *C");
  display.print("Temperature: "); display.print(bme.temperature); display.println(" *C");

  Serial.print("Pressure = "); Serial.print(bme.pressure / 100.0); Serial.println(" hPa");
  display.print("Pressure: "); display.print(bme.pressure / 100); display.println(" hPa");

  Serial.print("Humidity = "); Serial.print(bme.humidity); Serial.println(" %");
  display.print("Humidity: "); display.print(bme.humidity); display.println(" %");

  Serial.print("Gas = "); Serial.print(bme.gas_resistance / 1000.0); Serial.println(" KOhms");
  display.print("Gas: "); display.print(bme.gas_resistance / 1000.0); display.println(" KOhms");

  Serial.println();
  display.display();
  delay(2000);

  #else
  Serial.println("Choose the correct board! " );
  #endif 
}
