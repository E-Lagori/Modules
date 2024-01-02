/*
  @file PIR_MotionSensor.ino
  @brief Interface HC-SR501 PIR motion sensor with ARIES V2 board
  @detail Green LED will turn ON when movement is detected in the vicinity of the sensor and RED LED will glow when there is no movement.
  
   Reference aries board: https://vegaprocessors.in/blog/pir-motion-sensor-with-vega-processors/
   
   *** Passive Infrared Motion Sensor(HC-SR501) ***
   Connections:
   PIR        Aries Board
   VCC      -   5V
   GND      -   GND
   OUT      -   GPIO0
*/

int led1 = 22;               // Green LED
int led2 = 24;               // Red LED
int sensor = 0;              // the pin that the sensor is atteched to GPIO-0 of Aries Board

void setup() {
  pinMode(led1, OUTPUT);      // initalize LED as an output
  pinMode(led2, OUTPUT);    
  pinMode(sensor, INPUT);     // initialize sensor as an input
  Serial.begin(115200);       // initialize serial
}

void loop(){
  int val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led1, LOW);   // if motion detected turn (Green LED -> ON) and (Red LED -> OFF)
    digitalWrite(led2, HIGH);
  } 
  else {
      digitalWrite(led1, HIGH); // for no motion turn (Red LED -> ON) and (Green LED -> OFF) 
      digitalWrite(led2, LOW); 
    }
}
