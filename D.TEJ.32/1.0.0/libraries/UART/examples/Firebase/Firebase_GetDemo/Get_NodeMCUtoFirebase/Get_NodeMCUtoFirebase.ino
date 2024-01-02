/*
 * @file1 Get_NodeMCUtoFirebase.ino
 * @brief NodeMCU Module communicates with the ARIES v2 Board via the UART Protocol 
 * @detail In this program, NodeMCU allows ARIES to connect to a Wi-Fi network and control the ARIES board internal LED from the Firebase cloud
 * 
 * 
 * Reference aries board: https://vegaprocessors.in/blog/esp8266-wifi-module-with-thejas-soc/
 * ESP8266 Pinout: https://components101.com/development-boards/nodemcu-esp8266-pinout-features-and-datasheet
 * Firebase : https://console.firebase.google.com/
 * 
 * 
 * Required Libraries : ArduinoJson (Version (5.13.2))
 *                      firebase-arduino (Github - https://github.com/FirebaseExtended/firebase-arduino ) 
 * 
 * NodeMCU Package json link: https://arduino.esp8266.com/stable/package_esp8266com_index.json
 * Note: Install Version 2.7.4 of NodeMCU board from Tools-> Board Manager for this code to work
 * 
 * Burn this code to NodeMCUESP8266
 * Go to Tools -> Board -> ESP8266 Boards(2.7.4) -> NodeMCU 0.9 (ESP-12 Module) 
 * Go to Tools -> Port -> Select appropriate port
 * 
 * 
 * *** NodeMCU Module ***
 * Connections:
 * NodeMCU          Aries Board
 * 3.3           -   3.3V
 * GND           -   GND
 * D7 (RXD)      -   TX1
 * D8 (TXD)      -   RX1
 * 
 *         
 * Steps to do in Firebase cloud platform:
 * 1) Visit https://console.firebase.google.com/ and login or create an account if you do not already have.
 * 2) click on "Go to Console" 
 * 3) Click on "Add Project" and give any project name for your project ( Example project name - RandomData)
 * 4) Click on Continue 
 * 5) Select "default account for Firebase" and Click on "Create Project"
 * 6) Click on "Continue" -> Continue
 * 7) Click on Build -> Real time Database -> Create Database
 * 8) Click on Next -> Start in Test Mode
 *    Note: If you  selected start in Locked mode then,after creating the data base, you need to change the rules of database to "false" for working, 
 * 9) You can see the url required for this project on the top of your database. Copy this url for future use
 * 10) Go to Project Overview -> Project Settings -> Service accounts -> Database Secrets, to copy the Database secret key
 * 11) Turn on your hotspot before uploading the code
 * 
 * Steps to do in code:
 * 1) Replace FIREBASE_HOST with your Database url by removing https:// from the url
 * 2) Replace FIREBASE_AUTH with your Firebase secret key 
 * 3) Replace WIFI_SSID with your Wi-Fi hotspot username
 * 4) Replace WIFI_PASSWORD with your Wi-Fi hotspot password
 * 5) Check and update the latest Fingerprint inside  "kFirebaseFingerprint[]", which is available in FirebaseHttpClient.h. Refer the below link for details:
 *     https://stackoverflow.com/questions/53068413/unable-to-connect-nodemcu-with-firebase-as-console-shows-setting-number-failed 
 *     Latest fingerprint available as on 24/July/2023 -> BA:24:75:4D:AB:45:63:9E:01:8D:54:6F:2C:D9:E9:30:20:EC:DC:FF
 *    
 * 
 * 
 * After completing above steps, connect NodeMCU and ARIES v2, Connect USB to NODEMCU and upload this code to NodeMCU 
 * 
 * Example Scenario:
 * Firebase project Name: RandomData
 * Firebase project url: https://randomdata-55fed-default-rtdb.firebaseio.com/
 * Firebase Secret key : dIr2SgAwI3dHlTkPdZ5VCgN6YDSgUXGP9LMtpPdQ
 * Wi-Fi Username : redmi
 * Wi-Fi password : 123456789
 *      
*/


#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<SoftwareSerial.h> //Included SoftwareSerial Library


#define FIREBASE_HOST "randomdata-55fed-default-rtdb.firebaseio.com"    // Replace with the project name address from firebase id
#define FIREBASE_AUTH "dIr2SgAwI3dHlTkPdZ5VCgN6YDSgUXGP9LMtpPdQ"       // Replace with the secret key generated from firebase
#define WIFI_SSID "redmi"                                             // Replace with your Wi-Fi hotspot username                    
#define WIFI_PASSWORD "123456789"                                     //Replace with your Wi-Fi hotspot password

SoftwareSerial NodeMCU(13, 15);                                      //D7(GPIO-13/RX) && D8(GPIO-15/TX) pins of nodemcu, nodemcu rx - ARIES tx, nodemcu tx - ARIES rx
char data, arr[15], a = 0;
int indx = 0;
char flag = 0;

String fireStatus = "";                                            // led status received from firebase
void setup()
{
  Serial.begin(9600);
  NodeMCU.begin(9600);                                            // initialization
  Serial.println("tx rx begin");


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);    // connect to firebase
  Firebase.setString("LED_STATUS", "OFF");      //send initial string of led status
}

void loop()
{

  //..... communication between nodemcu and vegaboard....

  if (NodeMCU.available() > 0) // to check the status of vega
  {
    if (flag == 0)
    {
      read_RX();
      flag = 1;
    }
    delay(500);
    NodeMCU.write("Start\n"); // initial signal to start data txn


    read_RX(); // initial read command

    Serial.println(arr); // string
    Firebase.setString("LED Start", arr); // updated in firebase         ......communication to firebase from nodemcu............
   
    if (Firebase.failed())
    {
      Serial.print("setting /message failed:");
      Serial.println(Firebase.error());
      return;
    }

    Serial.println("ok");

    //communication from firebase to nodemcu............

     NodeMCU.write("Send \n");
     fireStatus = Firebase.getString("LED_STATUS");                                      // get ld status input from firebase
    
    if (fireStatus == "ON")
    { // compare the input of led status received from firebase
      NodeMCU.write("ON \n");
    }
    else if (fireStatus == "OFF")
    { // compare the input of led status received from firebase
      NodeMCU.write("OFF \n");
    }
    else
    {
      NodeMCU.write("Command Error! Please send ON/OFF");
    }       
  }
}

char read_RX()
{
  if (NodeMCU.available() > 0)
  {
    do {
      data = NodeMCU.read();
      arr[indx] = data;
      indx++;
      delay(5);
    } 
    while (data != '\n');

    arr[indx - 1] = '\0';
    indx = 0;
  }
}
