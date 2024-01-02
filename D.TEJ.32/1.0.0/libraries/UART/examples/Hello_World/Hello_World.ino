/*
  @file hello_world.ino
  @brief contains routines for UART interface
  @detail Includes software functions declarations to initialize,configure, write and read UART interface

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/first-hello-world-project-in-aries-v3-0/
   
  ** Hello World **
  Note: Default baud rate for serial communication is 115200 bits per second
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  // replace the string to change output on serial monitor
  Serial.println("Hello World...!");
  delay(1000);
}
