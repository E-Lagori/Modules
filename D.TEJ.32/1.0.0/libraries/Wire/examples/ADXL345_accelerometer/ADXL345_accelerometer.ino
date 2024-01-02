/**
 @file ADXL345_accelerometer.ino
 @brief contains routines for I2C Wire ADXL345 interface
 @detail Includes software functions declarations to initialize,configure, write and read ADXL345 over I2C interface

 * Reference arduino code: https://www.engineersgarage.com/Wire345-accelerometer-arduino-i2c/
 * Refrence aries board: https://vegaprocessors.in/blog/interfacing-adxl345-digital-accelerometer-to-thejas-soc/
 * 
 * ADXL345 accelerometer sensor
 * Device address -0x50
 * Connections:
 * ADXL345     Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * SDA      -   SDA1
 * SCL      -   SCL1
 * For connecting to port 0 (SCL 0 and SDA0) of aries board use the default variable TwoWire Wire(0) instead of TwoWire Wire(1);
 * .
 **/

#include <Wire.h>

TwoWire Wire(1);

void setup() {
Serial.begin(115200);
Wire.begin();

Wire.beginTransmission(0x53);
Wire.write(0x2C); 
Wire.write(0x08); 
Wire.endTransmission();

Wire.beginTransmission(0x53);
Wire.write(0x31); 
Wire.write(0x08); 
Wire.endTransmission();

Wire.beginTransmission(0x53);
Wire.write(0x2D); 
Wire.write(0x08); 
Wire.endTransmission();
}

void loop() {
Wire.beginTransmission(0x53);
Wire.write(0x32); 
Wire.endTransmission();
Wire.requestFrom(0x53, 1);
byte x0 = Wire.read();

Wire.beginTransmission(0x53);
Wire.write(0x33); 
Wire.endTransmission();
Wire.requestFrom(0x53, 1);
byte x1 = Wire.read();
x1 = x1 & 0x03;

uint16_t x = (x1 << 8) + x0;
int16_t xf = x;
if(xf > 511)
{
xf = xf - 1024;
}
float xa = xf * 0.004;
Serial.print("X = "); 
Serial.print(xa);
Serial.print(" g"); 
Serial.println(); 


Wire.beginTransmission(0x53);
Wire.write(0x34); 
Wire.endTransmission();
Wire.requestFrom(0x53, 1);
byte y0 = Wire.read();

Wire.beginTransmission(0x53);
Wire.write(0x35); 
Wire.endTransmission();
Wire.requestFrom(0x53, 1);
byte y1 = Wire.read();
y1 = y1 & 0x03;

uint16_t y = (y1 << 8) + y0;
int16_t yf = y;
if(yf > 511)
{
yf = yf - 1024;
}
float ya = yf * 0.004;
Serial.print("Y = "); 
Serial.print(ya);
Serial.print(" g"); 
Serial.println(); 

Wire.beginTransmission(0x53);
Wire.write(0x36); 
Wire.endTransmission();
Wire.requestFrom(0x53, 1);
byte z0 = Wire.read();

Wire.beginTransmission(0x53);
Wire.write(0x37); 
Wire.endTransmission();
Wire.requestFrom(0x53, 1);
byte z1 = Wire.read();
z1 = z1 & 0x03;

uint16_t z = (z1 << 8) + z0;
int16_t zf = z;
if(zf > 511)
{
zf = zf - 1024;
}
float za = zf * 0.004;
Serial.print("Z = "); 
Serial.print(za);
Serial.print(" g"); 
Serial.println(); 
Serial.println(); 
delay(500);
}
