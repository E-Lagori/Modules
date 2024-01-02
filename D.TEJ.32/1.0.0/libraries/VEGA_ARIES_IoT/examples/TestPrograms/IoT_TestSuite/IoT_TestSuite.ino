/*
 @file   IoT_TestSuite.ino
 @brief  Test for all sensors in ARIES IoT v1
 @detail This code will test all the sensors connected in ARIES IoT v1 and will display the output in serial Monitor

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
 * 
 * Note:
 * Select "Newline" option in Serial Monitor to view the proper output for this program
 * No external connections required for testing this code using ARIES IoT v1, except for ADC voltage testing. If you want to check ADC voltage 
 * in any analog pins then you can connect a Male-Male connecter between any analog pins and VCC(3.3V)/GND after running this code
 * 
 * 
 * Steps to do before executing this code :
 * 1) Replace the values in SECRET_SSID in arduino_secrets.h file with your wi-Fi hotspot username
 * 2) Replace the values in SECRET_PASS in arduino_secrets.h file with your wi-Fi hotspot password
 * 
 * After completing above steps properly, run this code and output values will be displayed in the serial monitor
 * 
*/

#include <Wire.h>
#include <SPI.h>
#include <Arduino_APDS9960.h>
#include <WiFiNINA.h>
#include <Adafruit_Sensor.h>
#include <pwm.h>
#include "Adafruit_BME680.h"
#include "BMI088.h"
#include "arduino_secrets.h" 


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
#define BUZZER 7  //Piezo buzzer connected in PWM 7
#define PERIOD 2500  //Piezo buzzer period is set as 2500
#define PIN0 A0  // Reading value from Analog pin 0
#define PIN1 A1
#define PIN2 A2
#define PIN3 A3
#define PIN4 A4
#define PIN5 A5



bool bmeTestflag = false;
bool bmiTestflag=false;
bool apdsTestflag=false;
bool apdsGestureTestflag=false;
bool thermistorTestflag=false;
bool buttonTestflag=false;
bool potTestflag=false;
bool ledTestflag=false;
bool buzzerTestflag=false;
bool adcTestflag=false;
bool wifiTestflag=false;

const int thermistor = A7;  // Thermistor in A7
const int btn0 = 19;        //Push button 0 in GPIO-19
const int btn1 = 18;       //Push button 1 in GPIO 18
const int pot = A6;        // potentiometer in A6
const int greenLED = 22;  //Internal Green LED in GPIO 22
const int blueLED = 23;   //Internal Blue LED in GPIO 22
const int redLED= 24;     //Internal Red LED in GPIO 22

int keypress;
int statusBmi;                  //Bmi variable
int proximity;                  //apds proximity variable
int r,g,b;                      //apds colour variable
float RT, VR, ln, TX, T0, VRT;  //Thermistor variables
int buttonVal0;                 //push button variables
int buttonVal1;                 //push button variables
float voltage;                  //potentiometer variables
int sensorValue;                //potentiometer variables
int i;                          //Piezo buzzer variable
int adc0;                       //analog channel variables
int adc1; 
int adc2;
int adc3;
int adc4;
int adc5;
//Wi-Fi NINA
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)
int status = WL_IDLE_STATUS;


Adafruit_BME680 bme;              // I2C
Bmi088Accel accel(SPIbmi,0xFF);  //accel object 
Bmi088Gyro gyro(SPIbmi,21);      //gyro object 
WiFiServer server(80);


void setup() {
  delay(2000);
  Serial.begin(115200);
  #if defined (VEGA_ARIES_IOT)
  bmeSetup();
  bmiSetup();
  apdsSetup();
  thermistorSetup();
  buttonSetup();
  buzzerSetup();
  wifiSetup();

  #else
  Serial.println("Choose the correct board! " );
  #endif 
}

void loop() {  
  #if defined (VEGA_ARIES_IOT)
  
  Serial.println("Press ENTER key to Start");
  Serial.println(" ");
  
  while (Serial.available()== 0) {};
  int keypress = Serial.read();

  if (keypress > 0 && !wifiTestflag){
    wifiTest();
    wifiTestflag = true;
    keypress = 0;
   }
   
  if (keypress > 0 && !bmeTestflag){  
    bmeTest();
    bmeTestflag = true;
    keypress = 0;
   } 
   if (keypress > 0 && !bmiTestflag){
    bmiTest();
    bmiTestflag = true;
    keypress = 0;
   }
   if (keypress > 0 && !apdsTestflag){
    apdsTest();
    apdsTestflag = true;
    keypress = 0;
   }
   if (keypress > 0 && !apdsGestureTestflag){
    Serial.println("Show Gestures: " );
    Serial.println("After testing press any key to go to next Test");
    Serial.println("Gesture directions are as follows: " );
    Serial.println("- RIGHT:    from USB connector towards antenna" );
    Serial.println("- LEFT:  from antenna towards USB connector" );
    Serial.println("- UP:  from analog pins side towards digital pins side" );
    Serial.println("- DOWN: from digital pins side towards analog pins side" );
    apdsGestureTest();
    apdsGestureTestflag = true;
    keypress = 0;
   }
   if (keypress > 0 && !thermistorTestflag){
    thermistorTest();
    thermistorTestflag = true;
    keypress = 0;
   }
   if (keypress > 0 && !buttonTestflag){
    buttonTest();
    buttonTestflag = true;
    keypress = 0;
   }
   if (keypress > 0 && !potTestflag){
    potTest();
    potTestflag = true;
    keypress = 0;
   }
   if (keypress > 0 && !ledTestflag){
    ledTest();
    ledTestflag = true;
    keypress = 0;
   }
   if (keypress > 0 && !buzzerTestflag){
    buzzerTest();
    buzzerTestflag = true;
    keypress = 0;
   }
   if (keypress > 0 && !adcTestflag){
    adcTest();
    adcTestflag = true;
    keypress = 0;
   }

    if (bmeTestflag && bmiTestflag && apdsTestflag && apdsGestureTestflag 
        && buttonTestflag && potTestflag && ledTestflag && buzzerTestflag
        && adcTestflag && wifiTestflag){
      while(1);
    }

    #else
  Serial.println("Choose the correct board! " );
  #endif 
}

void bmeSetup(){
   while (!Serial);
   Serial.println();
   Serial.println("ARIES IoT Test START");
   //Serial.println(F("BME680 test")); 
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
}

void bmiSetup(){
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
}

void apdsSetup(){
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor!");
  } 
}

void thermistorSetup(){
  T0 = 25 + 273.15;  //Temperature T0 from datasheet, conversion from Celsius to kelvin
}

void buttonSetup(){
  pinMode(btn0,INPUT);
  pinMode(btn1,INPUT);
}

void buzzerSetup(){
 // PWM.PWMC_Set_Period(BUZZER, 800000);  // setting period
}

void wifiSetup(){
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  Serial.println("Select 'Newline' option in Serial Monitor to view the proper output for this program");
  // attempt to connect to WiFi network:
  Serial.println("Turn on your Wi-Fi hotspot and give its credentials in arduino_secrets.h before running the program");
  Serial.println(" ");
  delay(5000);
  int retry = 5;
  while (status != WL_CONNECTED && retry > 0) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    retry --;
    Serial.print(retry);
    Serial.println("  retries left");
    // wait 10 seconds for connection:
    delay(10000);
  }
  if(retry <= 0){
    wifiTestflag=true;
    Serial.println("\nWi-Fi Test cases will not be executed since all retries exhausted for connecting to your hotspot");
    return;
  }
  //Serial.println("Note and type the given IP Address in your browser to view output ");
  server.begin();
  // you're connected now, so print out the status:
 // printWifiStatus();
}


void bmeTest(){
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.println("TEST 1: BME680 START: ");
  delay(2000);
  
  while (Serial.available()== 0){
  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(bme.humidity);
  Serial.println(" %");

  Serial.print("Gas = ");
  Serial.print(bme.gas_resistance / 1000.0);
  Serial.println(" KOhms");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
  Serial.println("Press any key to stop");
  Serial.println();
  delay(1000);
   }
   Serial.println("BME680 Test END ");
   Serial.println();
}

void bmiTest(){
  Serial.println("TEST 2: BMI088 START: ");
  Serial.println("Measures acceleration and gyroscope values in X,Y,Z Directions");
  delay(5000);
  while (Serial.available()== 0) {
  accel.readSensor(); // read the accel
  gyro.readSensor();  //read the gyro 
  Serial.print(accel.getAccelX_mss());
  Serial.print("\t");
  Serial.print(accel.getAccelY_mss());
  Serial.print("\t");
  Serial.print(accel.getAccelZ_mss());
  Serial.print("\t");
  Serial.print(gyro.getGyroX_rads());
  Serial.print("\t");
  Serial.print(gyro.getGyroY_rads());
  Serial.print("\t");
  Serial.print(gyro.getGyroZ_rads());
  Serial.print("\t");
  Serial.print(accel.getTemperature_C());
  Serial.println("  ");
  Serial.println("Press any key to stop");
  Serial.println();
  delay(500);
  }
  Serial.println("BMI088 Test END ");
  Serial.println();
}

void apdsTest(){
  Serial.println("TEST 3: APDS9960 START: ");
  Serial.println("APDS9960 is used for Proximity, RGB values and Gesture Detection ");
  delay(5000);
  while (Serial.available()== 0) {
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

    // print value to the Serial Monitor
    Serial.println("Show your hands in proximity range to check: ");
    Serial.println("Value will be 0 if in close proximity ");
    Serial.print("proximity: ");
    Serial.println(proximity);
    Serial.println("RGB values from APDS9960 is given below: ");
    Serial.print("r = ");
    Serial.println(r);
    Serial.print("g = ");
    Serial.println(g);
    Serial.print("b = ");
    Serial.println(b);
    Serial.println("Press any key to stop");
    Serial.println();
    delay(1000);
  }
}
Serial.println("Gesture Test: ");
Serial.println();
}

void apdsGestureTest(){
  while (Serial.available()== 0) {
  if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to Serial Monitor
    int gesture = APDS.readGesture();

    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        break;

      default:
        // ignore
        continue;
    }
  }
  }
  Serial.println("APDS9960 Test END ");
  Serial.println("Press any key to Stop");
  Serial.println();
  delay(1000); 
}

void thermistorTest(){
  Serial.println("TEST 4: THERMISTOR START: ");
  Serial.println("Temperature increases if you hold the sensor ");
  delay(5000);
  while (Serial.available()== 0) {
  VRT = analogRead(thermistor);              //Acquisition analog value of VRT
  VRT = (3.30 / 4095.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX = TX - 273.15;                 //Conversion to Celsius
  
  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.print(TX);
  Serial.print("C\t\t");
  Serial.print(TX + 273.15);        //Conversion to Kelvin
  Serial.print("K\t\t");
  Serial.print((TX * 1.8) + 32);    //Conversion to Fahrenheit
  Serial.print("F");
  Serial.print("K\t\t");
  Serial.println("Press any key to stop");
  //Serial.println();
  delay(1000);
  }
  Serial.println("THERMISTOR Test END: ");
  Serial.println();
}

void buttonTest(){
  buttonVal0 = digitalRead(btn0); // Take a reading
  buttonVal1 = digitalRead(btn1); // Take a reading
  Serial.println("PUSH BUTTONS Test START: ");
  Serial.println("Press BTN0 to continue");
  while (digitalRead(btn0) == HIGH){
  }
  Serial.println("BTN0 Press Success");
  Serial.println(" ");

  Serial.println("Press BTN1 to continue");
  while (digitalRead(btn1) == HIGH){  
  }
  Serial.println("BTN1 Press Success");
  Serial.println("PUSH BUTTON Test END ");
  //Serial.println("Press any key to Stop");
  Serial.println();
  delay(1000); 
}

void potTest(){
  Serial.println("TEST 5: POTENTIOMETER START: ");
  Serial.println("Rotate POT from Minimum to Maximum value");
  delay(2000);
  while (Serial.available()== 0) {
  int sensorValue = analogRead(pot);
  Serial.print("ADC Value: ");
  Serial.print(sensorValue);
  Serial.print("      ");
  // Convert the analog reading (which goes from 0 - 4095) to a voltage (0 - 3.3V):
  // Internal Reference OFF and A/D Converter ON
  float voltage = sensorValue * (3.3 / 4095.0);
  Serial.print(voltage);
  Serial.print(" V");
  Serial.print("      ");
  Serial.println("Press any Key to Stop");
  }
  Serial.println("POTENTIOMETER Test END: ");
  Serial.println();
  delay(1000);
}

void ledTest(){
  Serial.println("TEST 6: RGB LED START: ");
  while (Serial.available()== 0) {
   Serial.println("Check On Board LEDs ");
   Serial.println("RED LED ON");
   digitalWrite(redLED,LOW); //Turn the LED on
   delay(1000);
   digitalWrite(redLED,HIGH); //Turn the LED off
   delay(1000);

   Serial.println("GREEN LED ON");
   digitalWrite(greenLED,LOW); //Turn the LED on
   delay(1000);
   digitalWrite(greenLED,HIGH); //Turn the LED off
   delay(1000);

   Serial.println("BLUE LED ON");
   Serial.println("Press any Key to Stop");
   digitalWrite(blueLED,LOW); //Turn the LED on
   delay(1000);
   digitalWrite(blueLED,HIGH); //Turn the LED off
   delay(1000);
  }
  Serial.println("RGB LED Test END: ");
}

void buzzerTest(){
 Serial.println("TEST 7: PIEZO BUZZER START: ");
 
  while (Serial.available()== 0) {
  tone(BUZZER,PERIOD);
  delay(1000);
  Serial.println("Press any Key & wait for buzzer to stop");
  }
  analogWrite(BUZZER, 0);
  Serial.println("PIEZO BUZZER Test END ");
}

void adcTest(){
  Serial.println("TEST 8: ADC Voltage START ");
  while (Serial.available()== 0) {
   adc0 = analogRead(PIN0);
   adc1 = analogRead(PIN1);
   adc2 = analogRead(PIN2);
   adc3 = analogRead(PIN3);
   adc4 = analogRead(PIN4);
   adc5 = analogRead(PIN5);

  float voltage0 = adc0 * (3.3 / 4095.0);
  float voltage1 = adc1 * (3.3 / 4095.0);
  float voltage2 = adc2 * (3.3 / 4095.0);
  float voltage3 = adc3 * (3.3 / 4095.0);
  float voltage4 = adc4 * (3.3 / 4095.0);
  float voltage5 = adc5 * (3.3 / 4095.0);

  Serial.println("Connect M-M connector between VCC and analog channel to see output ");
 /*
  Serial.print("A0 = ");
  Serial.print(adc0);
  Serial.print("  ");
  Serial.print("A1 = ");
  Serial.print(adc1);
  Serial.print("  ");
  Serial.print("A2 = ");
  Serial.print(adc2);
  Serial.print("  ");
  Serial.print("A3 = ");
  Serial.print(adc3);
  Serial.print("   ");
  Serial.print("A4 = ");
  Serial.print(adc4);
  Serial.print("  ");
  Serial.print("A5 = ");
  Serial.print(adc5);
  Serial.print("  ");
  */
  Serial.print("A0: ");
  Serial.print(voltage0);
  Serial.print(" V");
  Serial.print("   ");
  Serial.print("A1: ");
  Serial.print(voltage1);
  Serial.print(" V");
  Serial.print("   ");
  Serial.print("A2: ");
  Serial.print(voltage2);
  Serial.print(" V");
  Serial.print("   ");
  Serial.print("A3: ");
  Serial.print(voltage3);
  Serial.print(" V");
  Serial.print("   ");
  Serial.print("A4: ");
  Serial.print(voltage4);
  Serial.print(" V");
  Serial.print("   ");
  Serial.print("A5: ");
  Serial.print(voltage5);
  Serial.println(" V");
  Serial.println("Press any key to stop");
  Serial.println(" ");
  delay(500);
  }
  Serial.println("ADC Voltage Test END ");
  delay(2000);
  Serial.println(" ");
  Serial.println("ALL Tests Completed ");
}

 void wifiTest(){
  Serial.println("TEST 0: Wi-Fi Test START ");
  printWifiStatus();
  //Serial.print("IP Address: ");
  Serial.print("Type the above");
  Serial.print(" IP address ");
  Serial.println(" in your browser to view output");
  while (Serial.available()== 0) {
    // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    //Serial.println("Type the address in Referer in your browser to view output");
    // an HTTP request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the HTTP request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard HTTP response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");            
           
            client.print("Temperature = ");
            client.print(bme.temperature);
            client.print(" *C ");
            client.println("<br />");

            client.print("Pressure =  ");
            client.print(bme.pressure / 100.0);
            client.print(" hPa ");
            client.println("<br />");

            client.print("Gas = ");
            client.print(bme.gas_resistance / 1000.0);
            client.print(" KOhms ");
            client.println("<br />");

            client.print("Approx. Altitude = ");
            client.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
            client.print(" m ");
            client.println("<br />");
          
          //}
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
    Serial.println("Press any Key to stop");
  }
    }
    Serial.println("Wi-Fi Test END ");
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

  
