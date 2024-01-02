/**
 @file Timer.h
 @brief header file for Timer driver
 @detail
 */

/***************************************************
 * Module name: Timer.h
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
 * Timer registers and function declarations
 *
 ***************************************************/
#ifndef Timer_h_
#define Timer_h_

/*  Include section
 *
 *
 ***************************************************/

#include "platform.h"
#include <WInterrupts.h>

/*  Defines section
 *
 ***************************************************/

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//#include "config/known_16bit_timers.h"

#define TIMER1_RESOLUTION 65536UL  // assume 16 bits for non-AVR chips

//Timers
#define TIMER0                        0
#define TIMER1                        1
#define TIMER2                        2

/* Register offsets */
#define	TIMER_REG_LoadCount  		0x00	//Timer1 load count register
#define TIMER_REG_CurrentValue 		0x04	//Timer1 current value register
#define	TIMER_REG_Control 			0x08	//Timer1 control register
#define	TIMER_REG_EOI 				0x0C	//Timer1 end-of-interrupt register
#define	TIMER_REG_IntrStatus 		0x10 	//Timer1 interrupt status register

//#define	TIMER_REG_EOI 				0xA4	//TimerN end-of-interrupt register
//#define	TIMER_REG_IntrStatus 		0xA0 	//TimerN interrupt status register
//#define	TIMER_REG_RawIntrStatus 	0xA8 	//TimerN interrupt status register

/*  Function declarations
 *
 ***************************************************/

class Timer {

public:
	Timer(uint32_t _id);
	//volatile uint32_t id;
	//****************************
	//  Configuration
	//****************************
	void initialize(unsigned int microseconds);
	void setPeriod(unsigned int microseconds);

	//****************************
	//  Run Control
	//****************************
	void start();
	void stop();
	void restart();
	void resume();

	//****************************
	//  PWM outputs
	//****************************

	//****************************
	//  Interrupt Function
	//****************************
	void attachInterrupt(void (*isr)());
	void attachInterrupt(void (*isr)(), unsigned long microseconds);
	void detachInterrupt();
	void isr_timer(void);
	void timerPutDelay(uint32_t no_of_clocks);
	uint32_t getCurrentValue(void);

private:
	volatile uint32_t id;
	static unsigned short pwmPeriod;
	static unsigned char clockSelectBits;
	static volatile unsigned int isrCallbackAddr;
	static volatile unsigned int id_isr;
	static unsigned int reload_cycles;
	static const unsigned int ratio = (F_CPU) / (1000000);
	static fp sw_irq_function; //Software IRQ Function pointer.
};

extern Timer Timer0;

#endif

