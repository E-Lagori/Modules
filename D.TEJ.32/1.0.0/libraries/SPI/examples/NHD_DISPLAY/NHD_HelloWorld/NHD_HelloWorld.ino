/**
 @file NHD_HelloWorld.ino
 @brief Example Code for NHD Display interface
 @detail This application demonstrates the usage of FT801 library on NHD_43CTP_SHIELD platform 

 * Reference NHD datasheet: https://www.mouser.in/datasheet/2/291/NHD_4_3CTP_SHIELD_L-2953341.pdf
 * Library Name: https://gitlab.com/riscv-vega/vega-sensor-libraries/display/nhd_display 
 * Connection Diagram: https://gitlab.com/riscv-vega/vega-sensor-libraries/display/nhd_display/-/blob/main/nhd_diagram.pdf
 * 
 * NHD Display
 * Connections:
 *    
 *    NHD Display     Aries Board
 * 
      *   J1 Interface
      SCL             No Connect
      SDA             No Connect
      AREF            No Connect
      GND             Ground
      13              No Connect (Short SJ2 for SPI SCK signal)
      12              No Connect (Short SJ3 for SPI MISO signal)
      11              No Connect (Short SJ1 for SPI MOSI signal)
      10              GPIO10-  FT801 Active LOW Chip Select signal
      9               GPIO9- FT801 Active LOW Host Interrupt signal
      8               GPIO8- FT801 Active LOW Power Down signal
   
      *  J2 Interface
      7               No Connect
      6               No Connect
      5               No Connect
      4               GPIO-4 ( Chip Select signal)     
   
      *  J3 Interface
    RESERVED        No Connect
    IOREF           No Connect
    RESET           No Connect
    3.3V            No Connect
    5V              Supply Voltage for Module (+5V)
    GND             Ground
    GND             Ground
    Vin             No Connect

      *  J4 Interface
    A0            No Connect
    A1            No Connect
    A2            No Connect
    A3            No Connect
    A4            No Connect
    A5            No Connect
 
      *  J5 Interface
    MISO          MISO-1 (SPI MISO signal (Default))
    5V            No Connect
    SCK           SCLK-1 (SPI SCK signal (Default))
    MOSI          MOSI-1 (SPI MOSI signal (Default))
    RESET         No Connect
    GND           Ground.
 **/


#include "SPI.h"
#include "Wire.h"

SPIClass SPI(1);
/* Platform specific includes */
#include "FT_NHD_43CTP_SHIELD.h"

/* Global object for FT801 Implementation */
FT801IMPL_SPI FTImpl(FT_CS_PIN,FT_PDN_PIN,FT_INT_PIN);

/* Api to bootup FT801, verify FT801 hardware and configure display/audio pins */
/* Returns 0 in case of success and 1 in case of failure */
int16_t BootupConfigure()
{
	uint32_t chipid = 0;
	FTImpl.Init(FT_DISPLAY_RESOLUTION);//configure the display to the WQVGA

	delay(20);//for safer side
	chipid = FTImpl.Read32(FT_ROM_CHIPID);
	
	/* Identify the chip */
	if(FT801_CHIPID != chipid)
	{
		Serial.print("Error in chip id read ");
		Serial.println(chipid,HEX);
		return 1;
	}
	
	/* Set the Display & audio pins */
	FTImpl.SetDisplayEnablePin(FT_DISPENABLE_PIN);
    FTImpl.SetAudioEnablePin(FT_AUDIOENABLE_PIN); 
	FTImpl.DisplayOn(); 	
	FTImpl.AudioOn();  		
	return 0;
}

/* API to display Hello World string on the screen */
void HelloWorld()
{
	/* Change the below string for experimentation */
	const char Display_string[12] = "Hello World";
	
	/* Display list to display "Hello World" at the centre of display area */
	FTImpl.DLStart();//start the display list. Note DLStart and DLEnd are helper apis, Cmd_DLStart() and Display() can also be utilized.
	FTImpl.ColorRGB(0xFF,0xFF,0xFF);//set the color of the string to while color
	FTImpl.Cmd_Text(FT_DISPLAYWIDTH/2, FT_DISPLAYHEIGHT/2, 29, FT_OPT_CENTER, Display_string);//display "Hello World at the center of the screen using inbuilt font handle 29 "
	FTImpl.DLEnd();//end the display list
	FTImpl.Finish();//render the display list and wait for the completion of the DL
}

/* bootup the module and display "Hello World" on screen */
void setup()
{
	/* Initialize serial print related functionality */
	Serial.begin(9600);
	
	/* Set the Display Enable pin*/   
	Serial.println("--Start Application--");
	if(BootupConfigure())
	{
		//error case - do not do any thing
	}
  	else
	{
		HelloWorld();
	}
	Serial.println("--End Application--");
}

/* Nothing in loop api */
void loop()
{
}
