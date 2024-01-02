/*
  @file   LED_Series.ino
  @brief  RGB LED
  @detail Various coloured LED will glow and color name will display on Serial Monitor
 
  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/how-to-make-color-combinations-with-rgb-led-on-aries-v3-0-board/
 
  Note: RGB LED will be in "ON" state for a digital input "0" & in "OFF" state for a digital input "1".
        * GPIO pin-22 - Green LED 
        * GPIO pin-23 - Blue LED
        * GPIO pin-24 - Red LED
*/

#define GREEN_LED     22
#define BLUE_LED      23
#define RED_LED       24

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  // all possible combinations of base RGB colors
  digitalWrite(GREEN_LED, LOW);  // Green LED 
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, HIGH);
  Serial.println("Green");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);  // Blue LED 
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  Serial.println("Blue");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);  // Red LED 
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  Serial.println("Red");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, LOW);  // Green + Blue = Cyan 
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  Serial.println("Cyan");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, HIGH);  // Blue + Red = Purple
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  Serial.println("Purple");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, LOW);  // Green + RED = Lime
  digitalWrite(BLUE_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  Serial.println("Lime");
  Serial.println("-----------");
  delay(1000);
  digitalWrite(GREEN_LED, LOW);  // Green + Blue + Red = white
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  Serial.println("White");
  Serial.println("-----------");
  delay(1000);
}
