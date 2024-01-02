/*
 @file   DIP_Switch.ino
 @brief  contains routines for GPIO interface of DIP Switches
 @detail by arranging the DIP switches respective LED will glow and switches status will display on Serial monitor.  

 Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/how-to-make-use-of-in-built-dip-switches-on-aries-v2-0-board/
 
 Note: In this demo we are using built-in Dip Switches
      * GPIO pin-22 - Green LED 
      * GPIO pin-23 - Blue LED
      * GPIO pin-24 - Red LED
      * RGB LED will be in "ON" state for a digital input "0" & in "OFF" state for a digital input "1".
      * GPIO pin-16 - DIP_SW-1
      * GPIO pin-17 - DIP_SW-2
      * ARIES v2 has two built-in Dip Switches.
*/

#define GREEN_LED     22
#define BLUE_LED      23
#define RED_LED       24
#define DIP_SW1       16
#define DIP_SW2       17

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  delay(1000);

  pinMode(DIP_SW1, INPUT);  // initializing GPIO-16 as INPUT
  pinMode(DIP_SW2, INPUT);  // initializing GPIO-17 as INPUT

  Serial.println("-----------------------------------|");
  Serial.println("| SWITCH-1 | SWITCH-2 | LED STATUS |");  
  Serial.println("-----------------------------------|");
  Serial.println("|     0    |    0     |   GREEN    |");
  Serial.println("|     0    |    1     |    BLUE    |");
  Serial.println("|     1    |    0     |    RED     |");
  Serial.println("|     1    |    1     |   PURPLE   |");
  Serial.println("------------------------------------");
}

// the loop function runs over and over again forever
void loop() {
  // try all the possible combinations of DIP switches
  Serial.println("-----------------------");
  Serial.println("| SWITCH-1 | SWITCH-2 |");  
  Serial.println("-----------------------");
  Serial.print("|    ");Serial.print(digitalRead(DIP_SW1));Serial.print("     ");
  Serial.print("|    ");Serial.print(digitalRead(DIP_SW2));Serial.println("     |");
  Serial.println("-----------------------");
  Serial.println();Serial.println();
  delay(1000);

  if((digitalRead(DIP_SW1) || digitalRead(DIP_SW2)) == 0) {
    digitalWrite(GREEN_LED, LOW);  // Green LED will ON
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
  }
  else if((digitalRead(DIP_SW1) == LOW) && (digitalRead(DIP_SW2) == HIGH)) {
    digitalWrite(GREEN_LED, HIGH); // Blue LED will ON
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
  else if((digitalRead(DIP_SW1) == HIGH) && (digitalRead(DIP_SW2) == LOW)) {
    digitalWrite(GREEN_LED, HIGH); // Red LED will ON
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  }
  else {
    digitalWrite(GREEN_LED, HIGH); // Red + Blue = Purple
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
}
