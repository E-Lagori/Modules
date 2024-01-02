/*
  @file JoyStick.ino
  @brief This program demonstrates how to Use a Joystick with Serial Monitor 
  @detail Controlling joystick in verticao and horizontal directions

   Reference arduino board:https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-joystick-with-serial-monitor-1f04f0
   Reference aries board:https://vegaprocessors.in/blog/hw-504-joystick-with-aries-v2-0-board/

   
   *** HW504 JoyStick ***
   Connections:
   JoyStick     Aries Board
    VCC     -    5V
    GND     -    GND
    VRx     -    A0
    VRy     -    A1
    SW      -    GPIO-0
*/


int VRx = A0;   //connect VRx pin of JoyStick to analog pin A0
int VRy = A1;   // connect VRy pin of JoyStick to analog pin A0
int SW = 2;   // connect SW pin of JoyStick to GPIO-0

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

void setup() {
  Serial.begin(115200); 
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  
}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  delay(100);
  
}
