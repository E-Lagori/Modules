 /**
 @file eeprom.h
 @brief header file for EEPROM
 @detail
 */
/***************************************************
 * Module name: eeprom.h
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
 * eeprom registers and function declarations
 *
 ***************************************************/

/*  Defines section
*
*
***************************************************/

#ifndef LIBRARIES_EEPROM_SPI_EEPROM_H_
#define LIBRARIES_EEPROM_SPI_EEPROM_H_

#define E2END 0x40000

/*  Function declaration section
*
***************************************************/

void eeprom_write_byte(unsigned int eepromAddress, unsigned char wr_data);
unsigned char eeprom_read_byte(unsigned int eepromAddress);
void eeprom_init(void);


#endif /* LIBRARIES_EEPROM_SPI_EEPROM_H_ */
