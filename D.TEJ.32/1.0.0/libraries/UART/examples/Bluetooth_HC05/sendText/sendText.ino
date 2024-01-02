/*
  @file sendText.ino
  @brief send text via bluetooth
  @detail demo to send text to an android app via bluetooth

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Android App : https://play.google.com/store/apps/details?id=com.aniketraj.bluetronics

  *** HC-05 Bluetooth Module ***
  Connections:
    HC-05       ARIES Board
    VCC      -   3.3/5V
    GND      -   GND
    RXD      -   TX-1
    TXD      -   RX-1
*/

#include <esp8266.h>

ESP8266Class Bluetooth(1); // UART-1 (Bluetooth)
ESP8266Class mySerial(0);  // UART-0 (Serial monitor)

char sendBuffer[4096] = {0, }; 
int count;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication for both:
  mySerial.begin(115200);  // UART-0
  Bluetooth.begin(9600); // UART-1
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  count = 0;
  for(;count<1000;count++){
    sendBuffer[count] = 0;
  }
  mySerial.print("Enter the text....");
  while(1){
    count = 0;
    while(mySerial.available() > 0){
      sendBuffer[count++] = mySerial.read();
    }
    if(sendBuffer[count-1] == '\n'){
      break;
    }
  }
  mySerial.println();
  mySerial.print("Message Entered: ");mySerial.println(sendBuffer); 

  for(int i=0; i<count; i++){
    Bluetooth.write(sendBuffer[i]);
  }
}
