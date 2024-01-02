/*
  @file RainSensor.ino
  @brief Interfacing Rain sensor with ARIES v2 
  @detail This demo read the Rain Sensor value and detect the presence of Rain based on the water that falls on the senosr

   Refrence aries board: https://www.openhacks.com/uploadsproductos/rain_sensor_module.pdf
   
   *** Rain Sensor (HL-83) ***
   
   Connections:
   Rain Sensor       Aries Board
   One end        -   3.3V
   Other end      -   A0
  
  100 ohm Resistor    Aries board
  One end         -   Rain Sensor & A0
  Other end       -   Ground

  Note: Seperate controller module is available for rain sensor. Follow the above connections only if you don't have the controller module along with the rain sensor.
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  //Serial.println(sensorValue);

  if(sensorValue <10) 
  Serial.println("No Rain");
  else if(sensorValue<150) 
  Serial.println("Moderate Rain");
  else Serial.println("Heavy Rain");

  delay(1);        // delay in between reads for stability
}
