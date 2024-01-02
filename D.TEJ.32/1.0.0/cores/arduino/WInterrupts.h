/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_INTERRUPTS_
#define _WIRING_INTERRUPTS_

#include <stdint.h>

__BEGIN_DECLS

//      LOW 0
//      HIGH 1
// #define CHANGE 2
#define FALLING 3
// #define RISING 4

typedef void (*fp)(void); //Declares a type of a void function that accepts an void

#define DEFAULT 1
#define EXTERNAL 0
#define MAXIMUM_INTR_COUNT 32

#define RAW_INTRUPPT 		            (*(volatile unsigned long*)0x20010000)
#define MACHINE_INT_ENABLE 		      (*(volatile unsigned long*)0x20010008)
#define MACHINE_INT_STATUS 	        (*(volatile unsigned long*)0x20010010)

// #define digitalPinToInterrupt(P) (INT_GPIO_BASE + variant_pin_map[P].bit_pos) 

  typedef void (*voidFuncPtr)(void);

/*
 * \brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs. Use digitalPinToInterrupt(pin) to get the correct intnum.
 *        Other interrupt numbers are available, see platform.h.
 *        Replaces any previous function that was attached to the interrupt.
 */
// void attachInterrupt(uint32_t intnum, voidFuncPtr callback, uint32_t mode);
void attachInterrupt(uint8_t intr_number, void (*irq_handler)(), uint32_t mode);
/*
 * \brief Turns off the given interrupt.
 */
// void detachInterrupt(uint32_t intnum);
void detachInterrupt(uint32_t intr_number); 
void interrupt_handler(void);

__END_DECLS

#endif
