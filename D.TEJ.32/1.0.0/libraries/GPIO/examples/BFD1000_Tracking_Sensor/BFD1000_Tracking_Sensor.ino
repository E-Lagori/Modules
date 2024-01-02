/**
  @file BFD1000_Tracking_Sensor.ino
  @brief  To detect and track a line (black) even if the path is altered by changing the shape of the line. 
  @detail Senses black line by using sensor module and then sends the signal to aries. Then aries blinks LED according to the sensors' output.
  
   Reference arduino code: https://www.youtube.com/watch?v=9uPWW2ZlG_g
   Refrence aries board: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf
   
    *** xcluma BFD-1000 5 Channel Tracking Sensor ***
   Connections:
   BFD1000        Aries Board
   GND        -   GND
   VCC        -   3.3V
   S1         -   GPIO-0
   S2         -   GPIO-1
   S3         -   GPIO-2
   S4         -   GPIO-3  
   S5         -   GPIO-4    
 **/


//**********5 Channel IR Sensor Connection**********//
#define ir1 2      //Connect s1 pin of Sensor to GPIO-0 of Aries
#define ir2 3      //Connect s2 pin of Sensor to GPIO-1 of Aries
#define ir3 4      //Connect s3 pin of Sensor to GPIO-2 of Aries
#define ir4 5      //Connect s4 pin of Sensor to GPIO-3 of Aries
#define ir5 6      //Connect s5 pin of Sensor to GPIO-4 of Aries
//*************************************************//

void setup() {
  Serial.begin(115200);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ir4, INPUT);
  pinMode(ir5, INPUT);
}

void loop() {
  //Reading Sensor Values
  int s1 = digitalRead(ir1);  //Left Most Sensor
  int s2 = digitalRead(ir2);  //Left Sensor
  int s3 = digitalRead(ir3);  //Middle Sensor
  int s4 = digitalRead(ir4);  //Right Sensor
  int s5 = digitalRead(ir5);  //Right Most Sensor

  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    Serial.println("S3 Detected Black line");
  }
  
  //if only left sensor detects black line
  else if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    Serial.println("S2 Detected Black line");
  }
  
  //if only left most sensor detects black line
  else if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
  {
    Serial.println("S1 Detected Black line");
    //going right with full speed 
  }

  //if only right sensor detects black line
  else if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
  {
    Serial.println("S4 Detected Black line");
  }

  //if only right most sensor detects black line
  else if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
  {
    Serial.println("S5 Detected Black line");
  }

  //if middle and right sensor detects black line
 else  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
  {
    Serial.println("S3 & S4 Detected Black line");
  }

  //if middle and left sensor detects black line
 else  if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    Serial.println("S2 & S3 Detected Black line");
  }

  //if middle, left and left most sensor detects black line
  else if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
  {
    Serial.println("S1, S2 & S3 Detected Black line");
  }

  //if middle, right and right most sensor detects black line
 else if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    Serial.println("S3, S4 & S5 Detected Black line");
  }

  //if all sensors are on a black line
 else if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
  {
    Serial.println("All sensors detected black line");
  }
  else{
    Serial.println("No black line detected");
  }
  delay(1);
}
