/*
 @file   Thermistor.ino
 @brief  This example reads the data from the on-board thermistor 
 @detail This example reads the temperature from thermistor and prints updates to the Serial Monitor every 500 ms.

 * Reference ARIES IoT board: https://vegaprocessors.in/devboards/ariesiot.html
 * Reference ARIES IoT pin diagram: https://vegaprocessors.in/files/ARIES-IoT-Pin-out.pdf
 * 
 * Note:
 * No external connections required for testing this code using ARIES IoT v1
 * 
 * Thermometer with thermistor
 * Thermistor parameters:
 * RT0: 10 000 Ω
 * B:   3977 K +- 0.75%
 * T0:  25 C
 * +- 5%
*/

//These values are in the datasheet
#define RT0 10000   // Ω
#define B 3977      // K
//--------------------------------------


#define VCC 3.3    //Supply voltage
#define R 10000  //R=10KΩ
#define thermistor A7  //thermistor connection

//Variables
float RT, VR, ln, TX, T0, VRT;

void setup() {
  Serial.begin(115200);
  T0 = 25 + 273.15;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin
}

void loop() {
  #if defined (VEGA_ARIES_IOT)
  
  VRT = analogRead(thermistor);       //Acquisition analog value of VRT
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
  Serial.println("F");
  delay(500);

  #else
  Serial.println("Choose the correct board! " );
  #endif
}
