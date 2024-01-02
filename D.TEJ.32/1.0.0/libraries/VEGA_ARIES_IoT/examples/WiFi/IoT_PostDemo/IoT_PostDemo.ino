/*
 @file   IoT_PostDemo.ino
 @brief  Wi-Fi NINA Module communicates with the ARIES IoT v1 Board via the SPI Protocol
 @detail Wi-Fi NINA allows ARIES to connect to a Wi-Fi network and push data of any sensor to adafruit block

 * Reference Arduino code: https://www.electronics-lab.com/project/getting-started-with-adafruit-io-iot-cloud-platform/
 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Required Libraries : VEGA_WiFiNINA (Version 1.0.1)
 *                      ArduinoJson   (Version 6.21.2)
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1
 * 
 * Steps to do in Adafruit cloud platform:
 * 1) Visit https://io.adafruit.com/ and login or create an account if you do not already have.
 * 2) Click the feeds button,select “create a new group”.
 * 3) Enter the name of the group and a description and click the create button. (example group Name = group)
 * 4) Click on the group you just created, when the new page opens, click on the action button again and select “Create a new feed“. (Example feed name -> temperature)
 * 6) select “create a new dashboard“ for creating the dashboard ( Example dashboard name -> temperature)
 * 7) Click on the dashboard you have created, it should open a new window. On the window, click on the “gear” Icon to start adding blocks (widgets) to the dashboard.
 * 8) Clicking on any block will enable you to set the properties of the block. Select the feed to whose data will be displayed on that block and hit the next button.
 * 9) Since no data has been uploaded to it yet, all values will be at zero.
 * 
 * Steps to do in the Code:
 * 1) Replace the values in SECRET_SSID in arduino_secrets.h file with your wi-Fi hotspot username
 * 2) Replace the values in SECRET_PASS in arduino_secrets.h file with your wi-Fi hotspot password
 * 3) Replace the values in IO_USERNAME (line 45) with your Adafruit username
 * 4) Replace the values in IO_GROUP (line 46) with your Adafruit group name
 * 5) Replace the values in IO_KEY (line 47) with your Adafruit group key
 * 6) Replace the values in feed1["key"] (line 168) with your Adafruit feed name
 * 
 * After completing above steps properly, run this code and output values will be displayed in the serial monitor and Adafruit dashboard created
 * 
*/

#include <ArduinoJson.h>  
#include <SPI.h>

/////////////////////////
#include <WiFiNINA.h>
#include "arduino_secrets.h"

#define IO_USERNAME "mydhily"   //Replace with your Adafruit username
#define IO_GROUP "group"        //Replace with your adafruit group name
#define IO_KEY "aio_UBnp43gUiHdyCK4mMgkXVmKkZ2hM"  //Replace with your Adafruit key


//These values are in the datasheet
#define RT0 10000   // Ω
#define B 3977      // K
//--------------------------------------

#define VCC 3.3    //Supply voltage
#define R 10000  //R=10KΩ

//Variables
float RT, VR, ln, TX, T0, VRT;

char ssid[] = SECRET_SSID;         // your network SSID (name)
char pass[] = SECRET_PASS;         // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;
char server[] = "io.adafruit.com"; // name address for Adafruit IOT Cloud

// Initialize the client library
WiFiClient client;
int state = 2;

unsigned long lastConnectionTime = 0;              // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 7000;       // delay between updates, in milliseconds

float _temperature = 0;

void setup() {
 delay(2000);
 Serial.begin(115200);
 #if defined (VEGA_ARIES_IOT)
  //while (!Serial); // wait for serial port to connect. Needed for native USB port only
 T0 = 25 + 273.15;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin

 connectToWIFI();

  #else
  Serial.println("Choose the correct board! " );
  #endif
}

void loop() {
  #if defined (VEGA_ARIES_IOT)
  
   httpRequest();
   if (state == 1) 
    {
      Serial.println("1");
    }
    else if (state == 0) 
    {
      Serial.println("0");
    }
    else
    {
       Serial.println(state);
    }

   // if 7 seconds have passed since your last connection,
  // then connect again and send data:
  //if (millis() - lastConnectionTime > postingInterval) 
  //{
  delay(1000);
    readSensors();
    httpRequest(); // send data to Cloud
 // }

  #else
  Serial.println("Choose the correct board! " );
  #endif
  
}

void readSensors()
{
  VRT = analogRead(A7);              //Thermistor connected in analog pin 7
  VRT = (3.30 / 4095.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX = TX - 273.15;                 //Conversion to Celsius

   _temperature =TX;
  Serial.print("Temperature : ");
  Serial.println(_temperature);
 delay(10); 

}

void httpRequest() 
{
/*
 * https://io.adafruit.com/api/docs/#operation/createGroupData
 * 
 * POST /{username}/groups/{group_key}/data
 * 
 * JSON:
 * 
{
  "location": {
    "lat": 0,
    "lon": 0,
    "ele": 0
  },
  "feeds": [
    {
      "key": "string",
      "value": "string"
    }
  ],
  "created_at": "string"
}
 */

  const size_t capacity = JSON_ARRAY_SIZE(3) + 3*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + 130;
  StaticJsonDocument<capacity> doc;

   // Add the "location" object
  JsonObject location = doc.createNestedObject("location");
  location["lat"] = 0;
  location["lon"] = 0;
  location["ele"] = 0;
  
  // Add the "feeds" array
  JsonArray feeds = doc.createNestedArray("feeds");
  JsonObject feed1 = feeds.createNestedObject();
  feed1["key"] = "temperature";           //Replace with your feed name
  feed1["value"] = _temperature;          //Temperature readings from thermistor
  
  // close any connection before send a new request.
  // This will free the socket on the Nina module
  client.stop();

  Serial.println("\nStarting connection to server...");
  if (client.connect(server, 80)) 
  {
    Serial.println("connected to server");
    
    // Make a HTTP request: sample API for group created: https://io.adafruit.com/api/v2/mydhily/groups/group
    client.print("POST /api/v2/");   
    client.print(IO_USERNAME); 
    client.print("/groups/");   
    client.print(IO_GROUP);
    client.println("/data HTTP/1.1");
   
    client.println("Host: io.adafruit.com");  
    client.println("Connection: close");  
    client.print("Content-Length: ");  
    client.println(measureJson(doc));  
    client.println("Content-Type: application/json");  
    client.println("X-AIO-Key: " IO_KEY); 

    // Terminate headers with a blank line
    client.println();
    // Send JSON document in body
    serializeJson(doc, client);

    // note the time that the connection was made:
    lastConnectionTime = millis();

    Serial.println("data sent!");
    
  } 
  
 else {
    // if you couldn't make a connection:
    Serial.println("connection failed!");
  } 
}
void connectToWIFI()
{
   // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0") {
    Serial.println("Please upgrade the firmware");
  }
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
