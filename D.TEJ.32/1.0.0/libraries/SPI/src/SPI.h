#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

/**
 @file SPI.h
 @brief header file for SPI driver
 @detail 
 */

/***************************************************
 * Module name: SPI.h
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
 * SPI registers and function declarations
 *
 ***************************************************/

#include "variant.h"
#include <stdio.h>
#include "platform.h"


// SPI Ports
#define SPI0       (*(SPIClass *) SPI0_BASE_ADDR)                
#define SPI1       (*(SPIClass *) SPI1_BASE_ADDR)          
#define SPI2       (*(SPIClass *) SPI2_BASE_ADDR)     
#define SPI3 	   (*(SPIClass *) SPI3_BASE_ADDR) 

// SPI Modes
#define SPI_MODE0 					0x00
#define SPI_MODE1 					0x01
#define SPI_MODE2 					0x02
#define SPI_MODE3 					0x03

// Register Fields
#define SPIM_CR_DBITS(x)            (((x) & 0xf) << 9)      // Bits per transfer
#define SPIM_CR_CSAAT               (0x1 << 8)              // Chip Select Active After Transfer
#define SPIM_CR_SPTIE(x)            (((x) & 0x1) << 7)      // SPI Transmit Interrupt Enable
#define SPIM_CR_SPRIE(x)            (((x) & 0x1) << 6)      // SPI Receive Interrupt Enable      

#define SPIM_CLK_CONFI_MODE(x)      (((x) & 0x3) << 4)      // SPI Clock configuration Modes
#define SPIM_SCK_MODE               (0x3 << 4)

#define SPIM_CR_LSBMSB(x)           (((x) & 0x1) << 3)      // This bit selects LSB/MSB first data transfer format.
#define SPIM_CR_PS(x)               (((x) & 0x1) << 2)      // Fixed peripheral-0  Variable peripheral-1
#define SPIM_CR_PCS(x)              ((x) & 0x3)             // Peripheral Chip select

#define SPIM_SR_TXE                 (1 << 7)                // Transmit data register empty
#define SPIM_SR_RXC                 (1 << 6)                // SPI Receive Complete
#define SPIM_SR_OVERR               (1 << 5)                // Overrun Error
#define SPIM_SR_TXB                 (1 << 4)                // Transmitter busy
#define SPIM_SR_TXINT               (1 << 3)                // Transmit hold register empty interrupt
#define SPIM_SR_RXINT               (1 << 2)                // Receive complete interrupt

#define SPIM_BRR_VALUE(x)           (((x) & 0xf) << 4)      // Baud rate register value

#define SPIM_TDR_CS0(x)             (((x) & 0x1) << 16)     // Slave Select bits in variable peripheral mode
#define SPIM_TDR_CS1(x)             (((x) & 0x1) << 17)
#define SPI_TDR_CSMODE(x)           (((x) & 0x3) << 16)

#define SPIM_RDR_CS0(x)             (((x) & 0x1) << 16)
#define SPIM_RDR_CS1(x)             (((x) & 0x1) << 17)
#define SPI_RDR_CSMODE(x)           (((x) & 0x3) << 16)

// Data transfer to slave
#define SPIM_TDR_DATA(x)            ((x) & 0xff)

// Data receive from slave
#define SPIM_RDR_DATA(x)            ((x) & 0xff)

// Status register
#define SPI_TXFIFO_FULL             (1 << 7)   
#define SPI_TXFIFO_EMPTY            (1 << 7)

#define SPI_RXNEW_DATA              (1 << 6)
#define SPI_NOTRXNEW_DATA           (1 << 6)

// Values
#define SPI_MSB_FIRST               0
#define SPI_LSB_FIRST               1

#define SPI_INTERRUPT_DISABLE       0
#define SPI_INTERRUPT_ENABLE        1

#define FIXED_PERIPHERAL            0
#define VARIABLE_PERIPHERAL         1

#define SPI_CSMODE_AUTO             0
#define SPI_CSMODE_HOLD             2
#define SPI_CSMODE_OFF              3

#define SPI_DIR_RX                  0
#define SPI_DIR_TX                  1

#define SPI_PROTO_S                 0
#define SPI_PROTO_D                 1
#define SPI_PROTO_Q                 2

// Data Bits Per Transfer
#define DBITS_8                     0
#define DBITS_9                     1
#define DBITS_10                    2
#define DBITS_11                    3
#define DBITS_12                    4
#define DBITS_13                    5
#define DBITS_14                    6
#define DBITS_15                    7
#define DBITS_16                    0x8

// Baudrate
#define SPI_BAUD_CFD_4        		0
#define SPI_BAUD_CFD_8        		1 
#define SPI_BAUD_CFD_16        		2 
#define SPI_BAUD_CFD_32        		3
#define SPI_BAUD_CFD_64        		4
#define SPI_BAUD_CFD_128        	5 
#define SPI_BAUD_CFD_256       		6
#define SPI_BAUD_CFD_512        	7 
#define SPI_BAUD_CFD_1024        	8 
#define SPI_BAUD_CFD_2048        	9

#define SPI_CLOCK_DIV4 				0
#define SPI_CLOCK_DIV8        		1 
#define SPI_CLOCK_DIV16        		2 
#define SPI_CLOCK_DIV32        		3
#define SPI_CLOCK_DIV64        		4
#define SPI_CLOCK_DIV128        	5 
#define SPI_CLOCK_DIV256       		6
#define SPI_CLOCK_DIV512        	7 
#define SPI_CLOCK_DIV1024        	8 
#define SPI_CLOCK_DIV2048        	9


enum SPITransferMode {
	SPI_CONTINUE,
	SPI_LAST
};

class SPISettings {
public:
	SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
		if (__builtin_constant_p(clock)) {
			init_AlwaysInline(clock, bitOrder, dataMode);
		} else {
			init_MightInline(clock, bitOrder, dataMode);
		}
	}
	SPISettings() { init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0); }
private:
	void init_MightInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
		init_AlwaysInline(clock, bitOrder, dataMode);
	}
	void init_AlwaysInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) __attribute__((__always_inline__)) {
		if (clock >= F_CPU / 4) {
        sckdiv = 0;
      } else if (clock >= F_CPU / 8) {
        sckdiv = 1;
      } else if (clock >= F_CPU / 16) {
        sckdiv = 2;
      } else if (clock >= F_CPU / 32) {
        sckdiv = 3;
      } else if (clock >= F_CPU / 64) {
        sckdiv = 4;
      } else if (clock >= F_CPU / 128) {
        sckdiv = 5;
      } else if (clock >= F_CPU / 256) {
        sckdiv = 6;
      } else if (clock >= F_CPU / 512) {
        sckdiv = 7;
      } else if (clock >= F_CPU / 1024) {
        sckdiv = 8;
      } else if (clock >= F_CPU / 2048) {
        sckdiv = 9;
      } else {
        sckdiv = 0;
	  }
                sckmode = dataMode;
                csid = 0;
                csdef = 0xFFFF;
                csmode = SPI_CSMODE_AUTO;
                border = bitOrder;
	}
        uint8_t   sckmode; // mode bits to set polarity and phase of spi clock
        uint8_t   sckdiv;  // spi clock frequency = F_CPU/2*(sckdiv-1), maximum is half of F_CPU 
        uint8_t   csid;    // csid = index of chip select aka slave select pin, valid values are 0,1,2,3
        uint16_t  csdef;   // inactive state of chip select pins (high or low)
        uint8_t   csmode;  // chip select mode (0 = auto, 1 = CS toggles with frame)
        BitOrder  border;  // bit ordering : 0 = LSB first, 1 = MSB first (common case)

	friend class SPIClass;
};


class SPIClass {
  public:
	SPIClass(uint32_t _id);

	// Transfer Function
	byte transfer(uint8_t _data, SPITransferMode _mode = SPI_LAST);
	void transfer(uint8_t *_buf, size_t _count, SPITransferMode _mode = SPI_LAST);
	uint16_t transfer16(uint16_t _data, SPITransferMode _mode = SPI_LAST);

	// Transaction Functions
	void usingInterrupt(uint8_t interruptNumber);
	void beginTransaction(SPISettings settings);
	void endTransaction(void);
	void spiSlaveDeselect(void);
 	void spiSlaveSelect(void);

	// SPI Initialization Functions
	void begin(void);
	uint32_t begin(uint32_t _bits, uint8_t _mode, uint8_t _msblsb);

	// Attach/Detach pin to/from SPI controller
	void end(void);

	// These methods sets the same parameters, but globally.
	void setBitOrder(BitOrder _order);
	void setDataMode(uint8_t _mode);
	void setClockDivider(uint8_t _div);
	uint16_t SPI_Receive(void);
	void SPI_Transmit(u_int8_t bData);

  private:
	volatile uint32_t id;
	// These are for specific pins.
	BitOrder bitOrder[4+1];
	uint32_t divider[4+1];
	uint32_t mode[4+1];
	
	uint8_t interruptMode;    // 0=none, 1-15=mask, 16=global
	uint8_t interruptSave;    // temp storage, to restore state
	uint32_t interruptMask[4];
};

extern SPIClass SPI;

#endif // _SPI_H_INCLUDED

