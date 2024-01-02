/*
  @file Vibration_Motor_Sensor.ino
  @brief Interfacing Vibration Motor Sensor to ARIES V2 Board
  @detail In this demo, Motor will vibrate for one second and then stops, this process is repeated.
   
   Reference aries board: https://vegaprocessors.in/blog/interfacing-8x8-led-dot-matrix-to-aries-v2-board/
   
   *** Vibration_Motor_Sensor ***
   Connections:
   Vibration Motor      Aries Board
   VCC                -   3.3V
   GND                -   GND
   SIG                -   GPIO-0
*/


int Pin = 0;    // Connect SIG pin of vibration motor to GPIO 0 of aries board 

void setup()  {
    pinMode( Pin, OUTPUT );
}

void loop()  {
    digitalWrite(Pin, HIGH);
    delay(1000);

    digitalWrite(Pin, LOW);
    delay(1000);
}
