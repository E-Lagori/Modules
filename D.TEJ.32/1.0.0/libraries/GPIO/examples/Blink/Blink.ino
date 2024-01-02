/*
  @file Blink.ino
  @brief contains routines for GPIO interface
  @detail Includes software functions declarations to initialize,configure, write and read LED over GPIO interface

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/aries-blinking-led/
   
  Connections:
    No external connections required to test this code. You can directly connect Aries board through USB and upload the program
    LED pins for Aries Board are: 
    pin no. 20,21 - Yellow LED (for Aries v2)
    Pin no. 22 - Green LED 
    Pin no. 23 - Blue LED
    Pin no. 24 - Red LED
  Note: BLUE,RED and GREEN LED will be in "ON" state for a digital "0" input and in "OFF" state for a digital "1" input.
        YELLOW LED will be in "ON" state for a digital "1" input and in "OFF" state for a digital "0" input.
*/

int ledPin=22; // Green LED

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize digital pin 22 as an output.
    pinMode(ledPin,OUTPUT);
}

// the loop function runs over and over again forever
void loop() {  
    // turning led ON and OFF after every 1 second delay
    digitalWrite(ledPin,HIGH); // LED OFF
    delay(1000);               // Set the delay time, 1000mS
    digitalWrite(ledPin,LOW);  // LED ON
    delay(1000);               // Set the delay time, 1000ms
} 
