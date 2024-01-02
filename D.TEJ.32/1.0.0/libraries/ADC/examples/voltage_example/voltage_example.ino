/*
  @file voltage_example.ino
  @brief Read volatge value 
  @detail This demo display the volatge (in volts) on serial monitor

   Aries board PINOUT: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf
   
   *** Voltage Example ***
   Connections:
   Aries       Aries Board
   A0      -   3.3V
*/

#define PIN A0  // Reading value from Analog pin 0

float Voltage; 
float resolution = 0.002;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Voltage = resolution * (float)analogRead(PIN);
  Serial.print("Voltage = ");
  Serial.print(Voltage);
  Serial.println(" V");
  delay(1000);
}
