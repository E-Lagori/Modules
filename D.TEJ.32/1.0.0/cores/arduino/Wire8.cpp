/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  Wire.cpp
 * Brief Description of file             :  Driver to control the i2c device.
 * Name of Author                        :  Mydhily M R
 * Email ID                              :  mydhily37@gmail.com

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
 @file Wire.cpp
 @brief Contains routines for different I2C functions
 @detail
 */

/*  Include section
 *
 ***************************************************/
extern "C" {
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "utility/twi.h"
}

#include "Wire8.h"

/*  Global variable section
 *
 ***************************************************/
uint8_t TwoWire8::rxBuffer[BUFFER_LENGTH];
uint8_t TwoWire8::rxBufferIndex = 0;
uint8_t TwoWire8::rxBufferLength = 0;

uint8_t TwoWire8::slaveAddress = 0;
uint8_t TwoWire8::txBuffer[BUFFER_LENGTH];
uint8_t TwoWire8::txBufferIndex = 0;
uint8_t TwoWire8::txBufferLength = 0;

uint8_t TwoWire8::transmitting = 0;
// uint8_t DataRead;

/** @fn TwoWire8::TwoWire8(uint8_t _id): id(_id)
 @brief Initialize i2c Port.
 @details This function initialize the I2C port.
 @warning
 @param[in]  unsigned int _id: This parameter sets I2C Port.
 '0' = I2C PORT 0, '1' = I2C PORT 1
 @param[Out] No output parameter
 */

TwoWire8::TwoWire8(uint8_t _id) :
		id(_id) {

}

/**
 @fn void TwoWire8::begin(void)
 @brief I2C Initialization
 @details Initializes I2C Clock period registers
 @param[in]  No input parameter
 @param[Out] No output parameter
 @return Void function.
 */

void TwoWire8::begin(void) {
	rxBufferIndex = 0;
	rxBufferLength = 0;
	txBufferIndex = 0;
	txBufferLength = 0;

	IIC_REG(id, IIC_REG_TxCLR) = 0xFF; //clear TxFIFO register
	__asm__ __volatile__ ("fence");
	unsigned short CH = F_CPU / (2 * I2C_CLK); //i2c clock=100000
	IIC_REG(id, IIC_REG_CHL) = ((unsigned char) (CH & 0x0FF)); //set timing registers CHL,CHH,CHHL,CHHH
	IIC_REG(id, IIC_REG_CHH) = (unsigned char) ((CH >> 8) & 0xFF);
	unsigned short CHH = F_CPU / (4 * I2C_CLK);
	IIC_REG(id, IIC_REG_CHHL) = ((unsigned char) (CHH & 0xFF));
	IIC_REG(id, IIC_REG_CHHH) = (unsigned char) ((CHH >> 8) & 0xFF);
	__asm__ __volatile__ ("fence");

}
void TwoWire8::begin(uint8_t address) {
	begin();
}
void TwoWire8::begin(int address) {
	begin((uint8_t) address);
}
/**
 @fn void TwoWire8::setClock(uint32_t clock)
 @brief Configures I2C
 @details Configures I2C Clock period registers
 @param[in] (uint32_t clock)-- I2C clock frequency to be used
 @param[Out] No output parameters.
 @return nil
 */

void TwoWire8::setClock(uint32_t clock) {
	unsigned short CH = F_CPU / (2 * clock); //i2c clock=100000
	IIC_REG(id, IIC_REG_CHL) = ((unsigned char) (CH & 0x0FF)); //set timing registers CHL,CHH,CHHL,CHHH
	IIC_REG(id, IIC_REG_CHH) = (unsigned char) ((CH >> 8) & 0xFF);
	unsigned short CHH = F_CPU / (4 * clock);
	IIC_REG(id, IIC_REG_CHHL) = ((unsigned char) (CHH & 0xFF));
	IIC_REG(id, IIC_REG_CHHH) = (unsigned char) ((CHH >> 8) & 0xFF);
	__asm__ __volatile__ ("fence");
}

uint8_t TwoWire8::requestFrom(uint8_t address, uint8_t quantity,
		uint32_t iaddress, uint8_t isize, uint8_t sendStop) { //address = slave adress,quantity=num ofbytes
	return requestFrom((uint8_t) address, (uint8_t) quantity,
			(uint8_t) sendStop);
}
/**
 @fn uint8_t TwoWire8::requestFrom(uint8_t address, uint8_t quantity,uint8_t sendStop)
 @brief to request bytes from a peripheral device.
 @details allows one master device to send multiple requests while in control. The default value is true.
 @param[in] (uint8_t address)--7-bit slave address of the device to request bytes from.
 @param[in] (uint8_t quantity)--the number of bytes to request.
 @param[in] (uint8_t sendStop)--true or false.
 @param[Out] No output parameters.
 @return rxBufferLength if true and return 0 when NACK is received
 */

uint8_t TwoWire8::requestFrom(uint8_t address, uint8_t quantity,
		uint8_t sendStop) {
	rxBufferLength = quantity;
	IIC_REG(id, IIC_REG_CR ) = ((quantity << 2) | 0x01); //Set Start bit for read,set read length
	__asm__ __volatile__ ("fence");
	slaveAddress = ((address << 1) | IIC_READ);	//shift address to indicate R/W
	while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxFFF) == (IIC_SR0_TxFFF))
		; //TxFF full or not
	IIC_REG(id, IIC_REG_TxFF) = slaveAddress; //write slave address to Txff
	__asm__ __volatile__ ("fence");

	while (((IIC_REG(id, IIC_REG_SR0)) & (IIC_SR0_TxC)) != (IIC_SR0_TxC))
		; //Transmission is completed or not
	if (((IIC_REG(id, IIC_REG_SR1)) & (IIC_SR1_NACK)) == (IIC_SR1_NACK)) { //checks NACK
		while (((IIC_REG(id, IIC_REG_SR0)) & (IIC_SR0_STPS)) != (IIC_SR0_STPS))
			; //wait for stop bit to be set
		return 0;
	}
	while (((IIC_REG(id, IIC_REG_SR0)) & (IIC_SR0_RxC)) != (IIC_SR0_RxC))
		; //Rxc or not
	if (rxBufferLength > BUFFER_LENGTH) {
		Serial.print("data too long to fit in transmit buffer for read. \n\r");
		return 0;	//data too long to fit in transmit buffer.
	}
	for (int i = 0; i < rxBufferLength; i++) {
		while (((IIC_REG(id, IIC_REG_SR0)) & (IIC_SR0_RxFFE)) == (IIC_SR0_RxFFE))
			; //check RxFF empty
		rxBuffer[i] = IIC_REG(id, IIC_REG_RxFF); //read data from Rx register
	}
	while (((IIC_REG(id, IIC_REG_SR0)) & (IIC_SR0_STPS)) != IIC_SR0_STPS)
		; //wait for stop bit to be set
	rxBufferIndex = 0;

	if (sendStop) {
		IIC_REG(id,IIC_REG_CR) = 0x02; 	//set stop bit
		__asm__ __volatile__ ("fence");
		while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_STPS) != (IIC_SR0_STPS))
			; //check stop sequence initiated
	}
	return rxBufferLength;
}

uint8_t TwoWire8::requestFrom(uint8_t address, uint8_t quantity) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire8::requestFrom(int address, int quantity) {
	return requestFrom((uint8_t) address, (uint8_t) quantity, (uint8_t) true);
}

uint8_t TwoWire8::requestFrom(int address, int quantity, int sendStop) {

	return requestFrom((uint8_t) address, (uint8_t) quantity,
			(uint8_t) sendStop);
}
/**
 @fn void TwoWire8::beginTransmission(uint8_t address)
 @brief begins transmission
 @details begins a transmission to the I2C peripheral device with the given address
 @param[in] (uint8_t address)--the 7-bit address of the device to transmit to.
 @param[Out] No output parameters.
 @return nil
 */
void TwoWire8::beginTransmission(uint8_t address) {

	// indicate that we are transmitting
	transmitting = 1;
	// set address of targeted slave
	slaveAddress = (address << 1) | IIC_WRITE;	//shift address to indicate R/W
	// reset tx buffer iterator vars
	txBufferIndex = 0;
	txBufferLength = 0;
	IIC_REG(id,IIC_REG_TxCLR) = 0xFF;		//clear TxFifo
	while ((((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxFFE) != (IIC_SR0_TxFFE))
			|| (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxC) != (IIC_SR0_TxC)))
		;		//checks for transmission complete and TxFifo empty
	IIC_REG(id,IIC_REG_CR) = 0x01;		//Set Start bit for write
	__asm__ __volatile__ ("fence");
	while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_STAS) != (IIC_SR0_STAS))
		;		//check start sequence initiated

}

void TwoWire8::beginTransmission(int address) {
	beginTransmission((uint8_t) address);
}
/**
 @fn uint8_t TwoWire8::endTransmission(uint8_t sendStop)
 @brief  ends a transmission to a peripheral device
 @details This function ends a transmission to a peripheral device that was
 begun by beginTransmission() and transmits the bytes that were queued by write()
 @param[in] (uint8_t sendStop)--true or false. True will send a stop message, releasing
 the bus after transmission. False will send a restart, keeping the connection active.
 @param[Out] No output parameters.
 @return
 0: success.
 1: data too long to fit in transmit buffer.
 2: received NACK on transmit of address.
 3: received NACK on transmit of data.
 4: other error.
 5: timeout
 */

uint8_t TwoWire8::endTransmission(uint8_t sendStop) {
	while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxFFF) == ( IIC_SR0_TxFFF))
		; //TxFF full or not
	IIC_REG(id,IIC_REG_TxFF) = slaveAddress; //write slave address to Txff
	// slaveAddress++;
	__asm__ __volatile__ ("fence");
	while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxC) != (IIC_SR0_TxC))
		;		//Transmission is completed or not

	if (((IIC_REG(id, IIC_REG_SR1)) & IIC_SR1_NACK) == (IIC_SR1_NACK)) { //checks NACK

		while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_STPS) != (IIC_SR0_STPS))
			;			//wait for stop bit to be set
		return 2;			//received NACK on transmit of address.
	}
	while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxFFF) == (IIC_SR0_TxFFF))
		;			//TxFF full or not
	if (txBufferLength > BUFFER_LENGTH) {
		Serial.print("data too long to fit in transmit buffer in write. \n\r");
		return 1;	//data too long to fit in transmit buffer.
	}
	for (int i = 0; i < txBufferLength; i++) {

		IIC_REG(id,IIC_REG_TxFF) = txBuffer[i];	//data of write stored in buffer in write()
		//	Serial.print(IIC_REG(IIC_REG_TxFF));

		while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxC) != (IIC_SR0_TxC))
			;			//Transmission is completed or not

		if (((IIC_REG(id, IIC_REG_SR1)) & IIC_SR1_NACK) == (IIC_SR1_NACK)) { //checks NACK
			Serial.print("NACK rxd and stop bit set in write \n\r");
			while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_STPS) != (IIC_SR0_STPS))
				; //wait for stop bit to be set
			return 3;				// received NACK on transmit of data.
		}
	}

	IIC_REG(id,IIC_REG_CR) = 0x02; //Set Stop bit;
	__asm__ __volatile__ ("fence");
	while (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_STPS) != (IIC_SR0_STPS))
		; //check stop sequence initiated

	if (sendStop == false) {
		transmitting = 1;
		// reset tx buffer iterator vars
		txBufferIndex = 0;
		txBufferLength = 0;
		IIC_REG(id,IIC_REG_TxCLR) = 0xFF;		//clear TxFifo
		while ((((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxFFE) != (IIC_SR0_TxFFE))
				|| (((IIC_REG(id, IIC_REG_SR0)) & IIC_SR0_TxC) != (IIC_SR0_TxC)))
			; //checks for transmission complete and TxFifo empty
		__asm__ __volatile__ ("fence");
	}

	txBufferIndex = 0;
	txBufferLength = 0;
	// indicate that we are done transmitting
	transmitting = 0;
	return 0;
}

uint8_t TwoWire8::endTransmission(void) {
	return endTransmission(true);
}
/**
 @fn size_t TwoWire8::write(uint8_t data)
 @brief  writes data
 @details  writes data from a peripheral device in response to a request from a controller device,
 or queues bytes for transmission from a controller to peripheral device
 @param[in] (uint8_t data)-- an array of data to send as bytes.
 @param[Out] No output parameters.
 @return 0 if data size exceeded and return 1 if txBufferLength = txBufferIndex;
 */
size_t TwoWire8::write(uint8_t data) {
	//Serial.print("write start \n\r");

	if (txBufferIndex >= BUFFER_LENGTH) {
		Serial.print(
				"error, data size exceeded call end transmission() before more write()");
		setWriteError();
		return 0;
	}
// put byte in tx buffer
	txBuffer[txBufferIndex] = data;
	++txBufferIndex;
// update amount in buffer
	txBufferLength = txBufferIndex;
	return 1;
}
/**
 @fn size_t TwoWire8::write(const uint8_t *data, size_t quantity)
 @brief  writes data
 @details  writes data from a peripheral device in response to a request from a controller device,
 or queues bytes for transmission from a controller to peripheral device
 @param[in] (uint8_t data)-- an array of data to send as bytes.
 @param[Out] No output parameters.
 @return quantity
 */
size_t TwoWire8::write(const uint8_t *data, size_t quantity) {
	//Serial.print("write start1 \n\r");
	for (size_t i = 0; i < quantity; ++i) {
		write(data[i]);
	}
	return quantity;
}
/**
 @fn int TwoWire8::available(void)
 @brief  number of bytes available
 @details returns the number of bytes available for retrieval with read()
 @param[in] No Input parameters.
 @param[Out] No output parameters
 @return rxBufferLength
 */
int TwoWire8::available(void) {
	return rxBufferLength;
}
/**
 @fn int TwoWire8::read(void)
 @brief  reads a byte
 @details reads a byte that was transmitted from a peripheral device to a controller device
 @param[in] No Input parameters.
 @param[Out] No output parameters.
 @return value
 */
int TwoWire8::read(void) {

	int value = -1;

	// get each successive byte on each call
	if (rxBufferLength > 0) {
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
		rxBufferLength--;
	}
	return value;
}

/*int TwoWire8::peek(void) {

}*/

void TwoWire8::flush(void) {
// XXX: to be implemented.
}

void TwoWire8::onRequestService(void) {

}

// sets function called on slave write
void TwoWire8::onReceive(void (*function)(int)) {
	user_onReceive = function;
}

// sets function called on slave read
void TwoWire8::onRequest(void (*function)(void)) {
	user_onRequest = function;
}

// Preinstantiate Objects //////////////////////////////////////////////////////

//TwoWire8 Wire = TwoWire8(0);
