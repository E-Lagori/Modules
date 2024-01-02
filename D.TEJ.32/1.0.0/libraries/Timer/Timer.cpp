/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  Timer.cpp
 * Brief Description of file             :  Driver to control the Timer devices.

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
 @file Timer.cpp
 @brief Contains routines for different Timer funtions
 @detail
 */

/*  Include section
 *
 ***************************************************/

#include "Timer.h"
#include "Arduino.h"
#include "wiring_private.h"
#include "encoding.h"
#include <string.h>

Timer Timer0(0);              // preinstatiate

/*  Global variable section
 *
 ***************************************************/

extern volatile unsigned int INTERRUPT_Handler_0;
extern volatile fp irq_table[64]; //Array of Function pointer.

unsigned short Timer::pwmPeriod = 0;
unsigned char Timer::clockSelectBits = 0;
volatile unsigned int Timer::isrCallbackAddr = 0;
volatile unsigned int Timer::id_isr = 0;
unsigned int Timer::reload_cycles = 0;

/** @fn Timer::Timer(uint32_t _id) :id(_id)
 @brief Initialize Timer Port.
 @details This function initialize the Timer port.
 @warning
 @param[in]  unsigned int _id: This parameter sets Timer Port.
 '0' = Timer PORT 0, '1' = Timer PORT 1, '2' = Timer PORT 2
 @param[Out] No output parameter
 */
Timer::Timer(uint32_t _id) :
		id(_id) {

}

/**
 @fn void Timer::isr_timer(void)
 @brief load, enable and wait for interrupt
 @details The selected timer is loaded with the no of clocks and it is enabled with intr unmasked. The timer module waits untill it interrupts.
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */

void Timer::isr_timer(void) {	// intr handler

	void (*timerIsrCallback)();

	//volatile unsigned int EOI =
	TIMER_REG(id_isr, TIMER_REG_EOI);//clear timer interrupt

	//volatile unsigned int EOI = TIMER_REG(id_isr, TIMER_REG_EOI);//clear timer interrupt

	 //volatile unsigned int istatus = TIMER_REG(id_isr, TIMER_REG_IntrStatus);//clear timer interrupt
	//EOI = istatus;
	//Serial.println("eoi addr:");
	//Serial.print((unsigned int) &(TIMER_REG(id_isr, TIMER_REG_EOI)), 16);
	//return;
	timerIsrCallback = (fp) isrCallbackAddr;
	timerIsrCallback();

}

//****************************
//  Configuration
//****************************

/**
 @fn void Timer::initialize(unsigned int microseconds)
 @brief Timer initialization
 @details
 @param[in]  unsigned int microseconds - Timer microseconds to be used
 @param[Out] No output parameter
 @return Void function.
 */
void Timer::initialize(unsigned int microseconds) {

	setPeriod(microseconds);
	id_isr = id;
}

/**
 @fn void Timer::setPeriod(unsigned int microseconds)
 @brief Set time period of Timer
 @details
 @param[in]  unsigned int microseconds - Timer microseconds to be used
 @param[Out] No output parameter
 @return Void function.
 */
void Timer::setPeriod(unsigned int microseconds) {
	unsigned int cycles = microseconds * ratio;

	reload_cycles = cycles;

	if (cycles > 0xffffffff)
		Serial.println("timer not supported for this value");

	TIMER_REG(id,TIMER_REG_Control) = 0x0;	// Disable timer.
	TIMER_REG(id,TIMER_REG_LoadCount) = cycles;	// Load timer with no of clocks.

}

//****************************
//  Run Control
//****************************

/**
 @fn void Timer::start()
 @brief Enable timer interrupt in unmasked & user defined mode..
 @details
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */
void Timer::start() {
	TIMER_REG(id,TIMER_REG_Control) = 0x03;	// Enable timer with intr unmasked.
}

/**
 @fn void Timer::stop()
 @brief Disable timer interrupt in unmasked & user defined mode..
 @details
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */
void Timer::stop() {
	TIMER_REG(id,TIMER_REG_Control) = 0x0;		// Disable timer.
}

/**
 @fn void Timer::restart()
 @brief Restart timer interrupt in unmasked & user defined mode..
 @details
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */
void Timer::restart() {
	TIMER_REG(id,TIMER_REG_Control) = 0x03;	// Enable timer with intr unmasked.
}

/**
 @fn void Timer::resume()
 @brief Resume timer interrupt in unmasked & user defined mode..
 @details
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */
void Timer::resume() {
	TIMER_REG(id,TIMER_REG_Control) = 0x03;	// Enable timer with intr unmasked.
}

//****************************
//  Interrupt Function
//****************************

/**
 @fn void Timer::attachInterrupt(void (*isr)(), unsigned long microseconds)
 @brief Enable timer interrupt in unmasked & default defined mode.
 @details
 @param[in]  void (*isr)())
 @param[in]  unsigned long microseconds
 @param[Out] No output parameter
 @return Void function.
 */
void Timer::attachInterrupt(void (*isr)(), unsigned long microseconds) {
	if (microseconds > 0)
		setPeriod(microseconds);
	attachInterrupt(isr);
	id_isr = id;
}

/**
 @fn void Timer::detachInterrupt()
 @brief Disable timer interrupt in unmasked & default mode.
 @details
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */
void Timer::detachInterrupt() {
	TIMER_REG(id,TIMER_REG_Control) = 0x0;		// Disable timer.

	MACHINE_INT_ENABLE &= ~((unsigned int) (1 << (7 + id)));// Enable interrupt for peripheral in interrupt controller.
}

/**
 @fn void Timer::attachInterrupt(void (*user_isr)())
 @brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs
 @details Replaces any previous function that was attached to the interrupt.
 @param[in]  void (*user_isr)()
 @param[Out] No output parameter
 @return Void function.
 */

void Timer::attachInterrupt(void (*user_isr)()) {

	unsigned int intr_number = (7 + id);

	// Should be enableInterrupt()
	// *************************Interrupt Enable*************************** //
	set_csr(mie, MIP_MEIP);	// Set MEIE bit in MIE register for Machine External Intr.
	set_csr(mstatus, MSTATUS_MIE);// Set global machine intr bit (3rd bit) in MSTATUS register.
	write_csr(mtvec, (uint32_t) (&INTERRUPT_Handler_0));// Set MTVEC register with vector address.
	MACHINE_INT_ENABLE |= ((unsigned int) (1 << intr_number));// Enable interrupt for peripheral in interrupt controller.
	//Serial.read();

	// *************************Register IRQ Handler*************************** //

	irq_table[intr_number] =  (volatile fp) (&isr_timer);

	isrCallbackAddr = (unsigned int) user_isr;

	TIMER_REG(id,TIMER_REG_Control) = 0x03;	// Enable timer with intr unmasked.
}

void Timer::timerPutDelay(uint32_t no_of_clocks) {

	TIMER_REG(id,TIMER_REG_Control) = 0x0;		// Disable timer.
	__asm__ __volatile__ ("fence");
	TIMER_REG(id,TIMER_REG_LoadCount) = no_of_clocks;	// Load timer with no of clocks.
	__asm__ __volatile__ ("fence");
	TIMER_REG(id,TIMER_REG_Control) = 0x07;		// Enable timer with intr masked
	__asm__ __volatile__ ("fence");
}

uint32_t Timer::getCurrentValue(void) {

	uint32_t currentTime = TIMER_REG(id, TIMER_REG_CurrentValue);
	return currentTime;
}