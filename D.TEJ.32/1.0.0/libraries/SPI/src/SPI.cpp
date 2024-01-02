/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  SPI.cpp
 * Brief Description of file             :  Driver to control the spi device.
 * Name of Author                        :  Himanshu Kishor Diwane
 * Email ID                              :  kishor.dh@cdac.in

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
 @file SPI.cpp
 @brief Contains routines for different SPI funtions 
 @detail 
 */

/*  Include section
 *
 ***************************************************/
#include "SPI.h"


// SPIClass SPI(0);


/** @fn SPIClass::SPIClass(uint32_t _id) : id(_id)
 @brief Initialize SPI Port.
 @details This function initialise the SPI port.
 @warning
 @param[in]  unsigned int _id: This parameter sets SPI Port.
 '0' = SPI PORT 0, '1' = SPI PORT 1, '2' = SPI PORT 2, '3' = SPI PORT 3 
 @param[Out] No output parameter
 */
SPIClass::SPIClass(uint32_t _id) :
  id(_id) {
  // Empty
}


/** @fn void SPIClass::begin()
 @brief Initialize SPI controller.
 @details Initialise SPI with the default setting.
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 */
void SPIClass::begin() {

  SPI_REG(id, SPIM_CR) = SPIM_CR_DBITS(DBITS_8)  | 
  SPIM_CR_SPTIE(SPI_INTERRUPT_DISABLE) |
  SPIM_CR_SPRIE(SPI_INTERRUPT_DISABLE) |
  SPIM_CLK_CONFI_MODE(SPI_MODE0) |
  SPIM_CR_LSBMSB(SPI_MSB_FIRST) |
  SPIM_CR_PS(FIXED_PERIPHERAL) |
  (SPIM_CR_PCS(0) & ~SPIM_CR_CSAAT);
}


/** @fn void SPIClass::begin(uint32_t _bits, uint8_t _sckmode, uint8_t _bitorder)
 @brief Initialize SPI controller.
 @details Initialise SPI with the customized setting.
 @warning
 @param[in]  unsigned int _bits:  Bits per transfer
  --------------------------------------
 | 	DBITS   		|  	Bits per transfer  |
 ---------------------------------------
 |  0000	     	|	          8	         |
 |  0001	     	|	          9		       |
 |  0010        |	          10		     |
 |  0011		    |	          11	    	 |
 |	0100		    |	          12		     |
 |	0101		    |	          13    		 |
 |	0110		    |	          14    		 |
 |	0111		    |	          15		     |
 |	1000		    |	          16	       |
 ---------------------------------------
 unsigned char _sckmode: SPI Clock configuration Modes
 -------------------------------------------------
 | SPI-mode   |  CPOL(bit - 5)	|  CPHA(bit - 4) |
 -------------------------------------------------
 |   0	      |	       0		    |	      0	       |
 |   1	      |	       0		    |	      1	       |
 |   2        |	       1		    |	      0	       |
 |   3	      |	       1		    |		    1        |
 -------------------------------------------------
 unsigned char _bitorder: LSB/MSB First. This parameter sets LSB/MSB first data transfer format.
  ‘0’ = MSB first transfer format, ‘1’ = LSB first transfer format
 @param[Out] No output parameter
 */
uint32_t SPIClass::begin(uint32_t _bits, uint8_t _sckmode, uint8_t _bitorder) {

  uint32_t CR_VALUE = SPIM_CR_DBITS(_bits) | 
  SPIM_CR_SPTIE(SPI_INTERRUPT_DISABLE) |
  SPIM_CR_SPRIE(SPI_INTERRUPT_DISABLE) |
  SPIM_CLK_CONFI_MODE(_sckmode) |
  SPIM_CR_LSBMSB(_bitorder) |
  SPIM_CR_PS(FIXED_PERIPHERAL) |
  (SPIM_CR_PCS(0) & ~SPIM_CR_CSAAT);
  
  SPI_REG(id, SPIM_CR) = CR_VALUE;

  return CR_VALUE;
}


/** @fn void SPIClass::beginTransaction(SPISettings settings)
 @brief Begin SPI transaction.
 @details Initializes the SPI bus using the defined SPISettings.
 @warning
 @param[in]  SPISettings settings: the chosen settings according to SPISettings.
 @param[Out] No output parameter
 */
void SPIClass::beginTransaction(SPISettings settings) {

  SPI_REG(id, SPIM_CR) = SPI_REG(id, SPIM_CR) | SPIM_CR_LSBMSB((settings.border == LSBFIRST) ? SPI_LSB_FIRST : SPI_MSB_FIRST) |
  SPIM_CR_DBITS(DBITS_8) | SPIM_CLK_CONFI_MODE(settings.sckmode);
  
  SPI_REG(id, SPIM_BRR) = SPIM_BRR_VALUE(settings.sckdiv);
}
 

/** @fn void SPIClass::endTransaction(void)
 @brief End of SPI transaction
 @details Stop SPI transaction using the SPI bus
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 */
void SPIClass::endTransaction(void) {
  // Empty
}


/** @fn void SPIClass::setBitOrder(BitOrder _bitOrder)
 @brief Set bit order.
 @details Sets the order of the bits shifted out of and into the SPI bus, 
 either LSBFIRST (least-significant bit first) or MSBFIRST (most-significant bit first).
 @warning
 @param[in]  BitOrder _bitOrder: This parameter sety the bit order
 ‘0’ = MSB first, ‘1’ = LSB first
 @param[Out] No output parameter
 */
void SPIClass::setBitOrder(BitOrder _bitOrder) {

  SPI_REG(id, SPIM_CR) = SPI_REG(id, SPIM_CR) | SPIM_CR_LSBMSB((_bitOrder == LSBFIRST) ? SPI_LSB_FIRST : SPI_MSB_FIRST) |
  SPIM_CR_DBITS(DBITS_8);
}


/** @fn void SPIClass::setDataMode(uint8_t _mode) 
 @brief Set data mode
 @details Sets the SPI data mode. That is, clock polarity and phase. 
 @warning
 @param[in]  unsigned char _mode: SPI Clock configuration Modes
 Mode: SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3
 @param[Out] No output parameter
*/
void SPIClass::setDataMode(uint8_t _mode) {

  SPI_REG(id, SPIM_CR) = SPI_REG(id, SPIM_CR) | SPIM_CLK_CONFI_MODE(_mode);
}


/** @fn void SPIClass::setClockDivider(uint8_t _divider) 
 @brief Set the baud frequency divider value to SPI controller baud register.
 @details 
 -------------------------------
 | 	BAUD  |  	CLk freq Divider |
 -------------------------------
 |   0	  |	        4		       |
 |   1	  |	        8		       |
 |   2    |	        16	    	 |
 |   3		|	        32	    	 |
 |	 4		|	        64    		 |
 |	 5		|	        128		     |
 |	 6		|	        256		     |
 |	 7		|	        512		     |
 |	 8		|	        1024	     |
 |	 9		|	        2048	     |
 | 10-15	|	      reserved 	   |
 -------------------------------
 @warning 
 @param[in]  unsigned char _divider: The baud frequency divisor value.
 @param[Out] No output parameter 
 */
void SPIClass::setClockDivider(uint8_t _divider) {

  SPI_REG(id, SPIM_BRR) = SPIM_BRR_VALUE(_divider);  // Set the baud frequency divider value
}


/** @fn void SPIClass::end()
 @brief Disables the SPI bus 
 @details 
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 */
void SPIClass::end() {
  // Empty
}


/** @fn byte SPIClass::transfer(uint8_t _data, SPITransferMode _mode)
 @brief  Transfer single byte data.
 @details SPI transfer is based on a simultaneous send and receive: 
 It tranfers single byte data and receive it in receive data register. It returns the data receive. 
 @warning 
 @param[in] unsigned char _data: the byte to send out over the bus, 
 SPITransferMode _mode: This parameter set the mode of transfer.
 @param[Out] No output parameter. 
 */
byte SPIClass::transfer(uint8_t _data, SPITransferMode _mode) {

  while (SPI_REG(id, SPIM_SR) & SPIM_SR_TXB);	         // Check if SPI controller is busy.
  while (!(SPI_REG(id, SPIM_SR) & SPI_TXFIFO_EMPTY)) ; // Check Tx Hold empty bit is set or not. If not wait here.
  SPI_REG(id, SPIM_TDR) = _data;
  
  volatile int32_t bRxData; 

  while (!(SPI_REG(id, SPIM_SR) & SPI_RXNEW_DATA));
  bRxData = SPI_REG(id, SPIM_RDR);   // Read SPI data reg value.

  return bRxData & 0xFF;
}


/** @fn void SPI_Transmit(u_int8_t bData)
 @brief  Write data.
 @details Writes data (8 bits) to transmit data register of SPI controller.
 @warning 
 @param[in] unsigned short bData: The data to be written to tx data register.
 @param[Out] No output parameter. 
 */
void SPIClass::SPI_Transmit(u_int8_t bData) {

  while(SPI_REG(id, SPIM_SR) & SPIM_SR_TXB)
    ;// Check if SPI controller is busy.
	while(!(SPI_REG(id, SPIM_SR) & SPI_TXFIFO_EMPTY)) ;	// Check Tx Hold empty bit is set or not. If not wait here.
	SPI_REG(id, SPIM_TDR) = bData;	// Write the data (can be a command or actual data to be written to spi device)
	return;
}


/** @fn uint16_t SPI_Receive(void)
 @brief  Read data.
 @details Read data (8 bits) received in Read data register of SPI controller.
 @warning 
 @param[in] No input parameter.
 @param[Out] No output parameter. 
 */
uint16_t SPIClass::SPI_Receive(void) {
  
	uint16_t bRxData;

	while (!(SPI_REG(id, SPIM_SR) & SPI_RXNEW_DATA))
		;	//  Waiting for RX complete bit to set.
	bRxData = SPI_REG(id, SPIM_RDR);				//  Read data.
	return bRxData;
}


/** @fn void SPIClass::transfer(uint8_t *_buf, size_t _count, SPITransferMode _mode)
 @brief  Transfer multiple bytes data.
 @details SPI transfer is based on a simultaneous send and receive: 
 It tranfers Multiple bytes data and receive it in receive data register.
 @warning 
 @param[in] unsigned char *_buf: the address of data buffer to send out over the bus,
 unsigned long _count: The length of data (in bytes) 
 SPITransferMode _mode: This parameter set the mode of transfer.
 @param[Out] No output parameter. 
 */
void SPIClass::transfer(uint8_t *_buf, size_t _count, SPITransferMode _mode) { 

  while (SPI_REG(id, SPIM_SR) & SPIM_SR_TXB);	      // Check if SPI controller is busy.

  while (_count)
  {
    SPI_Transmit(*_buf);
    *_buf = SPI_Receive(); 
    _buf++;
    _count--; 
  }
}


/** @fn void SPIClass::spiSlaveSelect(void)
 @brief Set CSAAT pin high
 @details This function sets the Chip Select Active After Transfer high,
 When this bit is set, the chip select line remains active low until transfer to another peripheral is required
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 */
void SPIClass::spiSlaveSelect(void) {
  
  while (SPI_REG(id, SPIM_SR) & SPIM_SR_TXB);	       // Check if SPI controller is busy.
  SPI_REG(id, SPIM_CR) = SPI_REG(id, SPIM_CR) | SPIM_CR_CSAAT; // Setting CSAAT bit high.
}


/** @fn void SPIClass::spiSlaveDeselect(void)
 @brief Set CSAAT pin low
 @details This function sets the Chip Select Active After Transfer low,
 When this bit is reset, the chip select line remains active high.
 @warning
 @param[in]  No input parameter
 @param[Out] No output parameter
 */
void SPIClass::spiSlaveDeselect(void) {

  SPI_REG(id, SPIM_CR) = SPI_REG(id, SPIM_CR) & ~SPIM_CR_CSAAT; // Setting CSAAT bit low.
}


uint16_t SPIClass::transfer16(uint16_t _data, SPITransferMode _mode) {

  SPI_REG(id, SPIM_CR) = SPI_REG(id, SPIM_CR) | SPIM_CR_DBITS(DBITS_16);
  while (SPI_REG(id, SPIM_SR) & SPIM_SR_TXB);	         // Check if SPI controller is busy.
  while (!(SPI_REG(id, SPIM_SR) & SPI_TXFIFO_EMPTY)) ; // Check Tx Hold empty bit is set or not. If not wait here.
  SPI_REG(id, SPIM_TDR) = _data;

  volatile uint16_t bRxData; 

  while (!(SPI_REG(id, SPIM_SR) & SPI_RXNEW_DATA));
  bRxData = SPI_REG(id, SPIM_RDR);   // Read SPI data reg value.

  return bRxData;
}
