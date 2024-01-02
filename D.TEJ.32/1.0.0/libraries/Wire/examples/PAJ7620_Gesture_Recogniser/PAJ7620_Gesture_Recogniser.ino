 /*
  @file PAJ7620_Gesture_Recogniser.ino
  @brief Demonstration of PAJ7620 Gesture Recogniser module
  @detail This sensor will recognize the hand gesture movement prints it in the serial monitor

   Reference arduino code: https://github.com/playfultechnology/arduino-gesture-recogniser
   *  Library Name : Gesture_PAJ7620
   *  Library Version : 1.0.0  
   
   *** PAJ7620 Gesture Recognizer ***
   Connections:
   PAJ7620     Aries Board
   VCC          -   3.3V
   GND          -   GND
   SDA          -   SDA0
   SCL          -   SCL-0
*/

// INCLUDES
// Aries Wire library is for communicating with any I2C device
#include <Wire.h>
// PAJ7620 library, based on datasheet as described at 
// https://www.epsglobal.com/Media-Library/EPSGlobal/Products/files/pixart/PAJ7620F2.pdf?ext=.pdf
#include <paj7620.h>

TwoWire Wire(0);

void setup() {
  //delay(2000);
	Serial.begin(115200);   // Initialise serial connection to display results

  int error = paj7620Init();    // Initialise the sensor
	if(error) {
    Serial.print(F("Initialisation error code: "));
    Serial.println(error);
	}
	else {
		Serial.println(F("Ready!"));
	}
}

void loop() {
	byte gesture;     // Create a variable to hold the value of any gesture recognised
	int error;         // Error variable holds any error code
  
	error = paj7620ReadReg(0x43, 1, &gesture);    // Read Reg 0x43 of Bank 0 to get result of any recognised gesture, and store in 'gesture' variable
 
	if(!error) {
		switch (gesture) {
			case GES_RIGHT_FLAG:
			  Serial.println(F("Right"));          
				break;
			case GES_LEFT_FLAG: 
				Serial.println(F("Left"));         
				break;
			case GES_UP_FLAG:
				Serial.println(F("Up"));        
				break;
			case GES_DOWN_FLAG:
				Serial.println(F("Down"));         
				break;
			case GES_FORWARD_FLAG:
				Serial.println(F("Forward"));
				break;
			case GES_BACKWARD_FLAG:		  
				Serial.println(F("Backward"));
				break;
      // Library also defines GES_CLOCKWISE_FLAG GES_COUNT_CLOCKWISE_FLAG and GES_WAVE_FLAG, but found these unreliable
			default:
				break;
		}
	}
 else {
    Serial.print(F("Error code: "));
    Serial.println(error);
 }
  
  delay(10);      // Introduce small delay before next polling the sensor 
}
