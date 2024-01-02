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

#ifndef _WIRING_DIGITAL_
#define _WIRING_DIGITAL_

__BEGIN_DECLS

/***************************************************/
// #define PIN_0			0
// #define PIN_1			1
// #define PIN_2			2
// #define PIN_3			3

// #define PIN_4			4
#define PIN_5			5
#define PIN_6			6
#define PIN_7			7

#define PIN_8			8
#define PIN_9			9
#define PIN_10			10
#define PIN_11			11

#define PIN_12			12
#define PIN_13			13
#define PIN_14			14
#define PIN_15			15

#define PIN_16			16
#define PIN_17			17
#define PIN_18			18
#define PIN_19			19

#define PIN_20			20
#define PIN_21			21
#define PIN_22			22
#define PIN_23			23

#define PIN_24			24
#define PIN_25			25
#define PIN_26			26
#define PIN_27			27

#define PIN_28			28
#define PIN_29			29
#define PIN_30			30
#define PIN_31			31

#define PIN_A0			A0
#define PIN_A1			A1
#define PIN_A2			A2
#define PIN_A3			A3


#define GPIO_0			0
#define GPIO_1			1
#define GPIO_2			2
#define GPIO_3			3


#define ON_LED		0
#define OFF_LED		1


// #define ON			1
// #define OFF			0

// #define HIGH			1
// #define LOW			0


/************************************************************************************************/
/**
 * \brief Configures the specified pin to behave either as an input or an output. See the description of digital pins for details.
 *
 * \param ulPin The number of the pin whose mode you wish to set
 * \param ulMode Either INPUT or OUTPUT
 */
extern void pinMode( uint32_t dwPin, uint32_t dwMode ) ;

/**
 * \brief Write a HIGH or a LOW value to a digital pin.
 *
 * If the pin has been configured as an OUTPUT with pinMode(), its voltage will be set to the
 * corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW.
 *
 * \note Digital pin PIN_LED is harder to use as a digital input than the other digital pins because it has an LED
 * and resistor attached to it that's soldered to the board on most boards. If you enable its internal 20k pull-up
 * resistor, it will hang at around 1.7 V instead of the expected 5V because the onboard LED and series resistor
 * pull the voltage level down, meaning it always returns LOW. If you must use pin PIN_LED as a digital input, use an
 * external pull down resistor.
 *
 * \param dwPin the pin number
 * \param dwVal HIGH or LOW
 */
extern void digitalWrite( uint32_t dwPin, uint32_t dwVal ) ;

/**
 * \brief Reads the value from a specified digital pin, either HIGH or LOW.
 *
 * \param ulPin The number of the digital pin you want to read (int)
 *
 * \return HIGH or LOW
 */
extern int digitalRead( uint32_t ulPin ) ;

__END_DECLS

#endif /* _WIRING_DIGITAL_ */
