/*
  @file RGB_LED_GPIO.ino
  @brief Simple LED Application
  @detail Turning LEDs ON and OFF in simple serial pattern (in loop)

   Aries Board pinout: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf
   Arduino code Reference: https://create.arduino.cc/projecthub/muhammad-aqib/arduino-rgb-led-tutorial-fc003e
   
   *** RGB LED ***
   Connections:
   LED        Aries Board
   GND      -   GND/3.3V
   R        -   GPIO0
   B        -   GPIO1
   G        -   GPIO2

Note: You cannot distinguish between the common cathode and common anode type by just looking at the RGB led because both look same. 
You will have to make the connections to see that either it is common cathode or common anode.
The RGB led has one big lead than the other leads. In the common cathode case, it will be connected to GND 
and in the common anode case; it will be connected to 3.3V.
*/

int red_light_pin= 0;
int green_light_pin = 2;
int blue_light_pin = 1;
void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}
void loop() {
  RGB_color(255, 0, 0); // Red
  delay(1000);
  RGB_color(0, 255, 0); // Green
  delay(1000);
  RGB_color(0, 0, 255); // Blue
  delay(1000);
  RGB_color(255, 255, 125); // Raspberry
  delay(1000);
  RGB_color(0, 255, 255); // Cyan
  delay(1000);
  RGB_color(255, 0, 255); // Magenta
  delay(1000);
  RGB_color(255, 255, 0); // Yellow
  delay(1000);
  RGB_color(255, 255, 255); // White
  delay(1000);
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  digitalWrite(red_light_pin, red_light_value);
  digitalWrite(green_light_pin, green_light_value);
  digitalWrite(blue_light_pin, blue_light_value);
}
