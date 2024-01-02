/*
  @file Capacitive_Soil_Moisture_Sensor.ino
  @brief Interfacing Capacitive Soil Moisture Sensor to ARIES V2 Board
  @detail This demo is used to display the readings of Soil Moisture Sensor using ARIES V2 Board.
  If no moisture content then Red LED will be ON, For high moisture content Green LED will be on.
  Corrsponding output can be seen using serial monitor also. 
   
   Reference aries board: https://vegaprocessors.in/blog/interfacing-8x8-led-dot-matrix-to-aries-v2-board/
   
   *** Capacitive Soil Moisture Sensor ***
   Connections:
   Sensor           Aries Board
   VCC          -   5V
   GND          -   GND
   Aout         -   A0
   Dout         -   Not Required

   **Note : You can use the same demo to interface Soil Moisture Sensor also by changing the threshold values.
   *You can change the threshold values according to your requirements.
*/
  
// Sensor pins
#define redLed    24    // Internal Red LED in Aries V2 board
#define yellowLed 21   // Internal Yellow LED in Aries V2 board
#define greenLed  22  // Internal Green LED in Aries V2 board

#define sensorPin A0  //Connect Aout Pin to A0 of aries board

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
  // Initially keep the sensor OFF
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);

  Serial.begin(115200);
}

void loop() { 
  
  int sensorValue = analogRead(A0);      // read the input on analog pin 0:
  //Serial.println(sensorValue);        // print out the value you read:   
  
  if(sensorValue < 1200) {
  digitalWrite(greenLed, LOW);
  delay(100);
  digitalWrite(greenLed, HIGH);
  delay(100);
  Serial.println("High Moisture content");
   }
   
  else if((sensorValue > 1200) && (sensorValue<1800)){ 
  digitalWrite(yellowLed, HIGH);
  delay(100);
  digitalWrite(yellowLed, LOW);
  delay(100);
  Serial.println("Moderate Moisture content");
  }
  
  else {
  digitalWrite(redLed, LOW);
  delay(100);
  digitalWrite(redLed, HIGH);
  delay(100);
  Serial.println("No moisture -  Need water");
  }

  delay(1);        // delay in between reads for stability
}
