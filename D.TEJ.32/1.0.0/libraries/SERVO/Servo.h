#ifndef _SERVO_VEGA__
#define _SERVO_VEGA__

#include "variant.h"
#include <stdio.h>
#include "platform.h"

#define SERVO_DELAY	5000
#define SERVO_MIN	50000
#define SERVO_MAX	250000
#define SERVO_PERIOD	1500000 //For 50Hz, thejas soc 40mHz, period=CPU_FREQ/HZ


class Servo {
public:
  Servo();
  uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
  uint8_t attach(int pin, int min, int max); // as above but also sets min and max values for writes. 
  void detach();
  void write(int angle);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
  void writeMicroseconds(int value); // Write pulse width in microseconds 
  int read();                        // returns current pulse width as an angle between 0 and 180 degrees
  int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
  bool attached();                   // return true if this servo is attached, otherwise false 
private:
  uint8_t ch;
  uint8_t servoIndex;               // index into the channel data for this servo
  int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH    
  int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH
  int8_t prev_ch;   
};



#endif