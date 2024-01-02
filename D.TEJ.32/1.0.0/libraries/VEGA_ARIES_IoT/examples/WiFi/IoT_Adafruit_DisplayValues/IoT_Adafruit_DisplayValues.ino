/*
 @file   IoT_PostDemo.ino
 @brief  Wi-Fi NINA Module communicates with the ARIES IoT v1 Board via the SPI Protocol
 @detail Wi-Fi NINA allows ARIES to connect to a Wi-Fi network and push data of any sensor to adafruit block

 * Reference Arduino code: https://www.electronics-lab.com/project/getting-started-with-adafruit-io-iot-cloud-platform/
 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Required Libraries : Adafruit BME680 Library (Version 2.0.2)
 *                      Adafruit GFX_Library (Version 1.11.5)
 *                      Adafruit SSD1306 (Version 2.5.7)
 *                      Adafruit Unified Sensor (Version 1.1.9)   
 *                      ArduinoJson   (Version 6.21.2)
 *                      Arduino_APDS9960 (Version 1.0.4)
 *                      VEGA_BMI088 (Version 1.0.0)
 *                      VEGAIoT_BusIO (Version 1.0.0)    
 *                      VEGA_WiFiNINA (Version 1.0.1)
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
 * 10) Repeat steps 4 to 9 to create more feeds and dashboards for other sensor values
 * 11) At present Maximum dashboard limit is 5 and maximum feed limit is 10 in a single adafruit account 
 * 
 * Steps to do in the Code:
 * 1) Replace the values in SECRET_SSID in arduino_secrets.h file with your wi-Fi hotspot username
 * 2) Replace the values in SECRET_PASS in arduino_secrets.h file with your wi-Fi hotspot password
 * 3) Replace the values in IO_USERNAME  with your Adafruit username
 * 4) Replace the values in IO_GROUP  with your Adafruit group name
 * 5) Replace the values in IO_KEY  with your Adafruit group key
 * 6) Replace the values in feed1["key"]  with your Adafruit feed name
 * 7) Repeat step 6 for all of your feed["key"] pairs created 
 * 
 * After completing above steps properly,turn on your hostspot, run this code and output values will be displayed in the serial monitor and Adafruit dashboard created
 * 
 * Example cloud data base details given in Adafruit account:
 * username         ->mydhily
 * Adafruit IO key  -> aio_UBnp43gUiHdyCK4mMgkXVmKkZ2hM
 * Group name       -> group
 * Feed names       -> feed 1 = altitude
 *                  -> feed 2 = bmiData
 *                  -> feed 3 = bmiGyro
 *                  -> feed 4 = gas
 *                  -> feed 5 = humidity
 *                  -> feed 6 = pressure
 *                  -> feed 7 = proximity
 *                  -> feed 8 = rgb
 *                  -> feed 9 = temperature
 *            
 * DashBoard name   -> room1
 * Block Names      -> All the 9 block names are same as the feed names
 * 
*/

#include <ArduinoJson.h>  
#include <SPI.h>
#include <WiFiNINA.h>
#include <Arduino_APDS9960.h>
#include "arduino_secrets.h"
#include "Adafruit_BME680.h"
#include "BMI088.h"

#define IO_USERNAME "mydhily"   //Replace with your Adafruit username
#define IO_GROUP "group"        //Replace with your adafruit group name
#define IO_KEY "aio_UBnp43gUiHdyCK4mMgkXVmKkZ2hM"  //Replace with your Adafruit key

TwoWire Wire(8);
SPIClass SPIbmi(2);

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

//These values are in the datasheet for thermistor
#define RT0 10000   // Ω
#define B 3977      // K
//--------------------------------------
#define VCC 3.3    //Supply voltage
#define R 10000  //R=10KΩ

Adafruit_BME680 bme;              // I2C
Bmi088Accel accel(SPIbmi,0xFF);  //accel object 
Bmi088Gyro gyro(SPIbmi,21);      //gyro object 

char ssid[] = SECRET_SSID;         // your network SSID (name)
char pass[] = SECRET_PASS;         // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;
char server[] = "io.adafruit.com"; // name address for Adafruit IOT Cloud

// Initialize the client library
WiFiClient client;
int state = 2;

unsigned long lastConnectionTime = 0;              // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 7000;       // delay between updates, in milliseconds
const int thermistor = A7;  // Thermistor in A7

float _temperature = 0;
float _pressure = 0;
float _altitude = 0;
float _gas = 0;
float _humidity = 0;

int statusBmi;    //Bmi variable
float _accelX = 0;
float _accelY = 0;
float _accelZ = 0;
float _gyroX = 0;
float _gyroY = 0;
float _gyroZ = 0;
char* op ;
char output[50];

int proximity;                  //apds proximity variable
int r,g,b;                      //apds colour variable
float RT, VR, ln, TX, T0, VRT;  //Thermistor variables
float _proximity = 0;

void setup() {
 delay(2000);
 Serial.begin(115200);
 #if defined (VEGA_ARIES_IOT)
 
 sensorsSetup();
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
     printValues();
    httpRequest(); // send data to Cloud
 // }

  #else
  Serial.println("Choose the correct board! " );
  #endif 
  
}

void sensorsSetup(){
//BME
   while (!Serial);
   if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

//BMI
  //start the sensors
  statusBmi = accel.begin();
  statusBmi = accel.begin();
  if (statusBmi < 0) {
    Serial.println("Accel Initialization Error");
    Serial.println(statusBmi);
    while (1) {}
  }
  statusBmi = gyro.begin();
  if (statusBmi < 0) {
    Serial.println("Gyro Initialization Error");
    Serial.println(statusBmi);
    while (1) {}
  } 

//THERMISTOR
    T0 = 25 + 273.15;  //Temperature T0 from datasheet, conversion from Celsius to kelvin

//APDS
    if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  } 
}

void readSensors()
{
 //BME
 if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
 
  _pressure = bme.pressure / 100.0;
  _humidity = bme.humidity;
  _gas = bme.gas_resistance / 1000.0;
  _altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  //BMI
   accel.readSensor(); // read the accel
  gyro.readSensor();  //read the gyro 
 
  _accelX =accel.getAccelX_mss();
  _accelY =accel.getAccelY_mss();
  _accelZ =accel.getAccelZ_mss();
  
  _gyroX = gyro.getGyroX_rads();
  _gyroY = gyro.getGyroY_rads();
  _gyroZ = gyro.getGyroZ_rads();
   delay(1000);

  //THERMISTOR
  VRT = analogRead(thermistor);              //Acquisition analog value of VRT
  VRT = (3.30 / 4095.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX = TX - 273.15;                 //Conversion to Celsius
   _temperature = TX;
   
   //APDS
  // check if a proximity reading is available
  if (APDS.proximityAvailable()) {
    // read the proximity
    // - 0   => close
    // - 255 => far
    // - -1  => error
    proximity = APDS.readProximity();

  // check if a color reading is available
  while (! APDS.colorAvailable()) {
    delay(5);
  }

  // read the color
  APDS.readColor(r, g, b);
  _proximity = proximity;  
  }  
}

void printValues(){
  readSensors();
  
  //Serial.println("Sensor Data sent to adafruit cloud:  ");
 //BME
  Serial.print("Pressure = ");
  Serial.print(_pressure);
  Serial.println(" hPa");
  Serial.print("Humidity = ");
  Serial.print(_humidity);
  Serial.println(" %");
  Serial.print("Gas = ");
  Serial.print(_gas);
  Serial.println(" KOhms");
  Serial.print("Approx. Altitude = ");
  Serial.print(_altitude);
  Serial.println(" m");

 //APDS
   //Serial.println("Show your hands in proximity range to check: ");
   //Serial.println("Value will be 0 if in close proximity ");
   Serial.print("proximity: ");
   Serial.println(_proximity);

 //THERMISTOR
  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.println(_temperature); 
}


//convert float values to string upto 6 digits accuracy
  char* toString(float value, int decimalPoints) {
  int multiplier = pow(10, decimalPoints);     //10^Power
  long integerPart = abs (long(value * multiplier) / multiplier); //Q
  long decimalPart = abs (long(value * multiplier) % multiplier); //R

if (value < 0){
    sprintf(output, "-%ld.%ld", integerPart, decimalPart); //Q.R  
  }
  else{
      sprintf(output, "%ld.%ld", integerPart, decimalPart); //Q.R
  }
  op = output ;
  return op;
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

  const size_t capacity = JSON_ARRAY_SIZE(6) + 6*JSON_OBJECT_SIZE(4) + 4*JSON_OBJECT_SIZE(6) + 130;
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

  JsonObject feed2 = feeds.createNestedObject();
  feed2["key"] = "humidity";           //Replace with your feed name
  feed2["value"] = _humidity;          

  JsonObject feed3 = feeds.createNestedObject();
  feed3["key"] = "altitude";           //Replace with your feed name
  feed3["value"] = _altitude;          

  JsonObject feed4 = feeds.createNestedObject();
  feed4["key"] = "gas";           //Replace with your feed name
  feed4["value"] = _gas;     

  JsonObject feed5 = feeds.createNestedObject();
  feed5["key"] = "pressure";           //Replace with your feed name
  feed5["value"] = _pressure;  

//BMI

  JsonObject feed6 = feeds.createNestedObject();
  static char value[50];
  sprintf(value, "aclX: %s, aclY: %s, aclZ: %s", toString(_accelX, 2 ), toString(_accelY, 2 ),toString(_accelZ, 2 ));
  feed6["key"] = "bmiData";
  feed6["value"] = value;
  Serial.println(value);
 

/*
  JsonObject feed6 = feeds.createNestedObject();
  static char value[50];
  sprintf(value, "aclX: %.2f, aclY: %.2f, aclZ: %.2f", _accelX,_accelY, _accelZ);
  feed6["key"] = "bmiData";
  feed6["value"] = value;
  Serial.println(value);
*/

  JsonObject feed7 = feeds.createNestedObject();
  static char buffer[50];
  sprintf(buffer, "GxX: %.2f, GyY: %.2f, GzZ: %.2f", _gyroX,_gyroY, _gyroZ);
  feed7["key"] = "bmiGyro";
  feed7["value"] = buffer;
  Serial.println(buffer);

  //APDS
  JsonObject feed8 = feeds.createNestedObject();
  feed8["key"] = "proximity";           //Replace with your feed name
  feed8["value"] = _proximity;  

  JsonObject feed9 = feeds.createNestedObject();
  static char buffers[20];
  sprintf(buffers, "r: %d, g: %d, b: %d", r,g,b);
  feed9["key"] = "rgb";           //Replace with your feed name
  feed9["value"] = buffers; 
  Serial.println(buffers); 
  
  
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
