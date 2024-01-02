/*
  @file GY906_IRtempSensor.ino
  @brief GY906/MLX90614  sensor for reading temperature
  @detail Reading the temperature using the MLX90614 sensor

  Aries Board pinout: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf

   
   *** MLX90614 ***
   Connections:
   MLX90614        Aries Board
   GND      -   GND
   VCC      -   3.3V
   SCL      -   GPIO6
   SDA      -   GPIO5 
*/


#include <SWire.h>

SWire mlx;

#define MLX90614_WRITE_ADDR     0xB4
#define MLX90614_READ_ADDR      0xB5
#define MLX90614_AMBIENT_TEMP   0x06
#define MLX90614_TARGET_TEMP    0x07


double temperature;
#define SCL 6
#define SDA 5

#define START_DELAY 250
#define CLK_DELAY 5
#define  FRAME_DELAY 10

double mlx90614ReadTempC(unsigned char reg)
{
  double tempC;
  unsigned int tempData = 0;


  
  mlx.Start(START_DELAY, CLK_DELAY);                    //mlx90614Start();
  mlx.writebyte(MLX90614_WRITE_ADDR, CLK_DELAY);                    //writebyte(MLX90614_WRITE_ADDR);
  mlx.writebyte(reg, CLK_DELAY);                    //writebyte(reg);
  mlx.Restart(CLK_DELAY);                  //mlx90614Restart();
  mlx.writebyte(MLX90614_READ_ADDR, CLK_DELAY);                    //writebyte(MLX90614_READ_ADDR);
  tempData =  mlx.readbyte(CLK_DELAY);          //readbyte();
  tempData |=  mlx.readbyte(CLK_DELAY) << 8;    //readbyte() << 8;
  mlx.Stop(FRAME_DELAY);                      //mlx90614Stop();
  tempC = tempData * 0.02;
  tempC -= 273.15;
  return tempC;
}

double mlx90614ReadAmbientTempC()
{
  return mlx90614ReadTempC(MLX90614_AMBIENT_TEMP);
}

double mlx90614ReadTargetTempC()
{
  return mlx90614ReadTempC( MLX90614_TARGET_TEMP);
}


void setup()
{
  delay(2000);
  mlx.init(SCL,SDA);
  
  Serial.begin(115200);
  Serial.println("+-----[ mlx90614 dci Temperature Sensor Demo ]-----+");
  Serial.println("|                                                  |");
  Serial.println("|                 SCL ---> GPIO6                   |");
  Serial.println("|                 SDA ---> GPIO5                   |");
  Serial.println("|                                                  |");
  Serial.println("+--------------------------------------------------+");
}


 void loop ()
  {
   
    temperature = mlx90614ReadAmbientTempC();   //Function to get ambient temperature
    Serial.print("Ambient Temp : ");
    Serial.print(temperature);
    temperature = mlx90614ReadTargetTempC();    //Function to get target temperature
    Serial.print("   Target Temp :");
     Serial.println(temperature);
    delay(500);
  }
