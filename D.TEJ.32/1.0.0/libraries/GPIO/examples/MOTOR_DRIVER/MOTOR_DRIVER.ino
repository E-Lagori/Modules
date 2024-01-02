/*
  @file MOTOR_DRIVER.ino
  @brief Interface L298N and L293D Motor Driver Module with Aries
  @detail To control the speed and spinning direction of a Small gear motor using the L298N & L293D Motor Driver
  
   Reference code: https://www.instructables.com/How-to-use-the-L293D-Motor-Driver-Arduino-Tutorial/ , 
                   https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/
                   https://www.teachmemicro.com/use-l298n-motor-driver/ 
   
   *** L298N Motor Driver ***
   Connections:
   L298N         Aries Board
   12V & 5V  -   5V
   GND       -   GND
   ENB       -   PWM 1
   IN3       -   GPIO 13
   IN4       -   GPIO 15

    Note: L298N motor driver includes a 78M05 On-board 5V Regulator and Jumper that can be enabled or disabled via a jumper.
    If we are giving only 12V supply this regulator will internally produce 5V that is required for the driver module. 
    But here we are giving an external 5V power supply from our board, so remove the cap of 5V Regulator Enable Jumper while connecting.
    
    *** L293D Motor Driver ***
   Connections:
   L293D        Aries Board
   12V & 5V  -   5V
   GND       -   GND
   EN2       -   PWM 1
   C2-A      -   GPIO 13
   C2-B      -   GPIO 15  
*/

//    The direction specifications
//  ENA   IN1   IN2     Description  
//  HIGH  HIGH  HIGH     stop
//  HIGH  HIGH  LOW      clockwise
//  HIGH  LOW   HIGH     anti clockwise
//  HIGH  LOW   LOW      stopped

#include<pwm.h>

//Motor Connections
//Change this if you wish to use another diagram
#define EnA 1       //Connect Enable pin to PWM 1
#define In1 13      //Connect input pin to GPIO-13
#define In2 15      //Connect input pin to GPIO-15

void setup()
{
  // All motor control pins are outputs
  pinMode(EnA, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  PWM.PWMC_Set_Period(EnA, 800000);
}

void startMotor() 
{
  analogWrite(EnA, 800000);
  // now turn on motors in clockwise direction
  digitalWrite(In1, HIGH);
  digitalWrite(In2,LOW);  
}

void clockwise() 
{
  analogWrite(EnA, 800000);
  // turn on motor in clockwise direction
  digitalWrite(In1, HIGH);
  digitalWrite(In2, LOW);
}

void antiClockwise() 
{
  // turn on motor in anticlockwise direction
  analogWrite(EnA, 800000);
  digitalWrite(In1, LOW);
  digitalWrite(In2, HIGH); 
}

void stopMotor() 
{
  // now turn off motors
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);  
}
void loop()
{
  startMotor();
  delay(1000);
  clockwise();
  delay(1000);
  antiClockwise();
  delay(1000);
  stopMotor();
  delay(3000);
}
