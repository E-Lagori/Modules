/*
  @file transmitter_nrf24.ino
  @brief Interfacing NRF24L01 with ARIES Board using SPI.
  @detail The demo to transmit the data to receiver controller using NRF24L01

   Aries V2 pinout: https://vegaprocessors.in/blog/interfacing-8x8-led-dot-matrix-to-aries-v2-board/
   NRF24L01 pinout: https://howtomechatronics.com/wp-content/uploads/2017/02/NRF24L01-Pinout-NRF24L01-PA-LNA-.png

   * Library Name : RF24 (by TMRH20, Avamander)

   *** A Radio Transceiver Module (NRF24L01+PA/LNA) ***

   Connections:
   NRF24L01      Aries Board
   VCC          -   3.3V
   GND          -   GND
   CE           -   GPIO-9
   CNS          -   GPIO-10
   SCK          -   SCLK0
   MISO         -   MISO0
   MOSI         -   MOSI0
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

SPIClass SPI(0);

RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int button_pin = 18;
boolean button_state = 0;

void setup() {
pinMode(button_pin, INPUT);
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter
}

void loop()
{
// Press and Hold the BTN1 button to change button state to LOW
button_state = digitalRead(button_pin);
if(button_state == HIGH)
{
const char text[] = "Your Button State is HIGH";
radio.write(&text, sizeof(text));                  //Sending the message to receiver
}
else
{
const char text[] = "Your Button State is LOW";
radio.write(&text, sizeof(text));                  //Sending the message to receiver 
}
radio.write(&button_state, sizeof(button_state));  //Sending the message to receiver 
delay(1000);
}
