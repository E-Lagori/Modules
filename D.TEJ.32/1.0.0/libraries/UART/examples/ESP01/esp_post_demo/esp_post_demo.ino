/*
  @file esp8266_post_demo.ino
  @brief ESP8266 Module communicates with the ARIES v2 Board via the UART Protocol
  @detail ESP8266 allows ARIES to connect to a Wi-Fi network and push data of any sensor to adafruit block

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/sending-data-to-adafruit-iot-cloud-platform-using-aries-v3-board-and-esp8266-wi-fi-module/
    Adafruit IO : https://io.adafruit.com/
   
  *** ESP8266 WiFi Module ***
  Connections:
   ESP8266     Aries Board
   VCC      -   3.3V
   GND      -   GND
   RXD      -   TX1
   TXD      -   RX1
*/

#include <esp8266.h>

ESP8266Class esp8266(1); // UART-1

char * AP = "HOTSPOT-NAME";       // Add your mobile hotspot name here
char * PASS = "HOTSPOT-PASSWORD"; // Add password
char * HOST = "io.adafruit.com";
int PORT=80;
char * KEY = "ADAFRUIT-KEY";   // Add Adafruit Key here
char * URL = "/api/v2/<ADAFRUIT-USERNAME>/feeds/<FEED-NAME>/data";  // Add URL of your feed here


int countTrueCommand;
int countTimeCommand; 
boolean found = false; 

int valSensor = 1;
char atcommand[250] = {0,};
char data[250] = {0,};
char payload[250] = {0,};
int timeout = 3;

int getSensorData(){
   return random(1000); // returns random integer data from 0 to 10000
}

void sendCommand(char * command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  { 
    esp8266.println(command);//at+cipsend   
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }  
    countTimeCommand++;
  }  
  if(found == true)
  {
    Serial.println("-> OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }  
  if(found == false)
  {
    Serial.println("-> Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  } 
  found = false;
 }

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize both (UART-0 & UART-1) serial communication at 115200 bits per second:
  Serial.begin(115200);
  esp8266.begin(115200);
  delay(2000);

  countTrueCommand=0;
  countTimeCommand=0;
  
  // start communicating with ESP8266 module using AT commands
  sendCommand("AT",5,"OK");  // the basic command that tests the AT start up. If the AT start up is successful, then the response is OK.
  sendCommand("AT+CWMODE=1",5,"OK");  // to set the WiFi Mode of operation (1 = Station mode i.e ESP connects to the router as a client.)
  memset(atcommand,0,250);
  sprintf(atcommand,"AT+CWJAP=\"%s\",\"%s\"",AP,PASS);   // This command is to connect to an Access Point (like a router).
  sendCommand(atcommand,2,"OK");
}

// the loop function runs over and over again forever
void loop() { 
  sendCommand("AT+CIPMUX=1",3,"OK");  // This AT Command is used to enable or disable multiple TCP Connections. (0: Single connection, 1: Multiple connections)
  memset(atcommand,0,250);
  sprintf(atcommand,"AT+CIPSTART=0,\"TCP\",\"%s\",%d", HOST, PORT);    // to establish one of the three connections: TCP, UDP or SSL. 
  sendCommand(atcommand,3,"OK");
  
  memset(atcommand,0,250);
  memset(data,0,250);
  sprintf(data,"{\"value\": %d}",getSensorData());
  sprintf(payload,"POST %s HTTP/1.1\r\nHost: %s\r\nContent-Type: application/json\r\nX-AIO-Key: %s\r\nContent-Length: %d\r\n\r\n%s",URL, HOST, KEY, strlen(data),data);
  sprintf(atcommand,"AT+CIPSEND=0,%d",strlen(payload));  //  to start sending data in transparent transmission mode.
  sendCommand(atcommand,4,">");
  esp8266.println(payload);
  countTrueCommand++;
  delay(2000);

  sendCommand("AT+CIPCLOSE=0",5,"OK");  // Closes TCP/UDP/SSL connection 
}