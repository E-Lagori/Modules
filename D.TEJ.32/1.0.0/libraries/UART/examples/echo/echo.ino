/*
  @file echo.ino
  @brief UART ECHO
  @detail in this demo we are reading the data from serial monitor 
          and then writing the same data on serial monitor 

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/

  Note: Default baud rate for UART communication is 115200 bits per second
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  // checking if data is available for read
  char data;

  if(Serial.available()) {
    data = Serial.read();
    Serial.write(data);
  }
}
