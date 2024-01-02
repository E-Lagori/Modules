/*
  @file dimmer.ino
  @brief control intensity of light  
  @detail In this demo we will control the intensity of LED
          using Android app. 

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Android App : https://play.google.com/store/apps/details?id=com.aniketraj.bluetronics

  *** HC-05 Bluetooth Module ***
  Connections:
    HC-05      Aries Board
    VCC      -   3.3/5V
    GND      -   GND
    RXD      -   TX-1
    TXD      -   RX-1

  *** LED ***
  Connections:
  LED      ARIES Board
  VCC      -     3.3V
  GND      -     GND
  IN       -     PWM-0
*/

#include <pwm.h>
#include <esp8266.h>

ESP8266Class Bluetooth(1); // UART-1

#define SIZE 1000 // receive buffer size
#define PIN 0    // PWM Channel 
#define PERIOD 1000000

char receiveBuffer[SIZE] = {0, };
int count;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication for both:
  Serial.begin(115200); // UART-0 : Serial monitor
  Bluetooth.begin(9600); // UART-1 : HC-05 Bluetooth Module
  delay(1000);

  PWM.PWMC_Set_Period(PIN, PERIOD); 
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
  
  int data = atoi(receiveBuffer); // convert argument to int
  analogWrite(PIN, map(data, 0, 99, 0, PERIOD));
}
