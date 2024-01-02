/*
  @file tic-tac-toe.ino
  @brief play tic-tac-toe on serial monitor
  @detail play tic-tac-toe game on serial monitor

  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/play-tic-tac-toe-on-serial-monitor-using-vega-aries-board/
   
 
  *  To use it, you need to connect the ARIES to USB and callthe 
  *  Serial monitor from inside Arduino IDE: Menu tools -> Serial monitor
  *  (or pressing Ctrl + Shift + M)
  *  
  *  Move using the 1...9 keys (plus Enter) from inside the Serial Monitor:
  *  
  *   1 | 2 | 3
  *  ---+---+---
  *   4 | 5 | 6
  *  ---+---+---
  *   7 | 8 | 9

  * by - Giovanni Verrua
*/

#include <esp8266.h>
ESP8266Class mySerial(0);

int gameStatus = 0;
int whosplaying = 0; //0 = Arduino, 1 = Human 

int winner  = -1;  //-1 = Playing, 0 = Draw, 1 = Human, 2 = CPU


int board[]={0,0,0,  
             0,0,0,
             0,0,0}; //0 = blank, 1 = human (circle),  2 = computer (cross)
          
//--------------------------------------------------------------------------------------------------------
void  playhuman() {
     
  int humanMove = -1;     
  bool stayInLoop = true;
  
  while(stayInLoop) {
                
    mySerial.println(F("Make your move"));
    
    while (mySerial.available() && mySerial.read());  // empty buffer
    while (!mySerial.available());                 // wait  for data
    
    if (mySerial.available()) {  //data available.
    
      int humanMove = mySerial.read() - 48;     //mySerial.read() return the  ascii value of the pressed key. The "1" ascii value is 49. 
      mySerial.println(humanMove);
      
      if (humanMove  >=0 && humanMove <=9) {
      
        if (board[humanMove-1] != 0) {
          mySerial.println(F("Error - Cell already in use"));                
          stayInLoop = true;
        }
        else {
          stayInLoop = false;                
          board[humanMove-1] = 1; //remember: the player uses the 1..9 keys, but the array index starts by 0  (9 cells = 0..8)
        }    
      }
      else {
        mySerial.println(F("type error (just 1 to 9)"));                
        stayInLoop = true;
      }      
    }      
  }
}

//--------------------------------------------------------------------------------------------------------
void  playcpu() {
          
  int cpumove = checkboard(2);  //2 = cpu  let's  check if there's a cpu's winner move
  
  if (cpumove >=0) {
    board[cpumove]  = 2;    //cpu's winner move
  }
  else {    
    cpumove = checkboard(1);  //1=player check if the player has a chance to win (2 circles and an empty cell  in a row)   
    if (cpumove >=0) {  
      board[cpumove] = 2;  //this move will break the player's winner move
    }     
    
    //there's no possible winner move neither for the cpu, nor for the human,  I will put an "X" in a random cell
    while (cpumove < 0) {                
      int randomMove = random(10);
      if (randomMove >=0 && randomMove  <=8 && board[randomMove] == 0) {
        cpumove = randomMove;
      }        
    }        
    board[cpumove] = 2;
  } 
}

//--------------------------------------------------------------------------------------------------------
int checkboard(int x) {   //x = 1 -> player, x = 2 -> cpu
  //full case
  if(board[0]==0 && board[1]==x && board[2]==x)  return  0;       //  0 1 1 
                                                                  //  . . .
                                                                  //  . . .
                                                             
  else if(board[0]==x && board[1]==0 && board[2]==x)  return  1;  //  1 0 1 
                                                                  //  . . .
                                                                  //  . . .
                                                             
  else if(board[0]==x && board[1]==x && board[2]==0)  return  2;  //  1 1 0
                                                                  //  . . .
                                                                  //  . . .                                                                   
  //-------------------------------------------------
  else if(board[3]==0 && board[4]==x && board[5]==x)  return  3;  //  . . .
                                                                  //  0 1 1
                                                                  //  . . .
                                                               
  else if(board[3]==x && board[4]==0 && board[5]==x)  return  4;  //  . . .  
                                                                  //  1 0 1
                                                                  //  . . .                                                                 
  
  else if(board[3]==x && board[4]==x && board[5]==0)  return  5;  //  . . .
                                                                  //  1 1 0
                                                                  //  . . .
  //-------------------------------------------------
  else if(board[6]==0 && board[7]==x && board[8]==x)  return  6;  //  . . .
                                                                  //  . . .
                                                                  //  0 1 1
                                                               
  else if(board[6]==x && board[7]==0 && board[8]==x)  return  7;  //  . . .  
                                                                  //  . . .
                                                                  //  1 0 1
  
  else if(board[6]==x && board[7]==x && board[8]==0)  return  8;  //  . . .
                                                                  //  . . .
                                                                  //  1 1 0
  
  //-------------------------------------------------
  else if(board[0]==0 && board[3]==x && board[6]==x)  return  0;  //  0 . .
                                                                  //  1 . .
                                                                  //  1 . .
  
  else if(board[0]==x && board[3]==0 && board[6]==x)  return  3;  //  1 . .
                                                                  //  0 . .
                                                                  //  1 . .
  
  else if(board[0]==x && board[3]==x && board[6]==0)  return  6;  //  1 . .
                                                                  //  1 . .
                                                                  //  0 . .  
                                                             
  //-------------------------------------------------
  else if(board[1]==0 && board[4]==x && board[7]==x)  return  1;  //  . 0 .
                                                                  //  . 1 .
                                                                  //  . 1 .
  
  else if(board[1]==x && board[4]==0 && board[7]==x)  return  4;  //  . 1 .
                                                                  //  . 0 .
                                                                  //  . 1 .  
  
  else if(board[1]==x && board[4]==x && board[7]==0)  return  7;  //  . 1 .
                                                                  //  . 1 .
                                                                  //  . 0 .  
                                                              
  //-------------------------------------------------
  else if(board[2]==0 && board[5]==x && board[8]==x)  return  2;  //  . . 0 
                                                                  //  . . 1 
                                                                  //  . . 1 
  
  else if(board[2]==x && board[5]==0 && board[8]==x)  return  5;  //  . . 1 
                                                                  //  . . 0 
                                                                  //  . . 1   
  
  else if(board[2]==x && board[5]==x && board[8]==0)  return  8;  //  . . 1 
                                                                  //  . . 1
                                                                  //  . . 0
                                                              
  //-------------------------------------------------
  else if(board[0]==0 && board[4]==x && board[8]==x)  return  0;  //  0 . . 
                                                                  //  . 1 . 
                                                                  //  . . 1 
  
  else if(board[0]==x && board[4]==0 && board[8]==x)  return  4;  //  1 . . 
                                                                  //  . 0 .
                                                                  //  . . 1   
  
  else if(board[0]==x && board[4]==x && board[8]==0)  return  8;  //  1 . . 
                                                                  //  . 1 .
                                                                  //  . . 0
  
  //-------------------------------------------------
  else if(board[2]==0 && board[4]==x && board[6]==x)  return  2;  //  . . 0 
                                                                  //  . 1 . 
                                                                  //  1 . . 
  
  else if(board[2]==x && board[4]==0 && board[6]==x)  return  4;  //  . . 1 
                                                                  //  . 0 . 
                                                                  //  1 . . 
    
  else if(board[2]==x && board[4]==x && board[6]==0)  return  6;  //  . . 1 
                                                                  //  . 1 . 
                                                                  //  0 . . 
  
  else                                                return  -1;
}

//--------------------------------------------------------------------------------------------
void  checkWinner() {    //check the board to see if there is a winner

  winner  = 3;  //3=draft, 1= winner->player, 2=winner->cpu
    
  // circles win?
  if(board[0]==1 && board[1]==1 && board[2]==1)          winner=1;   
  else if(board[3]==1 && board[4]==1 && board[5]==1)     winner=1;   
  else if(board[6]==1 && board[7]==1 && board[8]==1)     winner=1;     
  else if(board[0]==1 && board[3]==1 && board[6]==1)     winner=1;   
  else if(board[1]==1 && board[4]==1 && board[7]==1)     winner=1;   
  else if(board[2]==1 && board[5]==1 && board[8]==1)     winner=1;     
  else if(board[0]==1 && board[4]==1 && board[8]==1)     winner=1;   
  else if(board[2]==1 && board[4]==1 && board[6]==1)     winner=1; 
    
  // crosses win?
  else if(board[0]==2 && board[1]==2 && board[2]==2)     winner=2;   
  else if(board[3]==2 && board[4]==2 && board[5]==2)     winner=2;   
  else if(board[6]==2 && board[7]==2 && board[8]==2)     winner=2;     
  else if(board[0]==2 && board[3]==2 && board[6]==2)     winner=2;   
  else if(board[1]==2 && board[4]==2 && board[7]==2)     winner=2;   
  else if(board[2]==2 && board[5]==2 && board[8]==2)     winner=2;     
  else if(board[0]==2 && board[4]==2 && board[8]==2)     winner=2;   
  else if(board[2]==2 && board[4]==2 && board[6]==2)     winner=2;   

  if (winner == 3) {      
     for(int i=0;i<9;i++) if (board[i]==0)  winner=0;  //there are some empty cell yet. 
  }   
}

//--------------------------------------------------------------------------------------------------------------
void  resetGame() {
  mySerial.println("Resetting game...");
  for(int i=0;i<9;i++)  board[i]=0; 
  winner = 0;
  gameStatus = 0; 
}

//--------------------------------------------------------------------------------------------------------------
void  boardDrawing() {
  
  mySerial.println("");
  mySerial.print(F("  ")); mySerial.print(charBoard(0)); mySerial.print(F(" | ")); mySerial.print(charBoard(1)); mySerial.print(F(" | "));  mySerial.println(charBoard(2)); 
  mySerial.println(F(" ---+---+---")); 
  mySerial.print(F("  ")); mySerial.print(charBoard(3)); mySerial.print(F(" | ")); mySerial.print(charBoard(4)); mySerial.print(F(" | "));  mySerial.println(charBoard(5));  
  mySerial.println(F(" ---+---+---")); 
  mySerial.print(F("  ")); mySerial.print(charBoard(6)); mySerial.print(F(" | ")); mySerial.print(charBoard(7)); mySerial.print(F(" | "));  mySerial.println(charBoard(8)); 
  mySerial.println("");
}



//--------------------------------------------------------------------------------------------------------------
String  charBoard(int x) {
  if (board[x] == 0) return " ";       
  if (board[x] == 1) return "o";
  if (board[x] == 2) return "x";  
  
  return "?";  //error trap; it shouldn't pass here.
}


// the setup function runs once when you press reset or power the board
void  setup() {
  // initialize serial communication at 115200 bits per second:
  mySerial.begin(115200);
  delay(1000); 
  randomSeed(analogRead(0));  //resetting the random function.
}


// the loop function runs over and over again forever
void  loop() {         
  if(gameStatus == 0) {     
    mySerial.println(F("Let's  begin..."));  
  
    whosplaying = 2;
    while ( whosplaying <0 ||  whosplaying > 1) {
      whosplaying = random(2);  
    }
    
    gameStatus  = 1;
    winner = 0;
  }
  //---------------------------------------------
  if(gameStatus == 1) {   //start
  
    if (whosplaying == 1) boardDrawing();
    
    while (winner == 0) {  //game main loop
      
      if (whosplaying == 0) { 
        mySerial.println("CPU turn:");    
        playcpu();  
        whosplaying =1; 
      }
      else { 
        mySerial.println("Player turn:"); 
        playhuman(); 
        whosplaying =0; 
      }
      
      boardDrawing();
      checkWinner();  //this will assign the winner variable
      
      if (winner > 0) {
        mySerial.println("");
        if (winner == 3) 
          mySerial.print(F("Draft!"));
        else {
          mySerial.print(F("The winner is "));
          if (winner  == 1) mySerial.println(F("the human")); else mySerial.println(F("the CPU")); 
        }               
      }
    }
    resetGame();      
    mySerial.println("");
    delay(2000);
    mySerial.println("");
  }
}
