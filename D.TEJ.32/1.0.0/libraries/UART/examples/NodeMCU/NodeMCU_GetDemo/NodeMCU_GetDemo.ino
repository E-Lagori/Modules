/*
  @file NodeMCU_Get_Demo.ino
  @brief NodeMCU Module communicates with the ARIES V2 Board via the UART Protocol
  @detail NodeMCU allows ARIES to connect to a Wi-Fi network and get data from adafruit to ON/OFF the RGB LED on Aries board

   Reference aries board: https://vegaprocessors.in/blog/esp8266-wifi-module-with-thejas-soc/
   ESP8266 Pinout: https://raw.githubusercontent.com/AchimPieters/ESP8266-12F---Power-Mode/master/ESP8266_01X.jpg
   Adafruit IO : https://io.adafruit.com/
   
   *** NodeMCU Module ***
   Connections:
   NodeMCU     Aries Board
   VCC      -   3.3V
   GND      -   GND
   RXD      -   TX1
   TXD      -   RX1
*/

#include <esp8266.h>

ESP8266Class esp8266(1);

char * AP="CPH1609";    // Add network name here
char * PASS= "123456789";     // Add password
char * HOST="io.adafruit.com";
int PORT=80;
char * URL="/api/v2/mydhily/feeds/mculed/data/last?x-aio-key=aio_UBnp43gUiHdyCK4mMgkXVmKkZ2hM";  // Add URL of your feeds along with key

int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
boolean ledon = false; 
int valSensor = 1;
char atcommand[250]={0,};
char data[250]={0,};

int getSensorData(){
  return 100; // Replace with 
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

 int checkButtonStatus()
 {
    int i=500;
    while(i){
       while(esp8266.available())
       {
          Serial.print(char(esp8266.read()));
       }
       i--;
    }
 }


void setup() {
  delay(2000);
  countTrueCommand=0;
  countTimeCommand=0;
  Serial.begin(115200);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");          // the basic command that tests the AT start up. If the AT start up is successful, then the response is OK.
  sendCommand("AT+CWMODE=1",5,"OK");  // to set the WiFi Mode of operation (1 = Station mode i.e ESP connects to the router as a client.)
  memset(atcommand,0,250);
  sprintf(atcommand,"AT+CWJAP=\"%s\",\"%s\"",AP,PASS);  // This command is to connect to an Access Point (like a router).
  sendCommand(atcommand,2,"OK");
  ledon=false;
}
int timeout=3;
void loop() { 
  sendCommand("AT+CIPMUX=1",3,"OK");  // This AT Command is used to enable or disable multiple TCP Connections. (0: Single connection, 1: Multiple connections)
  memset(atcommand,0,250);
  sprintf(atcommand,"AT+CIPSTART=0,\"TCP\",\"%s\",%d", HOST, PORT);   // to establish one of the three connections: TCP, UDP or SSL. 
  sendCommand(atcommand,3,"OK");
  memset(atcommand,0,250);
  sprintf(data,"GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", URL, HOST);
  sprintf(atcommand,"AT+CIPSEND=0,%d",strlen(data));                  //  to start sending data in transparent transmission mode.
  sendCommand(atcommand,4,">");
  esp8266.println(data);
  countTrueCommand++; 
    
  timeout=2;
  while(timeout)
  { 
    if(esp8266.find("\"value\":\"1\""))
    {
        Serial.println("LED ON>>>>>>>>>");
        ledon=true;
        break;  
    }  
    else if(esp8266.find("\"value\":\"0\""))
    {
        Serial.println("LED OFF>>>>>>>>>");
        ledon=false;  
        break;
    }
    
    //Serial.println(timeout);
    timeout--;   
  }  
  
  if(ledon){
    digitalWrite(24,LOW);
    digitalWrite(22,LOW);
    digitalWrite(23,LOW);
  }
  else{
    digitalWrite(24,HIGH);
    digitalWrite(22,HIGH);
    digitalWrite(23,HIGH);
  }
  
  sendCommand("AT+CIPCLOSE=0",5,"OK");             // Closes TCP/UDP/SSL connection 
  delay(500);
}
