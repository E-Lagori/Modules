/*
  @file MQ135_Gas_Sensor.ino
  @brief Interfacing MQ135 to ARIES V2 Board
  @detail This demo is used to display the interfacing MQ135 to ARIES V2 Board
   
   Reference aries board: https://vegaprocessors.in/blog/interfacing-8x8-led-dot-matrix-to-aries-v2-board/
   
   *  Library Name : MQUnifiedsensor
   *  Library Version : 3.0.0  
   
            *** MQ135 ***
   Connections:
   MQ135              Aries Board
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
#define pin A0                  //Analog input 0 of your arduino
#define type "MQ-135"           //MQ135
#define ADC_Bit_Resolution 12 
#define RatioMQ135CleanAir 3.6  //RS / R0 = 3.6 ppm  



//Declare Sensor
MQUnifiedsensor MQ135(placa, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  //Init the serial port communication - to debug the library
  Serial.begin(115200); //Init serial port

  //Set math model to calculate the PPM concentration and the value of constants
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setA(102.2); MQ135.setB(-2.473); // Configure the equation to to calculate NH4 concentration

  /*
    Exponential regression:
  GAS      | a      | b
  CO       | 605.18 | -3.937  
  Alcohol  | 77.255 | -3.18 
  CO2      | 110.47 | -2.862
  Toluen  | 44.947 | -3.445
  NH4      | 102.2  | -2.473
  Aceton  | 34.668 | -3.369
  */
  
  /*****************************  MQ Init ********************************************/ 
 
  /************************************************************************************/ 
  MQ135.init(); 
  /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ135.setRL(10);
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
    MQ135.update(); // Update data, the board will read the voltage from the analog pin
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0/10);
  Serial.println("  done!.");
  
  if(isinf(calcR0)) {Serial.println("Warning: Conection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"); while(1);}
  if(calcR0 == 0){Serial.println("Warning: Conection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"); while(1);}
  /*****************************  MQ CAlibration ********************************************/ 
  MQ135.serialDebug(true);
}

void loop() {
  MQ135.update(); // Update data, the board will read the voltage from the analog pin
  MQ135.readSensor(); // Sensor will read PPM concentration using the model, a and b values set previously or from the setup
  MQ135.serialDebug(); // Will print the table on the serial port
  delay(500); //Sampling frequency
}
