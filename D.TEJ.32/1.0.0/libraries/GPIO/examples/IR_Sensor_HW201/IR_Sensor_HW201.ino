/*
  @file IR_Sensor_HW201.ino
  @brief Capturing IR(Infrared) signals using ARIES
  @detail GREEN LED on the aries board will ON when the IR receiver receives infrared waves

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-hw-201-ir-proximity-sensor-with-vega-aries-boards/
   
   *** Infrared Proximity Sensor(HW-201) ***
  Connections:
    IR        Aries Board
    VCC      -   3.3V
    GND      -   GND
    OUT      -   GPIO4
*/

int IRSensor = 4; // connect OUTPUT pin of IR sensor to Aries GPIO-4
int LED = 22; // Green color LED is internally connected to GPIO-22

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode (IRSensor, INPUT); // sensor pin as INPUT
  pinMode (LED, OUTPUT); // Led pin as OUTPUT
}

// the loop function runs over and over again forever
void loop() {
  // reading sensor data
  int statusSensor = digitalRead (IRSensor);   
  
  if (statusSensor == 1){
    digitalWrite(LED, HIGH); // LED OFF 
  }
  else {
    digitalWrite(LED, LOW); // LED ON
  }
}
