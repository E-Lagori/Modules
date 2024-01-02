/*
  @file 5V_2Channel_Relay.ino
  @brief Simple DC relay application
  @detail connecting your Aries to a 2 Channel relay module and using your sketch to control the switches.

   Reference Arduino code: https://www.instructables.com/Arduino-2-Channel-Relay/ 
   Reference Aries board: https://vegaprocessors.in/blog/one-channel-relay-module-with-aries-v2-board/
   
   *** DC RELAY ***
   Connections:
   Relay     Aries Board
   VCC      -   5V
   JD-VCC   -   5V
   GND      -   GND
   IN1      -   GPIO0
   IN2      -   GPIO1
*/



int RELAY1 = 0;
int RELAY2 = 1;
int LED1 = 22;
int LED2 = 23;
int delayValue = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY1, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(LED2, OUTPUT);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  Serial.begin(115200);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  digitalWrite(RELAY1, LOW);
  digitalWrite(LED1, HIGH);
  Serial.println("RELAY1 ON");
  delay(delayValue);
 
  digitalWrite(RELAY1, HIGH);
  digitalWrite(LED1, LOW);
  Serial.println("RELAY1 OFF");
//  delay(delayValue);

  digitalWrite(RELAY2, LOW);
  digitalWrite(LED2, HIGH);
  Serial.println("RELAY2 ON");
  delay(delayValue);
  
  digitalWrite(RELAY2, HIGH);
  digitalWrite(LED2, LOW);
  Serial.println("RELAY2 OFF");
//  delay(delayValue);
}
