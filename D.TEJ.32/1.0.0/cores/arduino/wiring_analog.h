/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_ANALOG_
#define _WIRING_ANALOG_

__BEGIN_DECLS

#define ADS1015_REG_CONFIG_OS_SINGLE (0x8000)       // Write: Set to start a single-conversion

#define ADS1015_REG_POINTER_CONFIG (0x01)           //Configuration
#define ADS1015_REG_POINTER_CONVERT (0x00)          // Conversion

#define ADS1015_REG_CONFIG_PGA_4_096V (0x0200)      // +/-4.096V range = Gain 1

#define ADS1015_REG_CONFIG_MUX_SINGLE_0 (0x4000)    // Single-ended AIN0
#define ADS1015_REG_CONFIG_MUX_SINGLE_1 (0x5000)    // Single-ended AIN1
#define ADS1015_REG_CONFIG_MUX_SINGLE_2 (0x6000)    // Single-ended AIN2
#define ADS1015_REG_CONFIG_MUX_SINGLE_3 (0x7000)    // Single-ended AIN3

#define ADS1015_REG_CONFIG_CQUE_NONE  (0x0003)      // Disable the comparator and put ALERT/RDY in high state (default)
#define ADS1015_REG_CONFIG_CLAT_NONLAT (0x0000)     // Non-latching comparator (default)
#define ADS1015_REG_CONFIG_CPOL_ACTVLOW (0x0000)    // ALERT/RDY pin is low when active (default)
#define ADS1015_REG_CONFIG_CMODE_TRAD (0x0000)      // Traditional comparator with hysteresis (default)
#define ADS1015_REG_CONFIG_DR_1600SPS (0x0080)      // 1600 samples per second (default)
#define ADS1015_REG_CONFIG_DR_3300SPS (0x00C0)      // 3300 samples per second
#define ADS1015_REG_CONFIG_MODE_SINGLE (0x0100)     // Power-down single-shot mode (default)

#define BIT_SHIFT 4
#define ADS1015_CONVERSIONDELAY (1)
#define ADS1015_ADDRESS (0x48)

#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

// Function declarations

void analogWrite(uint32_t pin, uint32_t ulValue);
uint32_t analogRead(uint32_t pin);

__END_DECLS

#endif /* _WIRING_ANALOG_ */
