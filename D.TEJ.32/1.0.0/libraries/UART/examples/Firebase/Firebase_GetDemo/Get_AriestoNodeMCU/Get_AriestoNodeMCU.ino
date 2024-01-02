/*
 * @file2 Get_AriestoNodeMCU.ino
 * @brief NodeMCU Module communicates with the ARIES v2 Board via the UART Protocol 
 * @detail In this program, NodeMCU allows ARIES to connect to a Wi-Fi network and control the ARIES board internal LED from the Firebase cloud
 * 
 * Note: Check and upload the "Get_NodeMCUtoFirebase.ino" file in NodeMCU module, before uploading this code in ARIES v2
 * 
 * Burn this code to ARIES v2
 * Go to Tools -> Board -> VEGA processor ARIES Boards: -> ARIES v2
 * Go to Tools -> Programmer and select VEGA XMODEM
 * Go to tools -> Port and select appropriate port
 * 
 * Reference aries board: https://vegaprocessors.in/blog/esp8266-wifi-module-with-thejas-soc/
 * ESP8266 Pinout: https://components101.com/development-boards/nodemcu-esp8266-pinout-features-and-datasheet
 * Firebase : https://console.firebase.google.com/
 * 
 * 
 * Required Libraries : ArduinoJson (Version (5.13.2))
 *                      firebase-arduino (Github - https://github.com/FirebaseExtended/firebase-arduino ) 
 *                      
 * Required NodeMCU Package json link: https://arduino.esp8266.com/stable/package_esp8266com_index.json
 * Note: Install Version 2.7.4 of NodeMCU board from Tools-> Board Manager for this code to work
 * 
 * 
 * *** NodeMCU Module ***
 * Connections:
 * NodeMCU        Aries Board
 * 3.3           -   3.3V
 * GND           -   GND
 * D7 (RXD)      -   TX1
 * D8 (TXD)      -   RX1
 * 
 * ***Note: Check the GetDemo_NodeMCUtoFirebase.ino file  also before uploading this code
 *         
 * Steps to do in Firebase cloud platform:
 * 1) Visit https://console.firebase.google.com/ and login or create an account if you do not already have.
 * 2) click on "Go to Console" 
 * 3) Click on "Add Project" and give any project name for your project ( Example project name - RandomData)
 * 4) Click on Continue -> Continue
 * 5) Select default account for Firebase and Click on "Create Project"
 * 6) Click on "Continue" -> Continue
 * 7) Click on Build -> Real time Database -> Create Database
 * 8) Click on Next -> Start in Test Mode
 *    Note: If you  selected start in Locked mode then you need to change the rules of database to false for working, after creating the data base.
 * 9) You can see the url required for this project on the top of your database. Copy this url for future use
 * 10) Go to Project Overview -> Project Settings -> Service accounts -> Database Secrets, to copy the Database key
 * 11) Check the Post_NodeMCUtoFirebase.ino file  also before uploading the code
 * 12) Upload the "PostDemo_NodeMCUtoFirebase.ino" file in NodeMCU module, before uploading this code in ARIES v2
 * Upload the below code to ARIES v2 by connecting USB to ARIES v2 and change the LED_STATUS from Firebase cloud to see the output
 *      
*/


#include <UARTClass.h>
#include <sprintf.h>

#define led  LED_BUILTIN

UARTClass esp(1);                       //NodeMCU connecte to UART-1 of ARIES v2

void send_string(const char* str) {
  while (*str != '\0') {
   esp.write(*str);
    if (*str == '\n') {
     esp.write('\r');
    }
    str++;
  }
}

void receive_string(char* str) {
  char data;
 // int i = 0;
  while (1) {
    if (esp.available() > 0) {
      data = esp.read();
      *str = data;
      str++;
      if (data == '\n') {
        *str = '\r';
        *(str + 1) = '\0';
        break;
      }
    }
  }
}


void setup() {
  Serial.begin(115200);
  esp.begin(9600);
  pinMode(22,OUTPUT);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  Serial.println("\nSetting up the Device");
  send_string("H \n");
}

void loop() {
  char str[100] = {0,};
 // char sensorValue[50] = {0,};
  receive_string(str);
  Serial.print("command str: ");
  Serial.println(str);
  
  if (strncmp(str, "Start", 2) == 0) {
   
    send_string("LED_ON\n");
  }  
    
  else if(strncmp(str,"Send",2)==0){
    receive_string(str);
     Serial.print("Send str: ");
    Serial.println(str);
    
    if(strncmp(str,"ON",2)==0)
    digitalWrite(led,LOW);
    if(strncmp(str,"OFF",2)==0)
    digitalWrite(led,HIGH);
  }
  else {
    send_string("error \n");
  }
  Serial.println("done !!");
  Serial.println();
}
