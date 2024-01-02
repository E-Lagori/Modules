#ifndef _EEPROM_H_
#define _EEPROM_H_


#include <inttypes.h>
#include <eeprom.h>

#define PAGE_SIZE 256
#define LENGTH_4K 262144

struct EEPROMClass {
	public:
		EEPROMClass(void);

		void begin(void);

		uint8_t read(uint32_t address);
		void write(uint32_t address, uint8_t val);
		void update(uint32_t address, uint8_t val);
		uint32_t length(void);
		void write(uint8_t *writeBuf, uint32_t length, uint32_t eepromAddress);
		void read(uint8_t *readBuf, uint32_t length, uint32_t eepromAddress);
		void clear(void);
		void clear(uint8_t value);
		void clear(uint32_t address, uint32_t length); 
		
		template< typename T > T &get( int idx, T &t ){
            int e = idx;
            uint8_t *ptr = (uint8_t*) &t;
            for( int count = sizeof(T) ; count ; --count, ++e )  *ptr++ = read(e);
            return t;
        }
    
        template< typename T > const T &put( int idx, const T &t ){
            int e = idx;
            const uint8_t *ptr = (const uint8_t*) &t;
            for( int count = sizeof(T) ; count ; --count, ++e )  update(e, *ptr++);
            return t;
        }

	protected:
		uint32_t _address;
};

extern EEPROMClass EEPROM;

#endif // _EEPROM_H_

