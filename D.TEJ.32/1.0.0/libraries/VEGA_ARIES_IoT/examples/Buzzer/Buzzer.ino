/*
 @file   Buzzer.ino
 @brief  Continuous beeping sound using Piezo Buzzer
 @detail Setting selected PWM pin with small delay in between to create beeping sound

 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1 
 * 
*/

#define buzzer 7  //buzzer connected to PWM pin 7
#define period 2500

void setup() {
  // put your setup code here, to run once:
  delay(2000);
  Serial.begin(115200);

}

void loop() {
   #if defined (VEGA_ARIES_IOT)
   
  // put your main code here, to run repeatedly:
 tone(buzzer,period);
 delay(1000);

 analogWrite(buzzer, 0);
 delay(500);

  #else
  Serial.println("Choose the correct board! " );
  #endif 
}
