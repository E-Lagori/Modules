/**
 @file MPU_Roll_Pitch.ino
 @brief contains routines for MPU Wire  interface
 @detail Display the X,Y,Z values for accelerometer and Gyroscope along with Temperature, Roll and pitch values using MPU6050

 * Reference arduino code: https://www.engineersgarage.com/Wire345-accelerometer-arduino-i2c/
 * Refrence aries board: https://vegaprocessors.in/blog/interfacing-adxl345-digital-accelerometer-to-thejas-soc/
 * 
 * MPU Gyro sensor
 * Device address -0x68
 * Connections:
 * MPU     Aries Board
 * 3V3      -   3.3V
 * GND      -   GND
 * SDA      -   SDA1
 * SCL      -   SCL1
 * For connecting to port 0 (SCL0 and SDA0) of aries board use the default variable TwoWire Wire(0) instead of TwoWire Wire(1);
 * .
 **/
#include <Wire.h>
#include "MPU6050_res_define.h"

TwoWire Wire(1);

#define TRUE 1
#define FALSE 0


int mpu6050 = 0x68; // The MPU6050 sensor I2C address
float Xa,Ya,Za,t,Xg,Yg,Zg; // final Outputs
signed short Ax,Ay,Az,T,Gx,Gy,Gz; // raw Outputs

float RateRoll, RatePitch, RateYaw;
float AngleRoll, AnglePitch,AngleYaw;
uint32_t LoopTimer;

void setup() {
  delay(2000);
  Serial.begin(115200);
  Wire.begin();
  Serial.println("mpu6050"); 
  
   //System clock =100MHz and I2C clock =100 kHz
  // Start communicating with the device
  Wire.beginTransmission(mpu6050); // Start with device write address 
  Wire.write(SMPLRT_DIV);   //Write to sample rate register 0x19
  Wire.write(0x07);     //1KHz sample rate
  delayMicroseconds(100);
  Wire.endTransmission(true);
  delayMicroseconds(100); 
  Wire.beginTransmission(mpu6050);
  Wire.write(PWR_MGMT_1);    //Write to power management register 0x6B
  Wire.write(0x01);    //X axis gyroscope reference frequency
  Wire.endTransmission(true);
  delayMicroseconds(100);
  
  
  Wire.beginTransmission(mpu6050);
  Wire.write(CONFIG);      // Write to Configuration register 0x1A
  Wire.write(0x00);    //Fs = 8KHz
  Wire.endTransmission(true);
  delayMicroseconds(100);
  
  
  Wire.beginTransmission(mpu6050);
  Wire.write(GYRO_CONFIG);   //Write to Gyro configuration register 0x1B
  Wire.write(0x18);    //Full scale range +/- 2000 degree/C
  Wire.endTransmission(true);
  delayMicroseconds(100);
}

  void loop () {
      Wire.beginTransmission(mpu6050);
      Wire.write(ACCEL_XOUT_H); // Start with register ACCEL_XOUT_H 0x3B
      Wire.endTransmission(true);
      Wire.requestFrom(mpu6050, 14, true); 
      
      
      Ax = ((Wire.read() << 8) | Wire.read()); //Accelerometer x-axis raw data 
      Ay = ((Wire.read() << 8) | Wire.read()); // Accelerometer y-axis raw data 
      Az = ((Wire.read() << 8) | Wire.read()); // Accelerometer z-axis raw data 
      T  = ((Wire.read() << 8) | Wire.read()); // //temperature raw data
      Gx = ((Wire.read() << 8) | Wire.read()); // Gyro x axis raw data 
      Gy = ((Wire.read() << 8) | Wire.read()); // Gyro y axis raw data 
      Gz = ((Wire.read() << 8) | Wire.read()); // Gyro z axis raw data 
      Wire.endTransmission(true);
      
      
    delayMicroseconds(30000);
      
    
      
      Xa = (float)Ax/16384.0 -0.04; //Accelerometer x-axis data in 2g unit
      Ya = (float)Ay/16384.0; // Accelerometer y-axis data in g unit
      Za = (float)Az/16384.0 +0.40; // Accelerometer z-axis data in g unit
      Xg = (float)Gx/131.0;   // Gyro x axis data in degree/seconds unit
      Yg = (float)Gy/131.0;   // Gyro y axis data in degree/seconds unit
      Zg = (float)Gz/131.0;  // Gyro z axis data in degree/seconds unit
      t = ((float)T/340.00)+36.53;  //temperature in degree/Celcius , Convert temperature in °/c using formula 

      AngleRoll = atan(Ya/sqrt(Xa*Xa+Za*Za))*1/(3.142/180);
      AnglePitch = atan(Xa/sqrt(Ya*Ya+Za*Za))*1/(3.142/180);
     
       // final out
      Serial.print("Xa: ");
      Serial.print(Xa);
      Serial.print("  ");
      Serial.print("Ya: ");
      Serial.print(Ya);
      Serial.print("  ");
      Serial.print("Za: ");
      Serial.print(Za);
      Serial.print("  ");
      Serial.print("Xg: ");
      Serial.print(Xg);
      Serial.print("  ");
      Serial.print("Yg: ");
      Serial.print(Yg);
      Serial.print("  ");
      Serial.print("Zg: ");
      Serial.print(Zg);
      Serial.print("  ");
      Serial.print("t: ");
      Serial.print(t);
      Serial.print("  ");

      Serial.print("Roll: ");
      Serial.print(AngleRoll);
      Serial.print("  ");
      Serial.print("Pitch: ");
      Serial.print(AnglePitch);
      Serial.print("  ");
      Serial.println(" ");
      
      delay(100);       
}
