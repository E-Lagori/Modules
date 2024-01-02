/*
  @file touch_sensor.ino
  @brief Recording physical touch using touch sensor
  @detail "Sensor is touched" message will be display and green led will blink if sensor get touched
  
  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-ttp223b-touch-sensor-module-with-vega-aries-boards/
   
   *** TOUCH SENSOR ***
   Connections:
   Touch Sensor   Aries Board
   VCC          -   3.3V
   GND          -   GND
   SIG          -   GPIO0
*/

#define PIN 0  // connect SIGNAL pin to ARIES GPIO-0

#define GREEN 22  // Green LED

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  delay(1000);

  pinMode(PIN, INPUT); // initialize digital PIN as INPUT
}

// the loop function runs over and over again forever
void loop() {
  // continuously raeding input PIN
  if (digitalRead(PIN) == HIGH){
    Serial.println("Sensor is touched");

    digitalWrite(GREEN, LOW);   // blink led if sensor is touched
    delay(50);
    digitalWrite(GREEN, HIGH);
  }
  delay(20);
}
