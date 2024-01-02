/*
  @file generic.ino
  @brief receive data from android app
  @detail this demo display the data (on serial monitor) receive from android app 
          via bluetooth module

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

  Note: Default baud rate of UART is 115200 bits per second
*/

#include <esp8266.h>
ESP8266Class Bluetooth(1);

#define SIZE 4096 // Size of receive buffer

char receiveBuffer[SIZE] = {0, };
int count;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication for both:
  Serial.begin(115200); // UART-0
  Bluetooth.begin(9600); // UART-1
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
}
