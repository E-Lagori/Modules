/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  UARTClass.cpp
 * Brief Description of file             :  Driver to control the UART device.
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
 @file UARTClass.cpp
 @brief Contains routines for UART interface
 @detail Includes software functions to initialize,
 configure, transmit and receive over UART
 */

/*  Include section
 *
 ***************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "UARTClass.h"

#include "variant.h"
#include "platform.h"
void *__dso_handle;

/*  Global variable section
 *
 ***************************************************/

UARTClass Serial(0);

/** @fn UARTClass::UARTClass(uint32_t _id) : id(_id)
 @brief Initialize UART Port.
 @details This function initialize the UART port.
 @warning
 @param[in]  unsigned int (_id)--This parameter sets UART Port.
 '0' = UART PORT 0, '1' = UART PORT 1, '2' = UART PORT 2
 @param[Out] No output parameter
 */
UARTClass::UARTClass(uint32_t _id) :
		id(_id) {

}

/** @fn void UARTClass::sio_setbaud(int bauds)
 @brief set baud rate for uart
 @details Calculate Divisor(Divisor = Input frequency / (Baud rate X 16) )
 for the baud rate  and configure uart register. UART frame is initialized by
 setting the data bits,parity bits and stop bits
 8 Data bits, 1 Stop bit, no Parity,Disable DR interrupt & THRE interrupt
 @warning
 @param[in]  int (bauds)--Baud rate
 @param[Out] No output parameter
 @return Void function.
 */

void UARTClass::sio_setbaud(int bauds) {
	unsigned long divisor;
	UART_REG(id, UART_REG_LCR) = 0x83;	//setting DLAB = 1 in LCR
	divisor = (F_CPU / (bauds * 16));
	UART_REG(id, UART_REG_DR) = divisor & 0xFF;	//to get LSB only AND with FF
	UART_REG(id, UART_REG_IE) = (divisor >> 0x08) & 0xFF;	//to get MSB only
	UART_REG(id, UART_REG_LCR) = 0x03;	//Clearing DLAB in LCR
	UART_REG(id, UART_REG_IE) = 0x00;
}

/** @fn void UARTClass::begin( unsigned long bauds)
 @brief Initialize UART
 @details Initialise UART with the customized setting
 @warning
 @param[in]  unsigned long (bauds)--Baud rate
 @param[Out] No output parameter
 @return Void function
 */
void UARTClass::begin(unsigned long bauds) {
	unsigned long divisor;
	divisor = (F_CPU / (bauds * 16));
	UART_REG( id, UART_REG_LCR ) = 0x83; //0x83
	UART_REG( id, UART_REG_DR) = divisor & 0xFF;	//LSB//0x28
	UART_REG( id, UART_REG_IE) = (divisor >> 0x08) & 0xFF;	//MSB//0x00
	UART_REG( id, UART_REG_LCR) = 0x03;	//set DLAB to 0
	UART_REG(id, UART_REG_IE) = 0x00;
	UART_REG( id, UART_REG_IIR_FCR) = 0x00;
	__asm__ __volatile__ ("fence");
}

/** @fn int UARTClass::sio_getchar(int c)
 @brief 1 byte character reception
 @details Receives 1 character through uart
 @warning
 @param[in]  int (c) --The variable to hold the read character
 @param[Out] No output parameter
 @return c -- read character
 */
int UARTClass::sio_getchar(int c) //c-The variable to hold the read character
		{
	while ((UART_REG(id, UART_REG_LSR) & UART_LSR_DR) != UART_LSR_DR)
		;  //waiting for Data Ready
	c = UART_REG(id, UART_REG_DR);
	return c;
}

/** @fn int UARTClass::sio_putchar(char c)
 @brief 1 byte character transmission
 @details Transmit 1 character through uart.Proceeds only when transmitter is idle
 @warning
 @param[in]  char (c) --The variable to write character
 @param[Out] No output parameter
 @return 0
 */
int UARTClass::sio_putchar(char c) {
	while ((UART_REG(id, UART_REG_LSR) & UART_LSR_THRE) != UART_LSR_THRE)
		;	//waiting for THRE to be empty
	UART_REG(id,UART_REG_DR) = c;
	__asm__ __volatile__ ("fence");
	return 0;
}

/** @fn int UARTClass::available(void)
 @brief to check availability of data
 @details Get the number of bytes (characters) available for reading from the serial port.
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return The number of bytes available to read.
 */

int UARTClass::available(void) {
	if ((UART_REG(id,UART_REG_LSR) & UART_LSR_DR))
		return 1;
	else
		return 0;
}

/** @fn int UARTClass::availableForWrite(void)
 @brief number of bytes available for writing
 @details Get the number of bytes (characters) available for writing in the
 serial buffer without blocking the write operation.
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return void function
 */
/*
 int UARTClass::availableForWrite(void) {
 int busy;
 if (UART_REG(UART_LSR_TEMT) != 0)
 ;
 return (UART_REG(UART_REG_DR));
 }
 */

/** @fn int UARTClass::read(void)
 @brief read data from uart
 @details 1 byte character reception
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return int function
 */
int UARTClass::read(void) {

	if ((UART_REG(id, UART_REG_LSR) & UART_LSR_DR) != UART_LSR_DR) {
		return -1; //No data
	}

	int c = UART_REG(id, UART_REG_DR);
	return c;

}

/** @fn size_t UARTClass::write(const uint8_t uc_data)
 @brief write data
 @details
 @warning
 @param[in]  const uint8_t (uc_data)
 @param[Out] No output parameter
 @return 1
 */
size_t UARTClass::write(const uint8_t uc_data) {
	sio_putchar(uc_data);
	return (1);
}

void UARTClass::enableInterrupt(uint8_t tx_intr, uint8_t rx_intr) {

	UART_REG(id, UART_REG_IE) = ((tx_intr << 1) | (rx_intr));
}

void UARTClass::disableInterrupt(void) {

	UART_REG(id, UART_REG_IIR_FCR);
}

void UARTClass::end(void){}
int UARTClass::peek(void){
	return 1;
}