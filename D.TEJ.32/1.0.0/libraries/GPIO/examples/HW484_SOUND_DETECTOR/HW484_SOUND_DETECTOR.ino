/*
  @file HW484_SOUND_DETECTOR.ino
  @brief microphone sound sensor that detects sound
  @detail A microphone sensor will detect the sound intensity of your surroundings 
          and will light up an LED if the sound intensity is above a certain threshold.

   Aries Board pinout: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf
   Arduino code Reference: https://randomnerdtutorials.com/guide-for-microphone-sound-sensor-with-arduino/
   
   *** HW484 V0.2 ***
   Connections:
   HW484        Aries Board
   GND        -   GND
   D0         -   GPIO-7
   VCC (+)    -   3.3V
   A0         -   A0

  Note: That example outputs 1, if the sound levels are above a certain threshold, and 0, if they are below.
  If you are always getting 1, it means that your threshold is too low.
  You need to adjust the threshold of your sensor by rotating the potentiometer at the back.
  One LED indicates the sensor is being powered, and the other indicates the digital output. 
  So, if you are always getting 1, the two LEDs on the sensor are lit. If you get 0, the second LED should be off.
  Alternatively, if your sensor has an analog output pin, you can read that pin instead, using the analogRead() function. 
  You’ll get varying values between 0 and 255 depending on the sound intensity.

  You can either use external LED using any GPIO pins available in aries board, or can use internal LEDs present.
*/

int ledPin=22;    //Green internal LED 
int sensorPin=7;  // connect D0 pin of the Sensor to GPIO-7
boolean val =0;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin (115200);
}
  
void loop (){
  val =digitalRead(sensorPin);
  Serial.println (val);

   // int sensorValue = analogRead(A0);
  //Serial.print("Value: ");
  // Serial.println(sensorValue);
 
  // when the sensor detects a signal above the threshold value, LED flashes
  if (val==HIGH) {
    digitalWrite(ledPin, LOW);
  }
  else {
    digitalWrite(ledPin, HIGH);
  }
}
