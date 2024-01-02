/*
 @file   Potentiometer.ino
 @brief  This example reads the data from the on-board potentiometer
 @detail This example reads the potentiometer values and prints updates to the Serial Monitor every 500 ms.

 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1
 * 
 *  ReadAnalogVoltage:
 *  Reads an analog input on pin 6, converts it to voltage, and prints the result to the Serial Monitor.
 *  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
 * 
*/


// the setup routine runs once when you press reset:
void setup() {
  delay(2000);
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {
  #if defined (VEGA_ARIES_IOT)
  
  // read the input on analog pin 6:
  int sensorValue = analogRead(A6);  
  
  Serial.print(" \nADC Value: ");
  Serial.print(sensorValue);
 
 
  // Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 3.3V):
  // Internal Reference OFF and A/D Converter ON
  float voltage = sensorValue * (3.3 / 4095.0);
  // print out the value you read:
  Serial.print(" \tVoltage Value: ");
  Serial.print(voltage);
  delay(500);

  #else
  Serial.println("Choose the correct board! " );
  #endif 
}
