/*
  @file MQ3_Gas_Sensor.ino
  @brief Interfacing MQ3 gas sensor with ARIES board 
  @detail This demo read the MQ3 Sensor values and detect the presence of Alcohol and displays it on the serial monitor
   
   Refrence aries board: https://www.openhacks.com/uploadsproductos/rain_sensor_module.pdf
   Reference Arduino code: https://lastminuteengineers.com/mq3-alcohol-sensor-arduino-tutorial/ 
   
   *** MQ3 Gas Sensor *** 
   Connections:
   MQ3 Sensor     Aries Board
   VCC        -   5V
   GND        -   GND
   A0         -   A0 using 2.7K & 4.7K  Resistor 
   

  Note: A voltage divider is required between MQ3 sensor output and Analog pin of Aries board, for accurate measurements. 
  Connect a 2.7K resistor to A0 pin of MQ3 sensor. Connect one end of 4.7K resistor in series to the 2.7K resistor, and other end to the GND.
  Take the output from the junction of 2.7K and 4.7K resistor.

*/

#define MQ3pin A0   //Connect to Analog Pin A0
#define Normal 400  // Define min value that we consider drunk. Replace this value with your own readings
#define Drunk 800   // Define max value that we consider drunk.  Replace this value with your own readings
#define ledPin 24   //Internal LED 


float sensorValue;  //variable to store sensor value

void setup() {
  delay(2000); 
  Serial.begin(115200); // sets the serial port to 115200
  Serial.println("Connect MQ3 sensor to ARIES board & adjust threshold");
  Serial.println("MQ3 warming up!");
  delay(20000); // allow the MQ3 to warm up
}

void loop() {
  sensorValue = analogRead(MQ3pin); // read analog input pin A0

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);

  // Determine the status
  if (sensorValue < Normal) {
    Serial.println("  |  Status: No Alchohol Detected");
     digitalWrite(ledPin,HIGH);
  } else if (sensorValue >= Normal && sensorValue < Drunk) {
    Serial.println("  |  Status: Drinking but within limits");
    digitalWrite(ledPin,HIGH);
  }else {
    Serial.println("  |  Status: DRUNK");
    digitalWrite(ledPin,LOW);
  }
  
  delay(200); // wait for next reading
}
