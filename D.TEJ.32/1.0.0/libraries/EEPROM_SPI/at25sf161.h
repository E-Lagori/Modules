#ifndef __AT25SF161_H_
#define __AT25SF161_H_

/**
 @file at25sf161.h
 @brief header file for at25sf161 EEPROM driver
 @detail 
 */
/***************************************************
 * Module name: at25sf161.h
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


/*  Include section
 *
 ***************************************************/
#include "SPI.h"

/*  Define section
 *
 *
 ***************************************************/
#define EEPROM_BUSY                 0x01
#define READ_EEPROM                 0x03
#define DUMMY_DATA                  0x00
#define PAGE_SIZE                   256
#define WRITE_ENABLE                0x06
#define WRITE_EEPROM                0x02
#define CHIP_ERASE                  0x60
#define BLOCK_ERASE                 0x20
#define READ_STATUS_1               0x05



class SPIEeprom {
    public:
    uint8_t *at25sf161Begin();
    void at25sf161ReadEeprom(unsigned char *readBuf, unsigned long length, unsigned int eepromAddress);
    void at25sf161WriteEeprom(unsigned char *writeBuf, unsigned long length, unsigned int eepromAddress);
    int at25sf161ChipErase(void);
    int at25sf161blockErase4k(int addr);
};

/*  Function declaration section
 *
 *
 ***************************************************/
void at25sf161BusyWait(void);


extern SPIEeprom SPI_EEPROM;

#endif  /* __AT25SF161_H_ */
