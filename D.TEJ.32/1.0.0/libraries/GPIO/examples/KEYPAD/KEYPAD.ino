/*
 * @file KEYPAD.ino
 * 
 * @brief Simple 4*3 Keypad Application
 * @detail When you press a key in the keypad, corresponding value will be displayed in serial monitor
 * 
 * Aries V2.0 reference: https://vegaprocessors.in/files/PINOUT_ARIES%20V2.0_.pdf   
 
  *** Keypad ***  
 *  Connections:  
 *  4*3 matrix Keypad   - Aries 
 *    1                 -  GPIO-9
 *    2                 -  GPIO-8
 *    3                 -  GPIO-7
 *    4                 -  GPIO-6
 *    5                 -  GPIO-5
 *    6                 -  GPIO-4 
 *    7                 -  GPIO-3
 * 
*/


#define NO_CHAR '$'
#define KEYPAD_START 3


char keypad()
{
  /*
  @  current code req pulldwn res (1k) conctd to the column pins to be ground, and connect  it with gpio pins 7,8,9 respc..
  @if u need to avoid the pulldwn res , change the values --> init_val=0,req_val=1 <--  to --> init_val=1,req_val=0 <--  respec....
  @ if u use --> init_val=1,req_val=0 <-- format then connect the column pins directly to gpio pins 7,8 & 9 .
  */

//  int init_val=1,req_val=0;  
  int init_val=0,req_val=1;  
  

  digitalWrite(3, init_val);
  digitalWrite(4, init_val);
  digitalWrite(5, init_val);
  digitalWrite(6, init_val);

  for (char i = 0; i < 4; i++)
  {
    digitalWrite(7, init_val);
    digitalWrite(8, init_val);
    digitalWrite(9, init_val);
    
    digitalWrite(KEYPAD_START + i, req_val);

    if (i < 3)
    {
      if (digitalRead(7) == req_val)
        return ('1' + (i * 3));
      if (digitalRead(8) == req_val)
        return ('1' + (i * 3) + 1);
      if (digitalRead(9) == req_val)
        return ('1' + (i * 3) + 2);
    }
    else
    {
      if (digitalRead(7) == req_val)
        return ('*');
      if (digitalRead(8) == req_val)
        return ('0');
      if (digitalRead(9) == req_val)
        return ('#');
    }

    digitalWrite(i, init_val);
  }

  return '$';
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key; 
  
  while (1){    
    key = keypad();
    if (key != NO_CHAR){
      Serial.print(" Key : ");     
      Serial.println(key);
    }
    delay(200);
  }
}
