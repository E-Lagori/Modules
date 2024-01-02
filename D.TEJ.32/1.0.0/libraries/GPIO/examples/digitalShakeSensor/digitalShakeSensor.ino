/*
  @file digitalShakeSensor.ino
  @brief The digital shake sensor is to detect hand shaking which is only sensitive to unidirectional hand movements.
  @detail In the direction indicated by the arrow on-board, every time the module is shaken, the built-in LED ON ARIES Board will toggle.

   
  * About ARIES Development Boards: https://vegaprocessors.in/devboards/
   
  *** Digital Shake Sensor ***
   
  * Connections:
  ---------------------------------
  |Shake Sensor   |  Aries Board  |
  ---------------------------------
  |     VCC(+)    |     3.3V      |
  |     GND(-)    |     GND       |
  |     OUT(D)    |     GPIO-0    |
  ---------------------------------
*/


#define LED_PIN                 22            // Green LED
#define DIGITAL_INPUT_PIN       0             // Connect the sensor to digital Pin 0 i.e. GPIO0

int stateFlag = 0;

void setup()
{
  delay(1000);
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  // Set to input mode and use external pull-up of 10K. 
  // Otherwise, it will fail to generate pulse under 3.3V power supply.
  pinMode(DIGITAL_INPUT_PIN, INPUT);   
}

void loop()
{  
  if (digitalRead(DIGITAL_INPUT_PIN) == 0){
    delay(100);
    stateFlag = !stateFlag;
  }
  digitalWrite(LED_PIN, stateFlag);
}
