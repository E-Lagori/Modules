// API compatibility
#include "variant.h"

#define PINS_COUNT    (40u)

#define PIN_LED_22  (22)
#define PIN_LED     PIN_LED_22
#define LED_BUILTIN PIN_LED

//NINA
#if defined(VEGA_ARIES_IOT)
    #define NINA_GPIO0      (17) //connect 27-GPIO0 (Boot pin) of WiFiNINA to GPIO17 of Aries IOT
    #define NINA_RESETN     (20)  // For Reseting NiNA Module 
    #define NINA_ACK        (16)   // Acknowledge 
    #define NINA_CTS        NINA_ACK
    #define NINA_RTS        NINA_GPIO0 
#else
    #define NINA_GPIO0      (13) //connect 27-GPIO0 (Boot pin) of WiFiNINA to GPIO13 of Aries V2
    #define NINA_RESETN     (14)  // For Reseting NiNA Module 
    #define NINA_ACK        (15)   // Acknowledge 
    #define NINA_CTS        NINA_ACK
    #define NINA_RTS        NINA_GPIO0 
#endif

#define SPIWIFI_SS (9)

#define SS_FLASHMEM 1

#define PIN_SPI_SS    (10)
#define PIN_SPI_MOSI  (-1)
#define PIN_SPI_MISO  (-1)
#define PIN_SPI_SCK   (-1)
#define SDCARD_SS_PIN (10)

// attachInterrupt()
#define digitalPinToInterrupt(p) ((p) >= 0 && (p) <= 11 ? (p) + 10 : NOT_AN_INTERRUPT)

// GPIO
#define PINA(mode) *(unsigned short *)0x100C0000 = (*(unsigned short *)0x100C0000 |= mode) // Pinmode GPIO 0-15
// #define PORTA(data) *(unsigned short *)0x100BFFFC = data // GPIO 0-15  
#define PORTA(data) *(unsigned short *)0x100803FC = data // GPIO 0-7
// #define PORTB(data) *(unsigned short *)0x100803FC << 8 = data // GPIO 8-15 
#define PORTA_READ *(unsigned short *)0x100803FC

#define SERIAL_PORT_MONITOR   Serial

static const uint8_t SS   = PIN_SPI_SS;
// static const uint8_t CS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

// WiFiNINA
#define regtype volatile uint32_t
#define regsize uint32_t

