/*
 @file   RGBLed.ino
 @brief  Contains routines for GPIO interface
 @detail Onboard RGB LEDs will blink with 1 second delay

 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1 
 * LED pins for Aries Board are: 
 * Pin no. 22 - Green LED 
 * Pin no. 23 - Blue LED
 * Pin no. 24 - Red LED
 * Note: BLUE,RED and GREEN LED will be in "ON" state for a digital "0" input and in "OFF" state for a digital "1" input.
 * 
*/

int redLed=24;    // Red LED
int greenLed=22; // Green LED
int blueLed=23; // Blue LED

void setup()
{
  delay(2000);
  Serial.begin(115200);   
}
void loop()
{  
  #if defined (VEGA_ARIES_IOT)
  
    digitalWrite(redLed,LOW);    // LED ON
    delay(1000);                // Set the delay time, 1000 = 1S
    digitalWrite(redLed,HIGH);  // LED OFF
    delay(1000);               // Set the delay time, 1000 = 1S
    
    digitalWrite(greenLed,LOW);    
    delay(1000);                 
    digitalWrite(greenLed,HIGH);  
    delay(1000);                 
    
    digitalWrite(blueLed,LOW); 
    delay(1000);               
    digitalWrite(blueLed,HIGH);  
    delay(1000);  

    #else
    Serial.println("Choose the correct board! " );
    #endif             
} 
