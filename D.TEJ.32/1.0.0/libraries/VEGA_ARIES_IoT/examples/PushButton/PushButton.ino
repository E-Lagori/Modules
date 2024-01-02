/*
 @file   PushButton.ino
 @brief  contains routines for GPIO interface of push buttons
 @detail Press BTN-0 in ARIES IoT and GREEN LED will be ON. Press BTN-1 in ARIES IoT and RED LED will be ON 

 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1
 * Pin no. 22 - Green LED 
 * Pin no. 23 - Blue LED
 * Pin no. 24 - Red LED
 * BLUE,RED and GREEN LED will be in "ON" state for a digital "0" input and in "OFF" state for a digital "1" input.
 * 
 * 
*/

const int redLED = 24;// We will use the internal LED
const int greenLED = 22;// We will use the internal LED
const int btn0 = 18;// the pin our push button is on
const int btn1 = 19;// the pin our push button is on

void setup()
{
  delay(2000);
  Serial.begin(115200);
  //pinMode(redLED,OUTPUT); // Set the LED Pin as an output
  //pinMode(greenLED,OUTPUT); // Set the LED Pin as an output
  pinMode(btn0,INPUT); // Set the button as an input
  pinMode(btn1,INPUT); // Set the button as an input
}

void loop()
{
   #if defined (VEGA_ARIES_IOT)
   
  int digitalVal = digitalRead(btn0); // Take a reading
  int digitalVal1 = digitalRead(btn1); // Take a reading

  if(HIGH == digitalVal)
  {
    digitalWrite(redLED,HIGH); //Turn the LED off
  }
  else
  {
    digitalWrite(redLED,LOW);//Turn the LED on
  }

   if(HIGH == digitalVal1)
  {
    digitalWrite(greenLED,HIGH); //Turn the LED off
  }
  else
  {
    digitalWrite(greenLED,LOW);//Turn the LED on
  }

  #else
  Serial.println("Choose the correct board! " );
  #endif 
}
