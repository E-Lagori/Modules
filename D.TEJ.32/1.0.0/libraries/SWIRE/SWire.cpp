/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  SWire.cpp
 * Brief Description of file             :  Driver to control the SMBUS i2c device.
 * Name of Author                        :  Mydhily M R
 * Email ID                              :  mydhily@cdac.in

 Copyright (C) 2020  CDAC(T). All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.

 ***************************************************************************/


/**
 @file SWire.cpp
 @brief Contains routines for different SoftWire SMBUS I2C functions
 @detail
 */

/*  Include section
 *
 ***************************************************/


#include <Arduino.h>
#include "variant.h"
#include <stdio.h>
#include "platform.h"
#include "SWire.h"


/** @fn SWire::SWire()
 @brief Initialize i2c Port.
 @details This function initialize the I2C port.
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 */


SWire::SWire()
{
	//empty
}

/** @fn void  SWire::StartDelay(unsigned long start)
 @brief I2C start delay
 @details This function initialize the I2C port.
 @warning
 @param[in]  unsigned long start
 @param[Out] No output parameter
 */

void  SWire::StartDelay(unsigned long start) {    

  delayMicroseconds(start);    //250 us for mlx
}


void  SWire::ClockDelay(unsigned long clock) {

 delayMicroseconds(clock);       //5 us
}

void  SWire::FrameDelay(unsigned long frame) {

 delayMicroseconds(frame);     //10us
}



/** @fn void SWire::init(uint8_t scl_pin, uint8_t sda_pin)
 @brief I2C pin declarations
 @details This function initialize the I2C port.
 @warning
 @param[in]  uint8_t scl_pin, uint8_t sda_pin
 @param[Out] No output parameter
 */

void SWire::init(uint8_t scl_pin, uint8_t sda_pin)
{
  sclPin = scl_pin;
  sdaPin = sda_pin;
}

/**
 @fn void SWire::Start()
 @brief I2C start funcion
 @details Function to start SMBUS i2c
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */

void SWire::Start(unsigned long start_delay, unsigned long clock_delay)
{
  pinMode(sclPin,OUTPUT);
  pinMode(sdaPin,OUTPUT);
  

  digitalWrite(sdaPin, HIGH);
  digitalWrite(sclPin, HIGH);
  StartDelay(start_delay);
  digitalWrite(sdaPin, LOW);
  ClockDelay(clock_delay);
  digitalWrite(sclPin, LOW);
}

/**
 @fn void SWire::Stop()
 @brief I2C Stop function
 @details Function to stop SMBUS i2c
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */

void SWire::Stop(unsigned long frame_delay)
{
  pinMode(sclPin,OUTPUT);
  pinMode(sdaPin,OUTPUT);

  digitalWrite(sdaPin, LOW);
  digitalWrite(sclPin, HIGH);
  FrameDelay(frame_delay);
  FrameDelay(frame_delay);
  digitalWrite(sdaPin, HIGH);
  FrameDelay(frame_delay);
}

/**
 @fn void SWire::Restart()
 @brief Repeated Start 
 @details Function for implementing Repeated Start in SMBUS i2c
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */

void SWire::Restart(unsigned long clock_delay)
{
  pinMode(sclPin,OUTPUT);
  pinMode(sdaPin,OUTPUT);

  digitalWrite(sdaPin, LOW);
  digitalWrite(sclPin, LOW);
  ClockDelay(clock_delay);
  digitalWrite(sdaPin, HIGH);
  ClockDelay(clock_delay);
  digitalWrite(sclPin, HIGH);
  ClockDelay(clock_delay);
  digitalWrite(sdaPin, LOW);
  ClockDelay(clock_delay);
  digitalWrite(sclPin, LOW);
}

/**
 @fn void SWire::writebyte( unsigned char data)
 @brief Write to i2c
 @details Write Function for SMBUS i2c
 @param[in]  unsigned char data -- Data to be written is passed here
 @param[Out] No output parameter
 @return Void function.
 */

void SWire::writebyte(unsigned char data, unsigned long clock_delay)
{
  pinMode(sclPin,OUTPUT);
  pinMode(sdaPin,OUTPUT);

  digitalWrite(sdaPin, LOW);
  digitalWrite(sclPin, LOW);

  for (int i = 0; i < 8; i++)
  {
    //delayMicroseconds(5);
    if (data & 0x80)
    {
      digitalWrite(sdaPin, HIGH);
    }
    else
    {
      digitalWrite(sdaPin, LOW);
    }
    data = data << 1;
    ClockDelay(clock_delay);
    digitalWrite(sclPin, HIGH);
    ClockDelay(clock_delay);
    digitalWrite(sclPin, LOW);
  }
  //ACK = GPIO_read_pin(SDA);
  pinMode(sdaPin,INPUT);
  ClockDelay(clock_delay);
  digitalWrite(sclPin, HIGH);
  ClockDelay(clock_delay);
  digitalWrite(sclPin, LOW);
}

/**
 @fn unsigned char SWire::readbyte()
 @brief Read from i2c device
 @details Read Function for SMBUS i2c
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return data
 */

unsigned char SWire::readbyte(unsigned long clock_delay)
{
  unsigned char data = 0, bits;
  pinMode(sclPin,OUTPUT);
  pinMode(sdaPin,INPUT);


 // digitalWrite(sdaPin, HIGH);
  digitalWrite(sclPin, LOW);
  ClockDelay(clock_delay);

  for (int i = 0; i < 8; i++)
  {
    ClockDelay(clock_delay);
    digitalWrite(sclPin, HIGH);
    ClockDelay(clock_delay);
    bits = digitalRead(sdaPin);
    digitalWrite(sclPin, LOW);
    data = data | (bits << (7 - i));
  }
  //ack
  pinMode(sdaPin,OUTPUT);
  digitalWrite(sdaPin, LOW);
  ClockDelay(clock_delay);
  digitalWrite(sclPin, HIGH);
  ClockDelay(clock_delay);
  digitalWrite(sclPin, LOW);
  return data;
}


