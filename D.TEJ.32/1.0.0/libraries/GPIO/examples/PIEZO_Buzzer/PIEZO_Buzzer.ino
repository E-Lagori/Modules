/*
  @file PIEZO_Buzzer.ino
  @brief Continuous beeping sound using Piezo Buzzer
  @detail Setting selected GPIO pin HIGH and LOW continuously (with small delay in between) to create beeping sound

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/
   
   *** Piezoelectric buzzer ***
   Connections:
   Buzzer     Aries Board
   VCC      -   3.3V
   GND      -   GND
   IN       -   GPIO0
*/

#define BUZZER 0 // connect INPUT pin of buzzer to GPIO-0

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 0 as an output.
  pinMode(BUZZER, OUTPUT); 
}

// the loop function runs over and over again forever
void loop() {
  // switching buzzer on and off rapidly
  digitalWrite(BUZZER, HIGH); //turn on the buzzer
  delay(100);
  digitalWrite(BUZZER, LOW);  //turn off the buzzer
  delay(100);
}
