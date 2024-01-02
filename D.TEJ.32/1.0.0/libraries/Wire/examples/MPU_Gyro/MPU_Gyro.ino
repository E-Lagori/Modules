/**
 @file MPU_Gyro.ino
 @brief contains routines for MPU Wire  interface
 @detail Learn how to interface MPU with Aries board

 * Reference arduino code: https://www.engineersgarage.com/Wire345-accelerometer-arduino-i2c/
 * Refrence aries board: https://vegaprocessors.in/blog/interfacing-adxl345-digital-accelerometer-to-thejas-soc/
 * 
 * MPU Gyro sensor
 * Device address -0x68
 * Connections:
 * MPU     Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * SDA      -   SDA0
 * SCL      -   SCL0
 * For connecting to port 1 (SCL 1 and SDA1) of aries board use the default variable TwoWire Wire(1) instead of TwoWire Wire(0);
 * .
 **/
#include<Wire.h>

TwoWire Wire(0);
const int MPU_addr = 0x68;    //The default address of the MPU is 0x68


void setup() {
  Serial.begin(115200);    //Here we will begin the I2C communication
  Serial.println ("Hit a key to start");     // signal initalization done
  while (Serial.available() == 0);
  Wire.begin();
  Wire.beginTransmission(MPU_addr);     //Begin transmission with the MPU
  
  //First, we tell the MPU which register we are writing to
  Wire.write(0x6B);

  //Second, we send the values that we discussed previously
  Wire.write(0x00);
  //we will end the transmission and restart it.
  Wire.endTransmission(true);
  delay(50);
  Wire.beginTransmission(MPU_addr);
  

  //According to those values, we want to send the value 0 0 0 1 0 0 0 0, which is dec 16 hex 0x10
  //And remember, we want to send it to 0x1B
  Wire.write(0x1B);
  Wire.write(0x10);

  //End and restart transmission
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr);

  //Next, let's do the accelerometer, the full scale range can be +-2g. The address is 0x1C
  Wire.write(0x1C);
  Wire.write(0x00);

  //Once we send the values, we end the transmission because we don't have any further data to send for now
  Wire.endTransmission(true);
}

void loop() {

  //First, lets create an 8 bit int to temporarily store the value
  byte XAxis = 0;
  //A byte is an 8 bit value. Assigning it to 0 means it is now 00000000

  //Let's go ahead and read the first register, ACCEL_XOUT_H
  Wire.beginTransmission(MPU_addr);
  //Tell the MPU that we want the data from register 59 (0x3B in hex)
  Wire.write(0x3B);
  //Send a Restart - we won't actually end the transmission, just send it a restart. 
  Wire.endTransmission(false);

  //We will now wait until we have data available

  //Now we will reguest 1 register from the MPU. The third parameter 'true' says that we are ending the transmission after we get the data.
  Wire.requestFrom(MPU_addr, 1, true);
  //Now we will assign the byte from before to the value we are reading.
  XAxis = Wire.read();
  //I'm getting 0x00. This probably depends on how it is sitting on your desk, etc.

  //NOTE: we really shouldn't be breaking up the measurements like this, since the value can change in an instant. But for education purposes, this should work fine.
  byte XAxisL = 0;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3C);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 1, true);
  XAxisL = Wire.read();

  //If we bit shift the XAxis 8 units to the right, it would be XAxis = 1111 1110 0000 0000. Then if we OR the Xaxis and XAxisL we would get 1111 1110 0101 0100. 
  int16_t XAxisFull = XAxis << 8 | XAxisL;
  
  // according to the MPU register map on page 29, we can see that with our Full Scale range we selected, the sensitivity is 16384 LSB/g. So, divide -468 by 16384 and we get 0.02856g. We'll do more with that later.
  float XAxisFinal = (float) XAxisFull / 16384.0;

  // We will read the Y and Z axis accel data from registers 0x3D to 0x40
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3D);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 4, true);
  int16_t YAxisFull =  (Wire.read() << 8 | Wire.read());
  int16_t ZAxisFull =  (Wire.read() << 8 | Wire.read());
  float YAxisFinal = (float)YAxisFull / 16384.0;
  float ZAxisFinal = (float) ZAxisFull / 16384.0;
  Serial.print("X Axis = ");
  Serial.print(XAxisFinal);
  Serial.println("g");
  Serial.print("Y Axis = ");
  Serial.print(YAxisFinal);
  Serial.println("g");
  Serial.print("Z Axis = ");
  Serial.print(ZAxisFinal);
  Serial.println("g");

  //by extrapolating our angle and what X and Y should be, and then finding if there is any additional acceleration. But let's move on to the temperature sensor - use page 30 of the register map

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x41);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 2, true);

  delay(500);
}
