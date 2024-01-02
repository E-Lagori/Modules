/*
  @file hallMagneticSensor.ino
  @brief KY-035 is a analog device that varies its output voltage proportional to the magnetic field it is sensing.
  @detail With no magnetic field present, the device will produce an output voltage equal to half the power-supply voltage (VCC).
          As the magnetic field strengthens, the output voltage will either start pulling it closer to ground (magnetic north) 
          or closer to the power-supply voltage (magnetic south) until it reaches a saturation point.

          
  * About ARIES Development Boards: https://vegaprocessors.in/devboards/
   
  *** ANALOG HALL MAGNETIC SENSOR (KY-035) ***
   
  * Connections:
  ---------------------------------
  |    KY-035     |  Aries Board  |
  ---------------------------------
  |  middle(+/R)  |     3.3V      |
  |   GND(-/G)    |     GND       |
  |     S(Y)      |     A-0       |
  ---------------------------------
*/


int sensorPin = 0; // select the input pin
int ledPin = 22; // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor

void setup () {
pinMode (ledPin, OUTPUT);
Serial.begin (115200);
}

void loop () {
sensorValue = analogRead (sensorPin);
// depending upon the magnetic field strengthens, led blinking delay will vary.
digitalWrite (ledPin, HIGH);
delay (sensorValue);
digitalWrite (ledPin, LOW);
delay (sensorValue);
Serial.println (sensorValue, DEC); // prints an output voltage in serial monitor
}
