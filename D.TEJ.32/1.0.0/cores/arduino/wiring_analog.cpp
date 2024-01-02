#include "Arduino.h"
#include "wiring_analog.h"
#include "platform.h"
#include "pwm.h"
#include "utility/twi.h"
#include "Wire8.h"

TwoWire8 Wire8(8);

void analogWrite(uint32_t pin, uint32_t ulValue)
{
//   PWM.PWMC_Set_Period(pin, 800000);
  PWM.PWMC_Set_OnOffTime(pin, ulValue);
  PWM.PWMC_init(pin);
  PWM.PWMC_Enable();
}

#if defined(VEGA_ARIES_IOT)

ADS7828 ads;

static void writeRegister(uint8_t i2cAddress, uint8_t reg)
{
	Wire8.beginTransmission(i2cAddress);
	Wire8.write((uint8_t)reg);
	Wire8.endTransmission();
}

static uint16_t readRegister(uint8_t i2cAddress)
{
	Wire8.beginTransmission(i2cAddress);
	Wire8.endTransmission();
	Wire8.requestFrom(i2cAddress, (uint8_t)2);
	return (int16_t)((Wire8.read() << 8) | Wire8.read());
}


void ADS7828::getAddr_ADS7828(uint8_t i2cAddress)
{
	ads_i2cAddress = i2cAddress;
	ads_conversionDelay = ADS7828_CONVERSIONDELAY;
}

void ADS7828::begin()
{
	Wire8.begin();
}

/**************************************************************************/
/*
		Sets the Single-Ended/Differential Inputs
*/
/**************************************************************************/
void ADS7828::setSDMode(adsSDMode_t sdmode)
{
	ads_sdmode = sdmode;
}

/**************************************************************************/
/*
		Gets the Single-Ended/Differential Inputs
*/
/**************************************************************************/
adsSDMode_t ADS7828::getSDMode()
{
	return ads_sdmode;
}

/**************************************************************************/
/*
		Sets the Power-Down Mode
*/
/**************************************************************************/
void ADS7828::setPDMode(adsPDMode_t pdmode)
{
	ads_pdmode = pdmode;
}

/**************************************************************************/
/*
		Gets the Power-Down Mode
*/
/**************************************************************************/
adsPDMode_t ADS7828::getPDMode()
{
	return ads_pdmode;
}

uint32_t analogRead(uint32_t pin) {

	ads.getAddr_ADS7828(ADS7828_DEFAULT_ADDRESS);   // 0x48, 1001 000 (ADDR = GND)
	// ads.getAddr_ADS7828(ADS7828_VDD_ADDRESS);    // 0x49, 1001 001 (ADDR = VDD)
	// ads.getAddr_ADS7828(ADS7828_SDA_ADDRESS);    // 0x4A, 1001 010 (ADDR = SDA)
	// ads.getAddr_ADS7828(ADS7828_SCL_ADDRESS);    // 0x4B, 1001 011 (ADDR = SCL)

	// The Device operating and Power-Down mode
	// can be changed via the following functions

	ads.setSDMode(SDMODE_SINGLE);       // Single-Ended Inputs
	//ads.setSDMode(SDMODE_DIFF);       // Differential Inputs

	// ads.setPDMode(PDIROFF_ADON);        // Internal Reference OFF and A/D Converter ON
	// ads.setPDMode(PDADCONV);         // Power Down Between A/D Converter Conversions
	// ads.setPDMode(PDIRON_ADOFF);     // Internal Reference ON and A/D Converter OFF
	ads.setPDMode(PDIRON_ADON);      // Internal Reference ON and A/D Converter ON

	ads.begin();

	if (pin > 7)
	{
		return 0;
	}

	uint8_t config = 0;
	// Set Single-Ended/Differential Inputs
	config |= ads.getSDMode();
	
	// Set Power-Down Selection
	config |= ads.getPDMode();

	// Set single-ended input channel
	switch (pin)
	{
		case (0):
			config |= ADS7828_REG_COMMAND_CH_SINGLE_0;
			break;
		case (1):
			config |= ADS7828_REG_COMMAND_CH_SINGLE_1;
			break;
		case (2):
			config |= ADS7828_REG_COMMAND_CH_SINGLE_2;
			break;
		case (3):
			config |= ADS7828_REG_COMMAND_CH_SINGLE_3;
			break;
		case (4):
			config |= ADS7828_REG_COMMAND_CH_SINGLE_4;
			break;
		case (5):
			config |= ADS7828_REG_COMMAND_CH_SINGLE_5;
			break;
		case (6):
			config |= ADS7828_REG_COMMAND_CH_SINGLE_6;
			break;
		case (7):
			config |= ADS7828_REG_COMMAND_CH_SINGLE_7;
			break;

	}

	// Write config register to the ADC
	writeRegister(ADS7828_DEFAULT_ADDRESS, config);

	// Wait for the conversion to complete
	delay(ADS7828_CONVERSIONDELAY);

	// Read the conversion results
	// 16-bit unsigned results for the ADS7828
	return readRegister(ADS7828_DEFAULT_ADDRESS);
}

#else // ARIES_VEGA_V2 || ARIES_VEGA_V3 || ARIES_VEGA_MICRO

static void writeRegister(uint8_t address, uint8_t reg, uint16_t value) {

	Wire8.beginTransmission(address);
	Wire8.write((uint8_t) reg);
	Wire8.write((uint8_t) (value >> 8));
	Wire8.write((uint8_t) (value & 0xFF));
	Wire8.endTransmission(TRUE);
}

static uint16_t readRegister(uint8_t address, uint8_t reg) {

	Wire8.beginTransmission(address);
	Wire8.write(reg);
	Wire8.endTransmission(TRUE);
	Wire8.requestFrom(address, (uint8_t) 2);	//true
	return (Wire8.read() << 8 | Wire8.read());
}

uint32_t analogRead(uint32_t pin)
{
	Wire8.begin(); //need to check
	if (pin > 3) {	//channel=pin
		return 1;
	}

	// Start with default values
	uint16_t config = ADS1015_REG_CONFIG_CQUE_NONE |// Disable the comparator (default val)
			ADS1015_REG_CONFIG_CLAT_NONLAT |  // Non-latching (default val)
			ADS1015_REG_CONFIG_CPOL_ACTVLOW | // Alert/Rdy active low   (default val)
			ADS1015_REG_CONFIG_CMODE_TRAD | // Traditional comparator (default val)
			ADS1015_REG_CONFIG_DR_3300SPS |	  // 3300 samples per second
			ADS1015_REG_CONFIG_MODE_SINGLE;	  // Single-shot mode (default)

	// Set PGA/voltage range
	config |= ADS1015_REG_CONFIG_PGA_4_096V;

	// Set single-ended input channel
	switch (pin) {
	case (0):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_0;
		break;
	case (1):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_1;
		break;
	case (2):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_2;
		break;
	case (3):
		config |= ADS1015_REG_CONFIG_MUX_SINGLE_3;
		break;
	}

	// Set 'start single-conversion' bit
	config |= ADS1015_REG_CONFIG_OS_SINGLE;

	// Write config register to the ADC
	writeRegister(ADS1015_ADDRESS, ADS1015_REG_POINTER_CONFIG, config);

	// Wait for the conversion to complete
	delayMicroseconds(ADS1015_CONVERSIONDELAY);

	// Read the conversion results
	// Shift 12-bit results right 4 bits for the ADS1015

	return readRegister(ADS1015_ADDRESS, ADS1015_REG_POINTER_CONVERT)>> BIT_SHIFT;

	//return 0;
}

#endif  // VEGA_ARIES_IOT


