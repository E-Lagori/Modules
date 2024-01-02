/*
  @file flameSensor.ino
  @brief For DETECTING fire for about a small range of 3 feets
  @detail If holding a flame within "1.5 feet" or "1.5 to 3" feet in front of the sensor; "case 0" ("Close Fire") or "case 1" ("Distant Fire") 
          will be activated respectively. If "no flame" is detected; "case 2" will be activated ("No Fire").
   
  * About ARIES Development Boards: https://vegaprocessors.in/devboards/
   
  *** Flame Sensor ***
   
  * Connections:
  ---------------------------------
  | Flame Sensor  |  Aries Board  |
  ---------------------------------
  |     VCC       |     3.3V      |
  |     GND       |     GND       |
  |     AOUT      |     A0        |
  ---------------------------------
*/

#define PIN 0   // Analog pin 0
#define GREEN_LED 22
#define BLUE_LED 23
#define RED_LED 24

// lowest and highest sensor readings:
const int sensorMin = 0;     //  sensor minimum
const int sensorMax = 1647;  // sensor maximum

void setup()  {
  // initialize serial communication @ 9600 baud:
  Serial.begin(115200);  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}
void loop() {
  // read the sensor on analog pin:
  int sensorReading  = analogRead(PIN);
  // map the sensor range (four options):
  // ex: 'long  int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading,  sensorMin, sensorMax, 0, 3);

  // range value:
  switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Serial.println("** Close  Fire **");  // Indicate by Red Led
    digitalWrite(RED_LED, LOW);   
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    break;
  case 1:    // A fire between 1.5 - 3 feet away.
    Serial.println("**  Distant Fire **");  // Indicate by Blue Led
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    break;
  case 2:    // No fire detected.
    Serial.println("No  Fire");  // Indicate by Green Led
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    break;
  }
  delay(1);  // delay between reads
}
