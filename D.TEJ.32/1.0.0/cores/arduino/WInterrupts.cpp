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

#include "Arduino.h"
#include "wiring_private.h"
#include "encoding.h"
#include "UARTClass.h"


#include <string.h>

volatile fp irq_table[64]; //Array of Function pointer.
volatile fp sw_irq_function; //Software IRQ Function pointer.
extern volatile unsigned long INTERRUPT_Handler_0;
extern volatile unsigned long trap_entry;

/*
 * \brief Specifies a named Interrupt Service Routine (ISR) to call when an interrupt occurs.
 *        Replaces any previous function that was attached to the interrupt.
 */
void attachInterrupt(uint8_t intr_number, void (*irq_handler)(), uint32_t mode) {
	// Should be enableInterrupt()
  // *************************Interrupt Enable*************************** //
  set_csr(mie, MIP_MEIP);			// Set MEIE bit in MIE register for Machine External Intr.
  set_csr(mstatus, MSTATUS_MIE);		// Set global machine intr bit (3rd bit) in MSTATUS register.
  write_csr(mtvec,(uint32_t)&INTERRUPT_Handler_0);		// Set MTVEC register with vector address.
  MACHINE_INT_ENABLE |= ((unsigned long)1 << intr_number);	// Enable interrupt for peripheral in interrupt controller.
	__asm__ __volatile__ ("fence");
  
  // *************************Register IRQ Handler*************************** //
  irq_table[intr_number] = irq_handler;
}


void interrupt_handler(void) {

	void (*func_ptr)();
	unsigned int mcause_val = 0, trap_type=0;

  trap_type = (read_csr(mcause) >> 31);



	if(trap_type){ //Interrupt

		mcause_val = ((read_csr(mcause) << 1)>>1);

		if(mcause_val == 3) {// Machine software interrupt
			clear_csr(mip, MIP_MSIP);	// Clear MSIP bit in MIP register for Machine 
			sw_irq_function(); // Invoke the peripheral handler as function pointer.	
		} else {
		
			unsigned int intr_status = MACHINE_INT_STATUS; // Read interrupt status register.

			for(unsigned int i = 0; i < MAXIMUM_INTR_COUNT ; i++)  /*MAXIMUM_INTR_COUNT*/
			{
				if ((intr_status >> i) & (unsigned int)1){
					irq_table[i]();// Invoke the peripheral handler as function pointer.
				}
			}
		}
	}
	else
	{ //Exception
		func_ptr = (void (*)()) (&trap_entry); //jump to exception handler
		func_ptr();
	}	
}


void detachInterrupt(uint32_t intr_number) {

	MACHINE_INT_ENABLE &= ~((uint32_t)1 << intr_number);	// Disable interrupt for peripheral in interrupt controller.
	irq_table[intr_number] = 0;
	__asm__ __volatile__ ("fence");
}
