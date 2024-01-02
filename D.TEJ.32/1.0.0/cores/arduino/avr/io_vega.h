
#ifndef _IO_VEGA__
#define _IO_VEGA__

#define SPCR 						SPI_REG(1, SPIM_CR)
#define SPSR						SPI_REG(1, SPIM_SR)
#define SPDR                        SPI_REG(1, SPIM_TDR)

#define SPIE            7
#define SPE             15 // not implemented
#define DORD            3
#define MSTR            14 // not implemented
#define CPOL            3
#define CPHA            2
#define SPR1            13  // not implemented
#define SPR0            13 // not implemented

#define SPIF            3
#define WCOL            2
#define SPI2X           1 // not implemented


#endif /*_IO_VEGA__*/