#include <avr/pgmspace.h>
#include "Arduino.h"
#include "pwm.h"

void tone(uint8_t _pin, unsigned int frequency, unsigned long duration)
{

    unsigned int period = F_CPU/frequency;
    PWM.PWMC_Set_Period(_pin, period);
    PWM.PWMC_Set_OnOffTime(_pin, period/2);
    PWM.PWMC_init(_pin);
    PWM.PWMC_Enable();
    unsigned long time_now = millis();
    if(duration != 0){
        while(millis() < time_now + duration){
            //wait approx. [period] ms
        }
        noTone(_pin);
    }
}

void noTone(uint8_t _pin)
{
    PWM.PWMC_Disable();
}