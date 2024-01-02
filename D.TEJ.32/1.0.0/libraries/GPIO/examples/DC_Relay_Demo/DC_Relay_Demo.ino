/*
  @file DC_Relay_Demo.ino
  @brief Simple DC relay application
  @detail GREEN LED on the relay module will ON/OFF when the Relay is ON/OFF

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-one-channel-relay-module-with-vega-aries-boards/
   
   *** DC RELAY ***
  Connections:
   Relay     Aries Board
   VCC      -   3.3V
   GND      -   GND
   INP      -   GPIO0
*/


#define RELAY_PIN 0  // connect INPUT pin of DC Relay to GPIO-0 of Aries board 

char mode = 0xff;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT); // initialize digital pin 0 as an output.
}

// the loop function runs over and over again forever
void loop() {
  if(mode){
    Serial.println("Relay ON");
    digitalWrite(RELAY_PIN, HIGH);  //// let's turn ON the relay
  }else{
    Serial.println("Relay OFF");
    digitalWrite(RELAY_PIN, LOW);  //// turn OFF the relay
  }
  delayMicroseconds(400000);
  mode = ~(mode);
}
