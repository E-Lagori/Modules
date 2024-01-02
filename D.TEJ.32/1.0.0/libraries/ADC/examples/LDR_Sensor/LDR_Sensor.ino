/*
  @file LDR_Sensor.ino
  @brief Interfacing LDR sensor with VEGA ARIES Boards
  @detail This demo read the LDR value and turns LED ON when LDR senses darkness.

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/interfacing-ldr-sensor-to-vega-aries-boards/

  *** Optical Photosensitive LDR Sensor(LM393)  ***
  Connections:
    LDR       Aries Board
    VCC      -   3.3V
    GND      -   GND
    A0/OUT   -   A0
    D0       -   Not Required
*/

#define LEDPIN 22 // Green LED is internally connected to GPIO-22
#define LDRPIN A0 // analog pin 0

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200); 
  pinMode(LEDPIN, OUTPUT); // initialize digital pin 22 as an output.
}

// the loop function runs over and over again forever
void loop() {
  // higher the light intensity, lower the resistance
  int ldrStatus = analogRead(LDRPIN); // resitance value 

  if (ldrStatus >= 1200)
  {
    digitalWrite(LEDPIN, LOW); // if LDR senses darkness, then make led pin low that means led will glow
    Serial.print("Darkness over here,turn on the LED : ");
    Serial.println(ldrStatus);
  }
  else
  {
    digitalWrite(LEDPIN, HIGH); // if LDR senses enough light, then make led pin high that means led will turn off
    Serial.print("There is sufficeint light , turn off the LED : ");
    Serial.println(ldrStatus);
  }
}
