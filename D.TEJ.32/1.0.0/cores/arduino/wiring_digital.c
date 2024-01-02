// See LICENSE file for license details.

#include "Arduino.h"

__BEGIN_DECLS

/**

 @file wiring_digital.c

 @brief Contains routines to read/write GPIO pins

 */


void pinMode(uint32_t pin, uint32_t mode)
{
	unsigned char gpio_number = 0;
	unsigned short dir_data = 0;
	unsigned short bit_position = 0;
	volatile unsigned short *gpio_0_dir_addr = (volatile unsigned short *)(GPIO_BASE_ADDR +0x40000) ; // GPIO 0 direction register.
	volatile unsigned short *gpio_1_dir_addr = (volatile unsigned short *)(GPI1_BASE_ADDR +0x40000) ; // GPIO 1 direction register.

	// unsigned long gen_gpio_0_addr,gen_gpio_1_addr;
	// volatile unsigned short *gpio_0_data, *gpio_1_data;  ////// warning: unused variable [-Wunused-variable]
	// unsigned short read_data = 0;

	if(pin <= 15)
	      gpio_number = 0;             // Pins 0 to 15 defined in GPIO 0.
	else
	      gpio_number = 1;            // Pins 16 to 31 defined in GPIO 1.

	if(mode == 0)
	{
	if(gpio_number == 0)
	{
		bit_position = (1 << pin);        // Align the selected pin to its position.
	    dir_data =  *gpio_0_dir_addr;         // Address of the direction register.
	    dir_data &= ~(bit_position);        // Clearing a bit configures the pin to be INPUT.
	    *gpio_0_dir_addr = dir_data;        // Data written to direction register.
	    __asm__ __volatile__ ("fence");
	 }

	else if(gpio_number == 1)
	{
		pin = (pin - 16);
	    bit_position = (1 << pin);        // Align the selected pin to its position.
	    dir_data =  *gpio_1_dir_addr;        // Address of the direction register.
	    dir_data &= ~(bit_position);        // Clearing a bit configures the pin to be INPUT.
	    *gpio_1_dir_addr = dir_data;        // Data written to direction register.
	     __asm__ __volatile__ ("fence");
	 }
	 }

	else if(mode == 1)
	{
	if(gpio_number == 0)
	{
		bit_position = (1 << pin);            // Align the selected pin to its position.
	    dir_data =  *gpio_0_dir_addr;             // Address of the direction register.
	    dir_data |= bit_position;            //Setting a bit configures the pin to be OUTPUT.
	    *gpio_0_dir_addr = dir_data;            // Data written to direction register.
	     __asm__ __volatile__ ("fence");
	 }

	else if(gpio_number == 1)
	{
		pin = (pin - 16);
	    bit_position = (1 << pin);            // Align the selected pin to its position.
	    dir_data =  *gpio_1_dir_addr;            // Address of the direction register.
	    dir_data |= bit_position;            //Setting a bit configures the pin to be OUTPUT.
	    *gpio_1_dir_addr = dir_data;            // Data written to direction register.
	     __asm__ __volatile__ ("fence");
	}

	}
	     __asm__ __volatile__ ("fence");
	}



void digitalWrite(uint32_t pin, uint32_t val)
{
	unsigned char gpio_number = 0;
    unsigned short dir_data = 0;
	unsigned short bit_position = 0;
	volatile unsigned short *gpio_0_dir_addr = (volatile unsigned short *)(GPIO_BASE_ADDR +0x40000) ; // GPIO 0 direction register.
	volatile unsigned short *gpio_1_dir_addr = (volatile unsigned short *)(GPI1_BASE_ADDR +0x40000) ; // GPIO 1 direction register.

	unsigned long gen_gpio_0_addr,gen_gpio_1_addr;
	volatile unsigned short *gpio_0_data, *gpio_1_data;

	if(pin <= 15)
		gpio_number = 0;			// Pins 0 to 15 defined in GPIO 0.
	else
		gpio_number = 1;			// Pins 16 to 31 defined in GPIO 1.


	if(gpio_number == 0)
	{
		bit_position = (1 << pin);			// Align the selected pin to its position.
		dir_data =  *gpio_0_dir_addr;	 		// Address of the direction register.
		dir_data |= bit_position;			//Setting a bit configures the pin to be OUTPUT.
		*gpio_0_dir_addr = dir_data;			// Data written to direction register.
		__asm__ __volatile__ ("fence");

		gen_gpio_0_addr = GPIO_BASE_ADDR;		// Base address of GPIO 0.
		gen_gpio_0_addr|=(bit_position << 2);		// Generate address of the selected GPIO pin in GPIO 0.
		gpio_0_data = (unsigned short *)gen_gpio_0_addr;		// Generated address.
		*gpio_0_data = (val << pin);		// Write data to the address.
	}


	else if(gpio_number == 1)
	{
		pin = (pin - 16);
		bit_position = (1 << pin);			// Align the selected pin to its position.
		dir_data =  *gpio_1_dir_addr;			// Address of the direction register.
		dir_data |= bit_position;			//Setting a bit configures the pin to be OUTPUT.
		*gpio_1_dir_addr = dir_data;			// Data written to direction register.
		__asm__ __volatile__ ("fence");

		gen_gpio_1_addr = GPI1_BASE_ADDR;		// Base address of GPIO 1.
		gen_gpio_1_addr|=(bit_position << 2);		// Generate address of the selected GPIO pin in GPIO 0.
		gpio_1_data = (unsigned short *)gen_gpio_1_addr;		// Generated address.
		*gpio_1_data = (val << pin);		// Write data to the address.
	}
		__asm__ __volatile__ ("fence");

		return;
	}


int digitalRead(uint32_t pin)
{
	unsigned char gpio_number = 0;
	unsigned short dir_data = 0;
	unsigned short bit_position = 0;

	volatile unsigned short *gpio_0_dir_addr = (volatile unsigned short *)(GPIO_BASE_ADDR +0x40000) ; // GPIO 0 direction register.
	volatile unsigned short *gpio_1_dir_addr = (volatile unsigned short *)(GPI1_BASE_ADDR +0x40000) ; // GPIO 1 direction register.
	unsigned long gen_gpio_0_addr,gen_gpio_1_addr;

	volatile unsigned short *gpio_0_data, *gpio_1_data;
	unsigned short read_data = 0;

	if(pin <= 15)
		gpio_number = 0; 			// Pins 0 to 15 defined in GPIO 0.
	else
		gpio_number = 1;			// Pins 16 to 31 defined in GPIO 1.


	if(gpio_number == 0)
	{
		bit_position = (1 << pin);		// Align the selected pin to its position.
		dir_data =  *gpio_0_dir_addr; 		// Address of the direction register.
		dir_data &= ~(bit_position);		// Clearing a bit configures the pin to be INPUT.
		*gpio_0_dir_addr = dir_data;		// Data written to direction register.
		__asm__ __volatile__ ("fence");

		gen_gpio_0_addr = GPIO_BASE_ADDR;	// Base address of GPIO 0.
		gen_gpio_0_addr+=(bit_position << 2);	// Generate address of the selected GPIO pin in GPIO 0.
		gpio_0_data = (unsigned short *)gen_gpio_0_addr;	// Generated address.
		read_data = *gpio_0_data; 		// Read data from the address.
	}

	else if(gpio_number == 1)
	{
	pin = (pin - 16);
	bit_position = (1 << pin);		// Align the selected pin to its position.
	dir_data =  *gpio_1_dir_addr;		// Address of the direction register.
	dir_data &= ~(bit_position);		// Clearing a bit configures the pin to be INPUT.
	*gpio_1_dir_addr = dir_data;		// Data written to direction register.
	__asm__ __volatile__ ("fence");

	gen_gpio_1_addr = GPI1_BASE_ADDR;	// Base address of GPIO 1.
	gen_gpio_1_addr+=(bit_position << 2);	// Generate address of the selected GPIO pin in GPIO 1.
	gpio_1_data = (unsigned short *)gen_gpio_1_addr;	// Generated address.
	read_data = *gpio_1_data;		// Read data from the address.
	}
	__asm__ __volatile__ ("fence");

	if(read_data)
		return 1; 				// GPIO pin is High.
	else
		return 0; 				// GPIO pin is Low.
}
__END_DECLS