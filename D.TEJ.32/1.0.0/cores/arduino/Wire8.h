#ifndef TwoWire_h
#define TwoWire_h

/**
 @file Wire.h
 @brief header file for I2C driver
 @detail
 */
/***************************************************
 * Module name: Wire.h
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

#include <inttypes.h>
#include "Arduino.h"

#define BUFFER_LENGTH 16	//Fifo depth

// WIRE_HAS_END means Wire has end()
#define WIRE_HAS_END 1

// IICs
#define IIC0                        0
#define IIC1                        1

#define TRUE 1
#define FALSE 0

// Register offsets
#define IIC_REG_CR               0x00             // Control Register
#define IIC_REG_SR0              0x01             // Status Register 0
#define IIC_REG_SR1              0x02             // Status Register 1
#define IIC_REG_IER              0x03             // Interrupt enable register
#define IIC_REG_TxFF			 0x04			  //Transmit data FIFO
#define IIC_REG_RxFF			 0x05			  //Receive data FIFO
#define IIC_REG_CHL				 0x06			  //Clock period half register low
#define IIC_REG_CHH				 0x07			  //Clock period half register high
#define IIC_REG_CHHL			 0x08			  //Clock period half half register low
#define IIC_REG_CHHH			 0x09			  //Clock period half half register high
#define IIC_REG_TxCLR			 0x0A			  //TX fifo clear register


#define I2C_CLK	 100000

#define IIC_READ 	1
#define IIC_WRITE 	0

#define I2C_EEPROM_ADDR_WR	(0xA2)
#define I2C_EEPROM_ADDR_RD	(0xA3)

// Fields R/W
#define IIC_CR_RDLEN(x)             (((x) & 0x1F) << 2)      // Read length
#define IIC_CR_STOP(x)              (((x) & 0x1) << 1)      //  Stop bit
#define IIC_CR_START(x)             (((x) & 0x1))          // Start bit

#define IIC_IER_RxIEN(x)            (((x) & 0x1) << 2)     //  Receive interrupt enable
#define IIC_IER_TxIEN(x)            (((x) & 0x1) << 1)     //  Transmit interrupt enable
#define IIC_IER_GIE(x)              (((x) & 0x1))          // Global interrupt enable

#define IIC_TxFF_TxD(x)             (((x) & 0xFF))      // Tx data fifo

/*fields Read only*/
#define IIC_SR0_RxC			    (1 << 7)	//Receive complete flag
#define IIC_SR0_RxFFE			(1 << 6)    //Receive fifo empty
#define IIC_SR0_RxFFF			(1 << 5)    //Receive fifo full
#define IIC_SR0_TxC				(1 << 4)    //Transmit complete-0x10
#define IIC_SR0_TxFFE			(1 << 3)    //Transmit fifo empty-0x08
#define IIC_SR0_TxFFF			(1 << 2)    //Transmit fifo full
#define IIC_SR0_STPS			(1 << 1)    //Stop condition sent on the bus
#define IIC_SR0_STAS			 0x1    	//Start condition sent on the bus -0x01

#define IIC_SR1_RxINTR			(1 << 2)     //Receive interrupt
#define IIC_SR1_TxINTR			(1 << 1)     //Transmit interrupt
#define IIC_SR1_NACK			0x1	    	 //Negative acknowledge received

#define IIC_RxFF_RxD			 (0xFF)    	//Rx data fifo

#define  SUCCESS		(0)
#define  DATA_LONG		(1)
#define  NACK_ADDR		(2)
#define  NACK_DATA		(3)
#define  OTHER_ERROR	(4)
#define  TIME_OUT		(5)
/*********************************************************************************************/

extern "C" void i2c0_isr(void);

class TwoWire8: public Stream {

	static uint8_t rxBuffer[];
	static uint8_t rxBufferIndex;
	static uint8_t rxBufferLength;

	static uint8_t slaveAddress;
	static uint8_t txBuffer[];
	static uint8_t txBufferIndex;
	static uint8_t txBufferLength;

	static uint8_t transmitting;
	static uint8_t FIFO_length;
	static uint8_t DataRead;
	static void (*user_onRequest)(void);
	static void (*user_onReceive)(int);
	static void onRequestService(void);
	static void onReceiveService(uint8_t*, int);

public:
	TwoWire8(uint8_t _id);
	void begin();
	void begin(uint8_t);
	void begin(int);
	void end();
	void setClock(uint32_t);
	void setWireTimeout(uint32_t timeout = 25000, bool reset_with_timeout =
			false);
	bool getWireTimeoutFlag(void);
	void clearWireTimeoutFlag(void);
	void beginTransmission(uint8_t);
	void beginTransmission(int);
	uint8_t endTransmission(void);
	uint8_t endTransmission(uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
	uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
	uint8_t requestFrom(int, int);
	uint8_t requestFrom(int, int, int);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t*, size_t);
	virtual int available(void);
	virtual int read(void);
	//virtual int peek(void);
	virtual void flush(void);
	void onReceive(void (*)(int));
	void onRequest(void (*)(void));

	inline size_t write(unsigned long n) {
		return write((uint8_t) n);
	}
	inline size_t write(long n) {
		return write((uint8_t) n);
	}
	inline size_t write(unsigned int n) {
		return write((uint8_t) n);
	}
	inline size_t write(int n) {
		return write((uint8_t) n);
	}
	using Print::write;
private:
	volatile uint8_t id;

};

extern TwoWire8 Wire8;

#endif
