#ifndef _SWire_H_INCLUDED
#define _SWire_H_INCLUDED

/**
 @file Wire.h
 @brief header file for Softwire I2C driver
 @detail
 */
/***************************************************
 * Module name: SWire.h
 *
 * Copyright 2020 Company CDAC(T).
 * All Rights Reserved.
 *
 *  The information contained herein is confidential
 * property of Company. The user, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Company.
 *
 *
 * Module Description:
 * I2CI registers and function declarations
 *
 ***************************************************/

#include <Arduino.h>
#include <wiring_digital.h>
#include "variant.h"
#include <stdio.h>
#include "platform.h"


//__BEGIN_DECLS

#define GPIO_0			0
#define GPIO_1			1
#define GPIO_2			2
#define GPIO_3			3
#define GPIO_4			4
#define GPIO_5			5
#define GPIO_6			6



#define HIGH 1
#define LOW 0

class SWire {
public:
SWire();
void init(uint8_t, uint8_t);
void Start(unsigned long start_delay, unsigned long clock_delay);
void Stop(unsigned long frame_delay);
void Restart(unsigned long clock_delay);
void writebyte( unsigned char data, unsigned long clock_delay);
unsigned char readbyte(unsigned long clock_delay);
void StartDelay(unsigned long start);
void ClockDelay(unsigned long clock);
void FrameDelay(unsigned long frame);

int udelay(unsigned int count);

private:
uint8_t sclPin;        
uint8_t sdaPin;        
};
//__END_DECLS

#endif  /*SWire_H_INCLUDED*/
