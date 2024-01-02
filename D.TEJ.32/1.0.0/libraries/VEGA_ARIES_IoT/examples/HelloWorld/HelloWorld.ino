/*
  @file HelloWorld.ino
  @brief contains routines for UART interface
  @detail Includes software functions declarations to initialize,configure, write and read UART interface

   Reference arduino code: https://arduinogetstarted.com/tutorials/arduino-hello-world
   Refrence aries board: https://vegaprocessors.in/blog/lets-get-started-with-vega/
   
   ** Hello World **
   By default this program runs if we directly upload it to the Aries Board.
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}



void loop() {
  #if defined (VEGA_ARIES_IOT)
  
  // put your main code here, to run repeatedly:
  Serial.println("Hello World...!");
  delay(1000);

  #else
  Serial.println("Choose the correct board! " );
  #endif 
}
