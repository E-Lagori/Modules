/*
  @file voiceControl.ino
  @brief voice controlled LED
  @detail In this demo we will control built-in LED over voice
          using Android app. 

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Android App : https://play.google.com/store/apps/details?id=com.aniketraj.bluetronics

  *** HC-05 Bluetooth Module ***
  Connections:
    HC-05      ARIES Board
    VCC      -   3.3/5V
    GND      -   GND
    RXD      -   TX-1
    TXD      -   RX-1
*/

#include <esp8266.h>
ESP8266Class Bluetooth(1); // UART-1

#define SIZE 100  // Size for receive buffer

char receiveBuffer[SIZE] = {0, };
int count;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication for both:
  Serial.begin(115200);  // UART-0
  Bluetooth.begin(9600); // UART-1 : HC-05 Bluetooth Module default baudrate is 9600 bits per second
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  count = 0;
  for(;count<SIZE;count++){
    receiveBuffer[count] = 0;
  }
  Serial.print("Ready to receive data.....");
  while(1){
    count = 0;
    while(Bluetooth.available() > 0){
      receiveBuffer[count++] = Bluetooth.read();
    }
    if(receiveBuffer[count-1] == '\n'){
      receiveBuffer[count-1] = '\0';
      break;
    }
  }
  Serial.println("received.");
  Serial.println(receiveBuffer);


  /* 
    Add your own code here to control anything 
    over voice using an android app.
  */

  /* Example: 
   *  Say "LED on" to turn on the LED
   *  Say "LED off" to turn off the LED
   */
  if(strncmp(receiveBuffer, "LED on", 6) == 0)
    digitalWrite(LED_BUILTIN, LOW);  // LED on
  else if(strncmp(receiveBuffer, "LED off", 6) == 0)
    digitalWrite(LED_BUILTIN, HIGH); // LED off
}
