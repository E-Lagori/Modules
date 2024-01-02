/*
  @file IR_Tx_Rx.ino
  @brief Interfacing IR receiver and transmitter LED with ARIES v2 
  @detail This demo reads values from both IR transmitter and receiver interfaces and display on serial monitor.
 
   Refrence aries board: https://www.youtube.com/watch?v=_mOF1JXo1DU&t=182s
   
   ***IR Rx and Tx LED  ***
  
   Connections:
   IR Tx Sensor     Aries Board
    (+)        -   3.3V & 10 ohm resistor
    (-)        -   GND
   
   IR Rx Sensor     Aries Board
    (+)        -   A0 & 10K ohm 
    (-)        -   3.3V
   
10 ohm Resistor         Aries Board
    one end        -   IR Tx anode (+ve)
    Other end      -   3.3V
   
10K ohm Resisitor      Aries Board
    one end        -   A0 & IR Rx anode(+ve)
   Other end       -   GND   
  
   Note: Threshold is set based on the IR LED readings  given by analogRead function
*/

 
int ifRead;
#define analogPin A0  //Connect IR LED Reciver anode to A0
#define ledPin 22     //Internal LED


void setup() {
 Serial.begin(115200);
 pinMode(analogPin,INPUT);

}

void loop() {
ifRead = analogRead(A0);
//Serial.println(ifRead);   //Uncomment this line if you want to see IR LED readings
if(ifRead > 900){
Serial.println("Object detected");
digitalWrite(ledPin,LOW);
}
else {
digitalWrite(ledPin,HIGH);
}
delay(1);
}
