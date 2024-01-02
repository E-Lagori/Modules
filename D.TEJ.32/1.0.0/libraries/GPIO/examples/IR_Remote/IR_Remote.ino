/*
  @file IR_Remote.ino
  @brief Interfacing IR receiver and Remote with ARIES v2 
  @detail When you press the key in the IR remote, corresponding values will be displayed in the Serial monitor
 
   Refrence arduino code: https://www.instructables.com/Arduino-IR-Remote-Control/
   Reference aries board: https://vegaprocessors.in/blog/interfacing-8x8-led-dot-matrix-to-aries-v2-board/

   Libraries used:
   *  Library Name    : IRremote (Download from gitlab)
   *  Library Download Link: https://gitlab.com/riscv-vega/aries_libraries/-/blob/main/IRremote.zip  

   ***Note: Inorder to add the Library downloaded from gitlab: 
   Click on Sketch -> Include Library -> Add .ZIP library -> Select the zip file you downloaded from Gitlab -> Click OK.

   ***IR Rx LED***
   Connections:
   IR Rx Sensor    Aries Board
    (+)        -   GPIO-11 & 10K ohm resistor
    (-)        -   3.3V
   
10K ohm Resisitor     Aries Board
   One end        -   GPIO-11 & IR Rx anode(+ve)
   Other end      -   GND     
*/

#include <IRremote.h>
 
int RECV_PIN = 11; //Connect +ve of IR LED & one end of 10K ohm resistor to  GPIO-11 in Aries board

#define code0  2334761289
#define code1  1420882249 
#define code2  1860289993 
#define code3  1335428721  
#define code4  3967547069
#define code5  197441045
#define code6  1891233129
#define code7  2515727689 
#define code8  1649260425
#define code9  1390076061
#define codeOK     433220201
#define codeLeft   1253364873
#define codeRight  969570077
#define codeTop    1020490281
#define codeBottom 2173273225
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 
void setup()
{
  Serial.begin(115200);   
  irrecv.enableIRIn();  
}
 
void loop() {
  if (irrecv.decode(&results)) {
    unsigned int value = results.value;
    switch(value) {
          case code1:
            Serial.println("Key 1 is pressed"); 
          break; 
          case code2:
            Serial.println("Key 2 is pressed"); 
          break; 
          case code3:
            Serial.println("Key 3 is pressed"); 
          break; 
          case code4:
            Serial.println("Key 4 is pressed"); 
          break; 
          case code5:
            Serial.println("Key 5 is pressed"); 
          break; 
          case code6:
            Serial.println("Key 6 is pressed"); 
          break; 
          case code7:
            Serial.println("Key 7 is pressed"); 
          break; 
          case code8:
            Serial.println("Key 8 is pressed"); 
          break; 
          case code9:
            Serial.println("Key 9 is pressed"); 
          break; 
          case code0:
            Serial.println("Key 0 is pressed"); 
          break; 
          case codeOK:
            Serial.println("OK is pressed"); 
          break; 
          case codeLeft:
            Serial.println("Left Key"); 
          break; 
          case codeRight:
            Serial.println("Right Key"); 
          break; 
          case codeTop:
            Serial.println("Top Key"); 
          break; 
          case codeBottom:
            Serial.println("Bottom Key"); 
          break;              
    }
   // Serial.println(value); // you can comment this line
    irrecv.resume(); // Receive the next value
  }
}
