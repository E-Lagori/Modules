/*
  @file RYG_LED_GPIO.ino
  @brief Simple LED Application
  @detail Turning LEDs ON and OFF in simple serial pattern (in loop)

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-ryg-led-with-aries-v2-0/
   
  *** RYG LED STRIP ***
  Connections:
   LED        Aries Board
   GND      -   GND
   R        -   GPIO0
   Y        -   GPIO1
   G        -   GPIO2
*/

#define RED_LED     0     // Connect Red LED pin to GPIO-0
#define YELLOW_LED  1     // Connect Yellow LED pin to GPIO-1
#define GREEN_LED   2     // Connect Green LED pin to GPIO-2

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as an output.
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // turning RYG LEDs on and then off in series with 1 second delay each
  digitalWrite(RED_LED, HIGH);      // Red LED ON
  delay(1000);
  digitalWrite(YELLOW_LED, HIGH);   // Yellow LED ON
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);    // Green LED ON
  delay(1000);
  digitalWrite(GREEN_LED, LOW);     // Green LED OFF
  delay(1000);
  digitalWrite(YELLOW_LED, LOW);    // Yellow LED OFF
  delay(1000);
  digitalWrite(RED_LED, LOW);       // Red LED OFF
  delay(1000);
}
