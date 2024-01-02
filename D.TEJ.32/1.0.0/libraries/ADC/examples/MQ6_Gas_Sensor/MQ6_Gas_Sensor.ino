/*
  @file MQ6_Gas_Sensor.ino
  @brief Interfacing MQ6 to ARIES V2 Board
  @detail This demo is used to display the interfacing MQ6 to ARIES V2 Board
   
   Reference aries board: https://vegaprocessors.in/blog/interfacing-8x8-led-dot-matrix-to-aries-v2-board/
   
   *  Library Name : MQUnifiedsensor
   *  Library Version : 3.0.0  
   
            *** MQ6 ***
   Connections:
   MQ6              Aries Board
   VCC          -   5V
   GND          -   GND
   Aout         -   A0 using 2.7K & 4.7K  Resistor 
   Dout         -   Not Required
   
   Note: A voltage divider is required between MQ6 sensor output and Analog pin of Aries board, for accurate measurements. 
  Connect a 2.7K resistor to A0 pin of MQ6 sensor. Connect one end of 4.7K resistor in series to the 2.7K resistor, and other end to the GND.
  Take the output from the junction of 2.7K and 4.7K resistor.
*/


//Include the library
#include <MQUnifiedsensor.h>

//Definitions
#define placa "Vega Aries"
#define Voltage_Resolution 5
#define pin A0                  //Analog input 0 of your aries
#define type "MQ-6"             //MQ6
#define ADC_Bit_Resolution 12 
#define RatioMQ6CleanAir 10   //RS / R0 = 10 ppm 


//Declare Sensor
MQUnifiedsensor MQ6(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  //Init the serial port communication - to debug the library
  Serial.begin(115200); //Init serial port

  //Set math model to calculate the PPM concentration and the value of constants
  MQ6.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ6.setA(2127.2); MQ6.setB(-2.526); // Configure the equation to to calculate CH4 concentration
  /*
    Exponential regression:
  GAS     | a      | b
  H2      | 88158  | -3.597
  LPG     | 1009.2 | -2.35
  CH4     | 2127.2 | -2.526
  CO      | 1000000000000000 | -13.5
  Alcohol | 50000000 | -6.017
  */
  
  /*****************************  MQ Init ********************************************/ 
  //Remarks: Configure the pin of arduino as input.
  /************************************************************************************/ 
  MQ6.init();   
  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ6.setRL(10);
  */
  /*****************************  MQ CAlibration ********************************************/ 
  // Explanation: 
   // In this routine the sensor will measure the resistance of the sensor supposedly before being pre-heated
  // and on clean air (Calibration conditions), setting up R0 value.
  // We recomend executing this routine only on setup in laboratory conditions.
  // This routine does not need to be executed on each restart

  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for(int i = 1; i<=10; i ++)
  {
    MQ6.update(); // Update data, the board will read the voltage from the analog pin
    calcR0 += MQ6.calibrate(RatioMQ6CleanAir);
    Serial.print(".");
  }
  MQ6.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
  /*****************************  MQ CAlibration ********************************************/ 
  MQ6.serialDebug(true);
}

void loop() {
  MQ6.update(); // Update data, the board will read the voltage from the analog pin
  MQ6.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  MQ6.serialDebug(); // Will print the table on the serial port
  delay(1000); //Sampling frequency
}
