/*
  @file switch.ino
  @brief bluetooth controlled switch
  @detail In this demo we are controlling built-in RGB LED 
          with android app via bluetooth module. 

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
ESP8266Class Bluetooth(1); // UART-1

#define SIZE 10  // Size for receive buffer

#define GREEN_LED 22   // GPIO-22
#define BLUE_LED  23   // GPIO-23
#define RED_LED   24   // GPIO-24

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

  // switch-1
  if(strncmp(receiveBuffer, "1A", 2) == 0)
    digitalWrite(GREEN_LED, LOW); // Green LED on
  else if(strncmp(receiveBuffer, "1a", 2) == 0)
    digitalWrite(GREEN_LED, HIGH);  // Green LED off

  // switch-2
  else if(strncmp(receiveBuffer, "2A", 2) == 0)
    digitalWrite(BLUE_LED, LOW); // Blue LED on
  else if(strncmp(receiveBuffer, "2a", 2) == 0)
    digitalWrite(BLUE_LED, HIGH);  // Blue LED off

  // switch-3
  else if(strncmp(receiveBuffer, "3A", 2) == 0)
    digitalWrite(RED_LED, LOW); // Red LED on
  else if(strncmp(receiveBuffer, "3a", 2) == 0)
    digitalWrite(RED_LED, HIGH);  // Red LED on

  /* 
    Add your own code here to control anything 
    over a switch using an android app.
  */
}
