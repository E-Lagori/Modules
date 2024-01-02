/*
  @file Bluetooth_HC05.ino
  @brief contains routines for UART HC05 interface
  @detail Includes software functions declarations to initialize,configure, write and read HC05 over UARt interface

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-hc-05-bluetooth-module-with-vega-aries-boards/
    Android App: https://drive.google.com/file/d/1I8Gzlu3QLy9f35Pzw_uch31uhC18UtSt/view?usp=sharing
   
  **HC05 bluetooth sensor**
  Connections:
   HC05     Aries Board
   VCC      -   3.3/5V
   GND      -   GND
   RXD      -   TX1
   TXD      -   RX1
   For connecting to port 2 (RX2 and TX2) of aries board use the function UARTClass MyBlue(2) instead of UARTClass MyBlue(1);
*/

#include <UARTClass.h>

UARTClass MyBlue(1); // UART-1 

int flag = 0;
int LED = 22;  // Green LED

// the send_string function
int send_string(char * str) {

  while (*str != '\0') {
    MyBlue.write(*str);
    if (*str == '\n')
      MyBlue.write('\r');
    str++;
  }

  return 0;
}

// the receive_string function
void receive_string(char * str) {
  int data;
  char char_data;

  while (1) {
    do{
      data = MyBlue.read();
    }while(data == -1);

    char_data = (char)data;
    *str = char_data;
    str++;

    if (char_data == '\n') {
      *str = '\r';
      break;
    }
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize both serial communication 
  Serial.begin(115200); 
  MyBlue.begin(9600); // default baudrate for HC_05 is 9600 bits per second

  delay(1000);
  pinMode(LED, OUTPUT); // initialize LED pin/GPIO-22 as OUTPUT
  Serial.println("Ready to connect\nDefualt password is 1234 or 0000");
}

// the loop function runs over and over again forever
void loop() {
  // Continuously check for the string received
  static char str[100] = {0,};

  memset(str, 0, sizeof(str));
  receive_string((char*)str);
  Serial.println(str);

  if (strncmp(str, "ON", 2) == 0)
  {
    digitalWrite(LED, LOW); // make LED on
    send_string((char*)"LED ON\n");
  }
  else
  {
    send_string((char*)"LED OFF\n");
    digitalWrite(LED, HIGH); // make LED off
  }
}
