/***************************************************************************
 * Project                               :  MDP
 * Name of the file                      :  SPI.cpp
 * Brief Description of file             :  Driver to control the eeprom device.

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
 @file eeprom.cpp
 @brief Contains routines for different eeprom funtions
 @detail
 */

/*  Include section
 *
 ***************************************************/

#include "at25sf161.h"

/**
 * @fn unsigned char eeprom_read_byte(unsigned int eepromAddress)
 * @brief To read at25sf161 eeprom data.
 * @details
 * @param[in] unsigned int eepromAddress
 * @param[Out] No output parameter
 * @return read_data
 */
unsigned char eeprom_read_byte(unsigned int eepromAddress) {

	unsigned char read_data;

	SPI_EEPROM.at25sf161ReadEeprom(&read_data, 1, (0x40000 + eepromAddress));

	return read_data;

}

/**
 * @fn void void eeprom_write_byte(unsigned int eepromAddress, unsigned char wr_data)
 * @brief To write a data byte to at25sf161 eeprom.
 * @details
 * @param[in] unsigned int eepromAddress, unsigned char wr_data
 * @param[Out] No output parameter
 */
//void eeprom_write_byte(unsigned int eepromAddress, unsigned char wr_data) {
void eeprom_write_byte(unsigned int eepromAddress, unsigned char wr_data) {

	SPI_EEPROM.at25sf161WriteEeprom(&wr_data, 1, (0x40000 + eepromAddress));

	return;

}

/**
 * @fn void eeprom_init(void)
 * @brief To initialize at25sf161 eeprom.
 * @details
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void eeprom_init(void) {

	int eeprom_addr = 0x40000;

	SPI_EEPROM.at25sf161Begin();

	for (int i = 0; i < 64; i++) { //earse 256K
		SPI_EEPROM.at25sf161blockErase4k(eeprom_addr);
		eeprom_addr += (4 * 1024);
	}

	return;
}

