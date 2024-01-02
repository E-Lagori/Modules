/*
  @file microwaveRadarMotionSensor.ino
  @brief The RCWL-0516 microwave sensor detects any movement from any object
  @detail In this demo we are using ARIES Board to poll the sensor pin continuously to see if it has detected any motion (Input Pin HIGH).
   
  * About ARIES Development Boards: https://vegaprocessors.in/devboards/
   
  *** Microwave Radar Motion Sensor (RCWL-0516) ***
   
  * Connections:
  ---------------------------------
  |   RCWL-0516   |  Aries Board  |
  ---------------------------------
  |     3V3       |     3.3V      |
  |     GND       |     GND       |
  |     OUT       |     GPIO-0    |
  ---------------------------------
*/

int ledPin = 24;                // choose the pin for the LED
int inputPin = 0;               // choose the input pin (for Radar sensor)
int motionState = LOW;          // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  delay(1000);
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(115200);
}
 
void loop() {
  val = digitalRead(inputPin);  // read input value

  if (val == HIGH) {  // check if the input is HIGH
    digitalWrite(ledPin, LOW);  // turn LED ON
    
    if (motionState == LOW) {
      Serial.println("Motion detected!"); // print on output change
      motionState = HIGH;
    }
  }
  else {
    digitalWrite(ledPin, HIGH); // turn LED OFF
    
    if (motionState == HIGH) {
      Serial.println("Motion ended!");  // print on output change
      motionState = LOW;
    }
  }
}
