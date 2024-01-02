#include "Arduino.h"
#include "EEPROM.h"
#include "at25sf161.h"

EEPROMClass EEPROM;

EEPROMClass::EEPROMClass(void) {
    // starting address 0x00, first 256 Kilo-bytes are reserved as program memory
    // 256 KB is equal to 262144 Bytes in hexadecimal 0x40000
    _address = 0x40000;
}

/**
 * @fn void EEPROMClass::begin(void)
 * @brief To initialize eeprom.
 * @details
 * @param[in] No input parameter
 * @param[Out] No output parameter
 */
void EEPROMClass::begin(void) {
    uint32_t address = _address;
    SPI_EEPROM.at25sf161Begin();
	for (int i = 0; i < 64; i++) { //earse 256K
		SPI_EEPROM.at25sf161blockErase4k(address);
		address += (4 * 1024);
	}
    return;
}

/**
 * @fn uint8_t EEPROMClass::read(uint32_t address)
 * @brief To read single byte data from eeprom.
 * @details
 * @param[in] unsigned int address : :  the location to read from, starting from 0 (int)
 * @param[Out] No output parameter
 * @return the value stored in that location (byte)
 */
uint8_t EEPROMClass::read(uint32_t address) {
    uint8_t data;
    SPI_EEPROM.at25sf161ReadEeprom(&data, 1, (_address + address));
    return data;
}

/**
 * @fn void EEPROMClass::read(uint8_t *readBuf, uint32_t length, uint32_t eepromAddress)
 * @brief To read multiple bytes at a time from eeprom.
 * @details
 * @param[in] uint32_t length : the length of data to be read in bytes(max 512 bytes) 
 *            uint32_t eepromAddress : Starting address (0 to onward)
 * @param[Out] uint8_t *readBuf
 * @return 
 */
void EEPROMClass::read(uint8_t *readBuf, uint32_t length, uint32_t eepromAddress) {
    if(length > 512) {
        Serial.println("Error: Maximum length for reading from EEPROM is 512 Bytes at a time!");
        return;
    }
    SPI_EEPROM.at25sf161ReadEeprom(readBuf, length, (_address + eepromAddress));
    return;
}

/**
 * @fn void EEPROMClass::write(uint32_t address, uint8_t val)
 * @brief To write a data byte to eeprom.
 * @details
 * @param[in] uint32_t address : the location to write to, starting from 0 (int)
 *            uint8_t val : the value to write, from 0 to 255 (byte)
 * @param[Out] No output parameter
 */
void EEPROMClass::write(uint32_t address, uint8_t val) {
    SPI_EEPROM.at25sf161WriteEeprom(&val, 1, (_address + address));
    return;
}

/**
 * @fn void EEPROMClass::write(uint8_t *writeBuf, uint32_t length, uint32_t eepromAddress)
 * @brief To write multiple bytes at a time
 * @details
 * @param[in] uint32_t length : the length of data to be write (in bytes) (max 256 bytes) 
 *            uint32_t eepromAddress : Starting address (0 to onward)
 * @param[Out] uint8_t *writeBuf
 * @return 
 */
void EEPROMClass::write(uint8_t *writeBuf, uint32_t length, uint32_t eepromAddress) {
    if(length > PAGE_SIZE) {
        Serial.println("Error: Maximum length for writing on EEPROM is 256 Bytes at a time!");
        return;
    }
    SPI_EEPROM.at25sf161Begin();
    SPI_EEPROM.at25sf161WriteEeprom(writeBuf, length, (_address + eepromAddress));
    return;
}

/**
 * @fn void EEPROMClass::update(uint32_t address, uint8_t val)
 * @brief To update a particular byte to eeprom.
 * @details Write a byte to the EEPROM. 
 * The value is written only if differs from the one already saved at the same address.
 * @param[in] uint32_t address : the location to write to, starting from 0 (int)
 *            uint8_t val : the value to write, from 0 to 255 (byte)
 * @param[Out] No output parameter
 * @return 
 */
void EEPROMClass::update(uint32_t address, uint8_t val) {
    uint8_t currentValue;
    SPI_EEPROM.at25sf161ReadEeprom(&currentValue, 1, (_address + address));

    if(currentValue == val)
        return;
        
    SPI_EEPROM.at25sf161WriteEeprom(&val, 1, (_address + address));
    return;
}

/**
 * @fn uint32_t EEPROMClass::length(void)
 * @brief This function returns an unsigned int containing the number of cells in the EEPROM.
 * @details
 * @param[in] 
 * @param[Out] 
 * @return Number of cells in the EEPROM as an unsigned int.
 */
uint32_t EEPROMClass::length(void) {
    return PAGE_SIZE;
}

/**
 * @fn void EEPROMClass::clear(uint8_t value) 
 * @brief This function erase the EEPROM.
 * @details
 * @param[in] uint8_t value: if value = 0, then it will clear first 4KB space
 *                           if value = 1, then it will erase the complete flash
 * @param[Out] 
 * @return 
 */
void EEPROMClass::clear(uint8_t value) {
    SPI_EEPROM.at25sf161Begin();
    switch(value)
    {
        case 0:
            SPI_EEPROM.at25sf161blockErase4k(_address);
            break;
        
        case 1:
            SPI_EEPROM.at25sf161ChipErase();
            break;

        default:
            SPI_EEPROM.at25sf161blockErase4k(_address);
            break;
        }
}

// void EEPROMClass::clear(uint32_t address, uint32_t length) {
//     uint32_t currentLength = length;
//     SPI_EEPROM.at25sf161Begin();
//     if(length >= LENGTH_4K) {
//         for( ; currentLength >= LENGTH_4K; address += LENGTH_4K) {
//             SPI_EEPROM.at25sf161blockErase4k(address + _address);
//             currentLength -= LENGTH_4K;
//         }
//     } 
//     if(length >= PAGE_SIZE) {
//         uint8_t buffer[PAGE_SIZE];
//         for(int i=0; i<PAGE_SIZE; i++) {
//             buffer[i] = 0xFF;
//         }
//         for(; currentLength >= PAGE_SIZE; address += PAGE_SIZE) {
//             write(buffer, currentLength, address);
//             currentLength -= PAGE_SIZE;
//         }
//     }
//     if(length <= PAGE_SIZE) {
//         for(uint32_t i=0; i < currentLength; i++) {
//             write(address, 0xFF);
//         }
//     }
// }

/**
 * @fn void EEPROMClass::clear(void) 
 * @brief This function erase the first 4KB of EEPROM.
 * @details
 * @param[in] 
 * @param[Out] 
 * @return 
 */
void EEPROMClass::clear(void) {
    clear(0);
}
