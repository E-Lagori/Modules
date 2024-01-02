/**
 @file NHD_DISPLAY_DEMO.ino
 @brief Example Code for NHD Display interface
 @detail This application demonstrates the usage of FT801 library on NHD_43CTP_SHIELD platform 

 * Reference NHD datasheet: https://www.mouser.in/datasheet/2/291/NHD_4_3CTP_SHIELD_L-2953341.pdf
 * Library Name: https://gitlab.com/riscv-vega/vega-sensor-libraries/display/nhd_display
 * Connection Diagram: https://gitlab.com/riscv-vega/vega-sensor-libraries/display/nhd_display/-/blob/main/nhd_diagram.pdf
 * 
 * NHD Display
 * Connections:
 *    
 *    NHD Display     Aries Board
 * 
      *   J1 Interface
      SCL             No Connect
      SDA             No Connect
      AREF            No Connect
      GND             Ground
      13              No Connect (Short SJ2 for SPI SCK signal)
      12              No Connect (Short SJ3 for SPI MISO signal)
      11              No Connect (Short SJ1 for SPI MOSI signal)
      10              GPIO10-  FT801 Active LOW Chip Select signal
      9               GPIO9- FT801 Active LOW Host Interrupt signal
      8               GPIO8- FT801 Active LOW Power Down signal
   
      *  J2 Interface
      7               No Connect
      6               No Connect
      5               No Connect
      4               GPIO-4 ( Chip Select signal)     
   
      *  J3 Interface
    RESERVED        No Connect
    IOREF           No Connect
    RESET           No Connect
    3.3V            No Connect
    5V              Supply Voltage for Module (+5V)
    GND             Ground
    GND             Ground
    Vin             No Connect

      *  J4 Interface
    A0            No Connect
    A1            No Connect
    A2            No Connect
    A3            No Connect
    A4            No Connect
    A5            No Connect
 
      *  J5 Interface
    MISO          MISO-1 (SPI MISO signal (Default))
    5V            No Connect
    SCK           SCLK-1 (SPI SCK signal (Default))
    MOSI          MOSI-1 (SPI MOSI signal (Default))
    RESET         No Connect
    GND           Ground.
 **/


#include "SPI.h"
#include "Wire.h"

/* Application specific includes */
#include "Lena_RawData.h"


//volatile char[16] x,y;
volatile int16_t xvalue,yvalue,pendown;
volatile bool var1 =1;
volatile bool var2 =1;
volatile bool var3 =1;
volatile bool var4 =1;
volatile bool var5 =1;
volatile bool var6 =1;
volatile uint32_t cell_colour1 = 0xcc0000;
volatile uint32_t cell_colour2 = 0xcc0000;
volatile uint32_t cell_colour3 = 0xcc0000;
volatile uint32_t cell_colour4 = 0xcc0000;
volatile uint32_t cell_colour5 = 0xcc0000;
volatile uint32_t cell_colour6 = 0xcc0000;

int count=1;
SPIClass SPI(1);
/* Platform specific includes */
#include "FT_NHD_43CTP_SHIELD.h"
#define pin1 1 //GPIO pin connection
#define pin2 2 //GPIO pin connection
#define pin3 3 //GPIO pin connection
#define pin4 7 //GPIO pin connection
#define pin5 5 //GPIO pin connection
#define pin6 6 //GPIO pin connection

/* Global object for FT801 Implementation */
FT801IMPL_SPI FTImpl(FT_CS_PIN,FT_PDN_PIN,FT_INT_PIN);

/* Lena face bitmap raw data and respective structure */
typedef struct Bitmap_header
{
  uint8_t Format;
  int16_t Width;
  int16_t Height;
  int16_t Stride;
  int32_t Arrayoffset;
}Bitmap_header_t;


Bitmap_header_t Lena40_Header[] = 
{
  /* format,width,height,stride,arrayoffset */
  {FT_RGB565, 170,  70,  170*2,  0 },
};


/* Macro for size of raw data */
#define Lena40_SIZE (3000)


/* Api to bootup ft801, verify FT801 hardware and configure display/audio pins */
/* Returns 0 in case of success and 1 in case of failure */
int16_t BootupConfigure()
{
  uint32_t chipid = 0;
  FTImpl.Init(FT_DISPLAY_RESOLUTION);//configure the display to the WQVGA

  delay(20);//for safer side
  chipid = FTImpl.Read32(FT_ROM_CHIPID);
  
  /* Identify the chip */
  if(FT801_CHIPID != chipid)
  {
    Serial.print("Error in chip id read ");
    Serial.println(chipid,HEX);
    return 1;
  }
  
  /* Set the Display & audio pins */
  FTImpl.SetDisplayEnablePin(FT_DISPENABLE_PIN);
    FTImpl.SetAudioEnablePin(FT_AUDIOENABLE_PIN); 
  FTImpl.DisplayOn();   
  FTImpl.AudioOn();   
  return 0;
}
/* API for calibration on FT801 */
void Calibrate()
{  
  /*************************************************************************/
  /* Below code demonstrates the usage of calibrate function. Calibrate    */
  /* function will wait untill user presses all the three dots. Only way to*/
  /* come out of this api is to reset the coprocessor bit.                 */
  /*************************************************************************/

  /* Construct the display list with grey as background color, informative string "Please Tap on the dot" followed by inbuilt calibration command */
  FTImpl.DLStart();
  FTImpl.ClearColorRGB(33,195,216);
  FTImpl.Clear(1,1,1);    
  FTImpl.ColorRGB(0xff, 0xff, 0xff);
  FTImpl.Cmd_Text((FT_DISPLAYWIDTH/2), (FT_DISPLAYHEIGHT/2), 27, FT_OPT_CENTER, "Please Tap on the dot");
  FTImpl.Cmd_Calibrate(0);
  
  /* Wait for the completion of calibration - either finish can be used for flush and check can be used */
  FTImpl.Finish();
}

 int wScissor = 0;
  int hScissor = 0;
  int bWidth = 160;
  int bHeight = 100;


void Widgets(uint32_t cell_colour1 , uint32_t cell_colour2 ,uint32_t cell_colour3 ,uint32_t cell_colour4, uint32_t cell_colour5, uint32_t cell_colour6 )
{
  int16_t xOffset,yOffset,cRadius,xDistBtwClocks;
  int16_t wScissor,hScissor,bWidth,bHeight;

 





/////////////////////////////////
 Bitmap_header_t *p_bmhdr;
  int16_t BMoffsetx,BMoffsety;

  p_bmhdr = (Bitmap_header_t *)&Lena40_Header[0];
  /* Copy raw data into address 0 followed by generation of bitmap */
  FTImpl.Writefromflash(FT_RAM_G,&Lena40_RawData[p_bmhdr->Arrayoffset], p_bmhdr->Stride*p_bmhdr->Height);
///////////////////////////////////
  /* Display list to demonstrate the display of lena bitmap at various co ordinates and various colors */
  FTImpl.DLStart();//start the display list 
  FTImpl.ClearColorRGB(33,195,216);
  FTImpl.Clear(1,1,1);  
  FTImpl.BitmapSource(FT_RAM_G);//set the source address of bitmap to starting address of graphis ram
  FTImpl.BitmapLayout(p_bmhdr->Format, p_bmhdr->Stride, p_bmhdr->Height);//set the layout of the bitmap
  FTImpl.BitmapSize(FT_NEAREST,FT_BORDER,FT_BORDER, p_bmhdr->Width, p_bmhdr->Height);//set the bitmap size
  FTImpl.Begin(FT_BITMAPS); // start drawing bitmaps
  
  FTImpl.ColorRGB(255,255,255);//set the color of the bitmap to white
  BMoffsetx = ((FT_DISPLAYWIDTH/2) - (p_bmhdr->Width/2));
//  BMoffsety = ((FT_DISPLAYHEIGHT/2) - (p_bmhdr->Height/2));
  FTImpl.Vertex2ii(BMoffsetx, 201, 0, 0);

  
  xOffset = 0;
  yOffset = 0;

  /* revert back the scissor for the following widgets */
  FTImpl.ScissorSize(FT_MAX_DISPLAYWIDTH,FT_MAX_DISPLAYHEIGHT);//use the scissor to cull and get the rectangle from gradient
  FTImpl.ScissorXY(0,0);//set the starting coordinates of the scissor to default values

  /* button with 3d effect with gradient color */
  FTImpl.Cmd_FGColor(cell_colour1);
  FTImpl.Cmd_GradColor(cell_colour1);
  FTImpl.Cmd_Button(0,0,160,100,27,0,"FAN");//draw button with 3d effect and gradient color


  FTImpl.Cmd_FGColor(cell_colour2);
  FTImpl.Cmd_GradColor(cell_colour2);
  FTImpl.Cmd_Button(160,0,160,100,27,0,"LAMP");//draw button with 3d effect and gradient color
  
  FTImpl.Cmd_FGColor(cell_colour3);
  FTImpl.Cmd_GradColor(cell_colour3);
  FTImpl.Cmd_Button(320,0,160,100,27,0,"REFRIGERATOR");//draw button with 3d effect and gradient color
  
  FTImpl.Cmd_FGColor(cell_colour4);
  FTImpl.Cmd_GradColor(cell_colour4);
  FTImpl.Cmd_Button(0,100,160,100,27,0,"KITCHEN BULB");//draw button with 3d effect and gradient color
  
  FTImpl.Cmd_FGColor(cell_colour5);
  FTImpl.Cmd_GradColor(cell_colour5);
  FTImpl.Cmd_Button(160,100,160,100,27,0,"LAWN LAMP1");//draw button with 3d effect and gradient color

  FTImpl.Cmd_FGColor(cell_colour6);
  FTImpl.Cmd_GradColor(cell_colour6);
  FTImpl.Cmd_Button(320,100,160,100,27,0,"LAWN LAMP2");//draw button with 3d effect and gradient color

  
//
  FTImpl.DLEnd();//end the display list
  //FTImpl.Finish();//render the display list and wait for the completion of the DL
 
}

void Touch()
{
  int32_t  wbutton,hbutton,tagval,tagoption;
  char StringArray[100],StringArray1[100];
  uint32_t ReadWord;
  
  sCTouchXY cTouchXY;
  /*************************************************************************/
  /* Below code demonstrates the usage of touch function. Display info     */
  /* touch raw, touch screen, touch tag, raw adc and resistance values     */
  /*************************************************************************/
  /* Perform the calibration */
  Calibrate();
  
  
  wbutton = FT_DISPLAYWIDTH/8;
  hbutton = FT_DISPLAYHEIGHT/8;
  FTImpl.SetCTouchMode(FT_CTOUCH_MODE_EXTENDED);  //set mode to extended for FT801
  
  Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);//displaying the widgets

  while(1)
  {
   
 
    /* Read the touch screen xy and tag from GetCTouchXY API */
    FTImpl.GetCTouchXY(cTouchXY);


    /* Draw informative text "Touch Screen XY0" with respective touch register values */

    yvalue = cTouchXY.y0;

    xvalue = cTouchXY.x0;


Serial.print("xvalue");
Serial.println(xvalue);
Serial.print("yvalue");
Serial.println(yvalue);
delay(50);

  if((xvalue>0 && xvalue<160) && (yvalue>0 && yvalue<100))
  {   
    
    if (var1==1)
    {
      var1=0;
      cell_colour1=0x009900;
      Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
      digitalWrite(pin1,HIGH);
      }
  
   else if (var1==0)
   {
    var1=1;
    cell_colour1=0xcc0000;
    Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);  
    digitalWrite(pin1,LOW);
    }
    
  }
  
  
  else if((xvalue>160 && xvalue<320) && (yvalue>0 && yvalue<100))
  {   
    if (var2==1)
    {
      var2=0;
      cell_colour2=0x009900;
      Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
      digitalWrite(pin2,HIGH);
      }
  
   else
   {
    var2=1;
    cell_colour2=0xcc0000;
    Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6); 
    digitalWrite(pin2,LOW); 
    }
  }

  else if((xvalue>320 && xvalue<480) && (yvalue>0 && yvalue<100))
  {   
      if (var3==1)
    {
      var3=0;
      cell_colour3=0x009900;
      Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
      digitalWrite(pin3,HIGH);
      }
  
   else
   {
    var3=1;
    cell_colour3=0xcc0000;
    Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
    digitalWrite(pin3,LOW);  
    }
   
  }

  else if((xvalue>0 && xvalue<160) && (yvalue>100 && yvalue<200))
  {   
    
    if (var4==1)
    {
      var4=0;
      cell_colour4=0x009900;
      Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
      digitalWrite(pin4,HIGH);
      }
      
  
   else
   {
    var4=1;
    cell_colour4=0xcc0000;
    Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6); 
    digitalWrite(pin4,LOW); 
    }
   
  }

  else if((xvalue>160 && xvalue<320) && (yvalue>100 && yvalue<200))
  {  
    if (var5==1)
    {
      var5=0;
      cell_colour5=0x009900;
      Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
      digitalWrite(pin5,HIGH);
      }
      
  
   else if (var5==0)
   {
    var5=1;
    cell_colour5=0xcc0000;
    Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
    digitalWrite(pin5,LOW);  
    }
   
  }

  else if((xvalue>320 && xvalue<480) && (yvalue>100 && yvalue<200))
  {   
    
    if (var6==1)
    {
      var6=0;
      cell_colour6=0x009900;
      Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
      digitalWrite(pin6,HIGH);
      }
      
  
   else if (var6==0)
   {
    var6=1;
    cell_colour6=0xcc0000;
    Widgets(cell_colour1,cell_colour2,cell_colour3,cell_colour4, cell_colour5, cell_colour6);
    digitalWrite(pin6,LOW);  
    }
   
   
  }
  
else
  {
  int a=1;//Random operation (of no consequence)
  }


  
}
}
/* bootup the module and demonstrate touch functionality on screen */
void setup()
{
  pinMode(pin1, OUTPUT); 
  pinMode(pin2, OUTPUT); 
  pinMode(pin3, OUTPUT); 
  pinMode(pin4, OUTPUT); 
  pinMode(pin5, OUTPUT); 
  pinMode(pin6, OUTPUT); 
  
  /* Initialize serial print related functionality */
  Serial.begin(9600);
  
  /* Set the Display Enable pin*/   
  Serial.println("--Start Application--");
  if(BootupConfigure())
  {
    //error case - do not do any thing    
  }
    else
  {
    
    
    Touch();
    
  } 
  Serial.println("--End Application--");
}

/* Do nothing */
void loop()
{


}
