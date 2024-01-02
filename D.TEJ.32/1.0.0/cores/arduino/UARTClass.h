/**
 @file UARTClass.h
 @brief header file for UART driver
 @detail
 */
/***************************************************
 * Module name: UARTClass.h
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
 * UART registers and function declarations
 *
 ***************************************************/

#ifndef _UART_CLASS_
#define _UART_CLASS_

/*  Include section
 *
 *
 ***************************************************/

#include "platform.h"
#include "HardwareSerial.h"
#include "uart.h"

/*  Function declaration section
 *
 ***************************************************/

class UARTClass: public HardwareSerial {
public:
	UARTClass(uint32_t _id);
	void begin(unsigned long dwBaudRate);
	void end(void);
	int available(void);
	//  int availableForWrite(void);
	int peek(void);
	int read(void);
	//void flush(void);
	size_t write(const uint8_t c);

	void enableInterrupt(uint8_t tx_intr, uint8_t rx_intr);
	void disableInterrupt(void);

	using Print::write; // pull in write(str) and write(buf, size) from Print
	operator bool() {
		return (true);
	}
	;
	// UART always active
private:
	volatile uint32_t id;

protected:
	// int sio_probe_rx();
	int sio_getchar(int c);
	int sio_putchar(char c);
	void sio_setbaud(int bauds);

	enum {
		SIO_RXBUFSIZE = (1 << 3), SIO_RXBUFMASK = (SIO_RXBUFSIZE - 1)
	};

	//volatile uint8_t *serbase;  // base address of SIO register for port
//    volatile uint8_t  tx_xoff;  // bit 7 set = disable Xoff/Xon flow control
	volatile uint8_t sio_rxbuf_head;
	volatile uint8_t sio_rxbuf_tail;
	char sio_rxbuf[SIO_RXBUFSIZE];
};

#if UART_INTERFACES_COUNT > 0
extern UARTClass uart;
#endif

extern UARTClass Serial;
#endif // _UART_CLASS_