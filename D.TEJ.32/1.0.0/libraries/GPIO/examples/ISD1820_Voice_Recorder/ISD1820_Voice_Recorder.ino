/*
  @file ISD1820_Voice_Recorder.ino
  @brief ISD1820 Arduino Voice Recorder
  @detail to record and playback sound using Aries and ISD1820 Sound Recorder

   Reference Aries Pinout: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf 
   Reference : Watch the video https://youtu.be/IfK8z_o5vbk
   
   *** ISD1820 Voice Recorder ***
   Connections:
   ISD1820        Aries Board
   VCC      -   3.3V
   GND      -   GND
   REC      -   GPIO2
   PLAYE    -   GPIO3
   PLAYL    -   GPIO4
   FT       -   GPIO5
*/

#define REC 2 // pin 2 is used for recording
#define PLAY_E 3 // pin 3 is used for playback-edge trigger
// when PLAY_E goes HIGH device will playbak STARTS and continues
// ISD1820 Arduino Voice Recorder for Robojax.com 

#define PLAY_L 4 // pin 4 is used for playback  
// when PLAY_L is HIGH it will playback. As soon as it goes LOW playback STOPS
// So you have to keep it HIGH to keep playing


#define FT 5 // pin 5 is used for feed through
// if the SPI (speaker) pin is used to send Audio to other device, 
// set FT to high and any audio from microphone will pass through the SPI connector
// and will NOT record

#define playTime 5000 // playback time 5 seconds
#define recordTime 3000 // recording time 3 seconds
#define playLTime 900 // press and release playback time 0.9 seconds

void setup() 
{
  delay(2000);
  
  // ISD1820 Arduino Voice Recorder for Robojax.com 
  pinMode(REC,OUTPUT);// set the REC pin as output
  pinMode(PLAY_L,OUTPUT);// set the PLAY_L pin as output
  pinMode(PLAY_E,OUTPUT);// set the PLAY_e pin as output
  pinMode(FT,OUTPUT);// set the FT pin as output  
  Serial.begin(115200);// set up Serial monitor   
  Serial.println("**** Enter r to record, p to play");

}

void loop() {
  // ISD1820 Arduino Voice Recorder for Robojax.com 
    while (Serial.available() > 0) {
          char inChar = (char)Serial.read();
         
          if (inChar == '\r' || inChar =='\n'){
          //Serial.print("inChar: ");
          //Serial.println(inChar);
       
          }
          
            if(inChar =='p' || inChar =='P'){
            digitalWrite(PLAY_E, HIGH);
            delay(50);
            digitalWrite(PLAY_E, LOW);  
            Serial.println("Playbak Started");  
            delay(playTime);
            Serial.println("Playbak Ended");
               
            break; 
            }// if          
            else if(inChar =='r' || inChar =='R'){
             digitalWrite(REC, HIGH);
             Serial.println("Recording started");
             delay(recordTime);
             digitalWrite(REC, LOW);
             Serial.println("Recording Stopped "); 
             break; 
            } 
            else if(inChar =='l' || inChar =='L'){
            digitalWrite(PLAY_L, HIGH); 
            Serial.println("Playbak L Started");  
            delay(playLTime);
            digitalWrite(PLAY_L, LOW);
            Serial.println("Playbak L Ended");  
            break;          
            }             
    // ISD1820 Voice Recorder       
      delay(500);
      
     Serial.println("**** Serial Monitor Exited"); 
    
    }// while
}
