#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void yield(void);

// typedef enum {
//   LOW     = 0,
//   HIGH    = 1,
//   CHANGE  = 2,
//   FALLING = 3,
//   RISING  = 4,
// } PinStatus;

// typedef enum {
//   INPUT           = 0x0,
//   OUTPUT          = 0x1,
//   INPUT_PULLUP    = 0x2,
//   INPUT_PULLDOWN  = 0x3,
// } PinMode;

#define PI          3.1415926535897932384626433832795
#define HALF_PI     1.5707963267948966192313216916398
#define TWO_PI      6.283185307179586476925286766559
#define DEG_TO_RAD  0.017453292519943295769236907684886
#define RAD_TO_DEG  57.295779513082320876798154814105
#define EULER       2.718281828459045235360287471352

#define SERIAL      0x0
#define DISPLAY     0x1

#ifndef constrain
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif

#ifndef radians
#define radians(deg) ((deg)*DEG_TO_RAD)
#endif

#ifndef degrees
#define degrees(rad) ((rad)*RAD_TO_DEG)
#endif

#ifndef sq
#define sq(x) ((x)*(x))
#endif

typedef void (*voidFuncPtr)(void);
typedef void (*voidFuncPtrParam)(void*);

// interrupts() / noInterrupts() must be defined by the core

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitToggle(value, bit) ((value) ^= (1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

#ifndef bit
#define bit(b) (1UL << (b))
#endif

/* TODO: request for removal */
typedef bool      boolean;
typedef uint8_t   byte;
//typedef uint16_t  word;

void init(void);
void initVariant(void);

#ifndef HOST
int atexit(void (*func)()) __attribute__((weak));
#endif
int main() __attribute__((weak));

#ifdef EXTENDED_PIN_MODE
// Platforms who wnat to declare more than 256 pins need to define EXTENDED_PIN_MODE globally
typedef uint32_t pin_size_t;
#else
typedef uint8_t pin_size_t;
#endif

unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long);
unsigned long pulseInLong(pin_size_t pin, uint8_t state, unsigned long timeout);


void setup(void);
void loop(void);

#ifdef __cplusplus
} // extern "C"
#endif

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif // min

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif // max

#ifdef __cplusplus

/* C++ prototypes */
uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

unsigned long In(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);

//void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
//void noTone(uint8_t _pin);

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned long);
long map(long, long, long, long, long);

#endif // __cplusplus
