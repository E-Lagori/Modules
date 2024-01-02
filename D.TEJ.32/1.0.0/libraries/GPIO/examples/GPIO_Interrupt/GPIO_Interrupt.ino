/*
  @file GPIO_Interrupt.ino
  @brief GPIO Interrupt demo
  @detail Green LED will turn on when button-1 is pressed 
  
  Useful Links:
    Official Site: https://vegaprocessors.in/
    Development Boards: https://vegaprocessors.in/devboards/
    Blogs : https://vegaprocessors.in/blog/how-to-test-interrupt-with-aries-v2/

  NOTE : GPIO0 - GPIO11 support external interrupts

   -------------------------------------
   |  Peripheral  |  Interrupt Number  |
   -------------------------------------
   |    GPIO-0    |         10         |
   |    GPIO-1    |         11         |
   |    GPIO-2    |         12         |
   |    GPIO-3    |         13         |
   |    GPIO-4    |         14         |
   |    GPIO-5    |         15         |
   |    GPIO-6    |         16         |
   |    GPIO-7    |         17         |
   |    GPIO-8    |         18         |
   |    GPIO-9    |         19         |
   |    GPIO-10   |         20         |
   |    GPIO-11   |         21         |
   -------------------------------------
*/

#define PUSH_BUTTON 18       // BTN-1 connected to GPIO-18

const byte ledPin = 22;      // Green LED connected to GPIO-22
const byte interruptPin = 0; // GPIO Number

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins
  pinMode(ledPin, OUTPUT);  
  pinMode(PUSH_BUTTON, INPUT);
  pinMode(interruptPin, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, 0);  // attachInterrupt(interrupt number, void (*irq_handler)(), mode);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(ledPin, HIGH);              // Green LED is OFF
  Serial.println("Waiting for Interrupt.....");
  
  if(digitalRead(PUSH_BUTTON) == LOW)      // True when button-1 is pressed  (LOW State)
    digitalWrite(interruptPin, HIGH);
}

// the blink function/ISR runs whenever interrupt occurs
void blink() {          
  // Interrupt Service Routine (ISR)                       
  Serial.print("Interrupt occur at GPIO-");
  Serial.println(interruptPin);
  digitalWrite(ledPin, LOW);               // Green LED is ON
  
  if(digitalRead(PUSH_BUTTON) == HIGH)     // True when button-1 is not pressed (HIGH State)
    digitalWrite(interruptPin, LOW);
}