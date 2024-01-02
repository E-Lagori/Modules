/*
 @file   IoT_GetDemo.ino
 @brief  Wi-Fi NINA Module communicates with the ARIES IoT v1 Board via the SPI Protocol
 @detail To control the internal LED in Aries IoT board from Adafruit cloud server using Wi-Fi 

 * Reference Arduino code: https://www.electronics-lab.com/project/getting-started-with-adafruit-io-iot-cloud-platform/
 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Required Libraries : VEGA_WiFiNINA (Version 1.0.1)         
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1
 * 
 * Steps to do in Adafruit cloud platform:
 * 1) Visit https://io.adafruit.com/ and login or create an account if you do not already have.
 * 2) Click the feeds button,select create a "new feed”.
 * 3) Enter the name of the feed and a description and click the create button. (example feed Name = onoff)
 * 4) Click on "Dashbords"
 * 6) select “create a new dashboard“ for creating the dashboard ( Example dashboard name -> onoffDash)
 * 7) Click on the dashboard you have created, it should open a new window. On the window, click on the “gear” Icon to start adding blocks (widgets) to the dashboard.
 * 8) Clicking on any block will enable you to set the properties of the block. Select the feed to whose data will be displayed on that block and hit the next button.
 * 9) Here in this example, for internal LED control, select the "toggle" widget from the available blocks.
 * 10)Select the feed name to connect with the block in the dashboard,Click on "Next Step"
 * 11) Give "Button On Text" value as 1 and "Button off Text" value as 0 and click on "Create block"
 * 
 * Steps to do in the Code:
 * 1) Replace the values in ssid[] with your wi-Fi hotspot username
 * 2) Replace the values in pass[] with your wi-Fi hotspot password
 * 3) Replace the values in IO_USERNAME  with your Adafruit username
 * 4) Replace the values in IO_FEEDNAME  with your Adafruit feed name
 * 5) Replace the values in adafruitKey[]  with your Adafruit key
 * 6) Replace the values in wifiClient.print() in line 99  with your Adafruit credentials
 * 
 * After completing above steps properly, run this code and then you can control the intenal LED from Adafruit cloud server
 * 
 * Example Adafruit credentials:
 * Username -> mydhily
 * Feed Name -> onoff
 * Adafruit key -> aio_UBnp43gUiHdyCK4mMgkXVmKkZ2hM
 * Adafruit Dashboard Name -> onoffDash
 * 
*/

#include <SPI.h>
#include <WiFiNINA.h>
#include <sprintf.h>

#define IO_USERNAME    mydhily   // Replace with your Adafruit username
#define IO_FEEDNAME    onoff      // Replace with your Adafruit feedname
char ssid[] = "redmi";       // Replace with your Wi-Fi network SSID
char pass[] = "123456789";   // Replace with your Wi-Fi network password
char adafruitKey[] = "aio_UBnp43gUiHdyCK4mMgkXVmKkZ2hM";   // Replace with your Adafruit IO Key

char server[] = "io.adafruit.com";   // Adafruit IO server address
char path = "/api/v2/IO_USERNAME/feeds/IO_FEEDNAME/data/last";   

char* values;
static char data[1500]={0,};
static char buffer[250];

int len_str ;
int len_target ;
const char* target;
  
WiFiClient wifiClient;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  #if defined (VEGA_ARIES_IOT)
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    delay(1000); // Try to connect every 5 seconds
  }

  Serial.println("Connected to Wi-Fi!");

  #else
  Serial.println("Choose the correct board! " );
  #endif
}

void loop() {
  #if defined (VEGA_ARIES_IOT)
  int i=0;
  // Make the GET request to Adafruit IO feed
  if (wifiClient.connect(server, 80)) {
    Serial.println("Connected to Adafruit IO!");

   // Build the HTTP GET request
   // static char buffer[50];
   //sprintf(data, "GET %s HTTP/1.1\r\nHost: %s\r\nX-AIO-Key: %c\r\nConnection: close\r\n\r\n",path,server,adafruitKey);

    
  //    String getRequest = "GET " + path + " HTTP/1.1\r\n" +
  //                        "Host: " + String(server) + "\r\n" +
  //                        "X-AIO-Key: " + String(adafruitKey) + "\r\n" +
  //                        "Connection: close\r\n\r\n";

   
   //Serial.println("GET /api/v2/mydhily/feeds/onoff/data/last HTTP/1.1\r\nHost: io.adafruit.com\r\nX-AIO-Key: aio_UBnp43gUiHdyCK4mMgkXVmKkZ2hM\r\nConnection: close\r\n\r\n");
   sprintf(buffer, "GET %s HTTP/1.1\r\nHost: %s\r\nX-AIO-Key: %s\r\nConnection: close\r\n\r\n",path,server,adafruitKey);
   // Serial.println(buffer);
    
    // Send the request
    //Replace the username,feedname and key with your Adafruit username,feedname and key in below code.
    wifiClient.print("GET /api/v2/mydhily/feeds/onoff/data/last HTTP/1.1\r\nHost: io.adafruit.com\r\nX-AIO-Key: aio_UBnp43gUiHdyCK4mMgkXVmKkZ2hM\r\nConnection: close\r\n\r\n");
    //wifiClient.print(data);
    
    // Wait for response
    i=0;
    while (wifiClient.connected()) {
      
      if (wifiClient.available()) {
        char c = wifiClient.read();
        //Serial.write(c); // Output the response to the serial monitor   
        if(i<1500)
          data[i]=c;
        i++;  
      }     
    }

    // Disconnect
    wifiClient.stop();
    Serial.println("\nDisconnected from Adafruit IO!");
    data[1499]='\0';
    //Serial.println("data: ");
    for(int j = 0; j < 1500; j++)
    {
      Serial.print(data[j]);
    }
    Serial.println();
    //Serial.println("data end: ");
   
  }
  else {
    Serial.println("Failed to connect to Adafruit IO.");
  }

  const char* target = "\"value\":\"";
  
  char characterAfterTarget = find(data, target);
  Serial.print("LED Status: ");
  Serial.println(characterAfterTarget);
  
  if(characterAfterTarget =='1'){
    digitalWrite(22,LOW);
  }
  if(characterAfterTarget =='0'){
    digitalWrite(22,HIGH);
  }
  

  // Wait before making the next request
  delay(5000);

  #else
  Serial.println("Choose the correct board! " );
  #endif
}


/**
 * @brief Finds a target substring within a source string and returns the character right after the target.
 * 
 * @param str The source string to search within.
 * @param target The target substring to search for.
 * @return char The character right after the target substring if found, or '\0' if not found.
 * 
 * This function searches for the target substring within the source string. If the target substring is found, it returns the character immediately following the target substring in the source string. If the target is not found, it returns the null character '\0'.
 * 
 * The function compares each character of the source string with the corresponding characters of the target substring. If a mismatch is found, it moves to the next character in the source string. If a complete match is found, it returns the character right after the target substring.
 * 
 * Note: The function assumes that both the source string and the target substring are null-terminated (i.e., they end with the null character '\0').
 */
 
  char find(const char* str, const char* target) {
  int len_str = strlen(str);
  int len_target = strlen(target);

  if (len_str < len_target) {
    return '\0'; // Target string is longer than the source string
  }

  for (int k = 0; k <= len_str - len_target; k++) {
    bool match = true;
    for (int l = 0; l < len_target; l++) {
      if (str[k + l] != target[l]) {
        match = false;
        break;
      }
    }
    if (match) {
      return str[k + len_target]; // Return the character right after the target
    }
  }
  return '\0'; // Target string not found in the source string
}
