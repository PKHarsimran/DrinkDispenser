
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13
int val;
int encoder0PinA = 11;
int encoder0PinB = 12;
int encoder0Pos = 0;
 int aState;
 int aLastState;  
#define enCoder0Btn 10
 int counter = 0; 
 // Realy with Pumps !
int R1 = 2;
int R2 = 3;
int R3 = 4;
int R4 = 5;
int R5 = 6;
int R6 = 7;
int R7 = 8;
int R8 = 9;
// Solon
int S1 = A0;
int S2 = A1;
int S3 = A3;
int S4 = A5;

char Data = 0; // data from Serial Connection Aka bluetooth
  int selection = 0;
    int currDispense = 0;
   char *ComboArray[] = {"Rum & Coke", "Gin & Tonic", "Long Island", "Scredriver","Margarita","Gin & Juice","Tequila Sunrise"};
   boolean Dispense = false;
   unsigned long previousTimer  = 0;
   //LiquidCrystal_I2C lcd(0x27);  // set the LCD address to 0x38
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  
void setup()
{
  pinMode ( BACKLIGHT_PIN, OUTPUT );
  lcd.begin (16,2); 
  digitalWrite ( BACKLIGHT_PIN, HIGH );
  pinMode(R1,OUTPUT);
    pinMode(R2,OUTPUT);
      pinMode(R3,OUTPUT);
        pinMode(R4,OUTPUT);
          pinMode(R5,OUTPUT);
            pinMode(R6,OUTPUT);
              pinMode(R7,OUTPUT);
                pinMode(R8,OUTPUT);
                
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);
  pinMode (enCoder0Btn, INPUT);
  Serial.begin(9600);
   lcd.setCursor(0,0);
   lcd.write("Welcome :)");
   // Keep the Relays to off position !
   digitalWrite(R1, HIGH);
      digitalWrite(R2, HIGH);
         digitalWrite(R3, HIGH);
            digitalWrite(R4, HIGH);
               digitalWrite(R5, HIGH);
                  digitalWrite(R6, HIGH);
                     digitalWrite(R7, HIGH);
                        digitalWrite(R8, HIGH);

                        
  aLastState = digitalRead(encoder0PinA);  
}

void loop()
{
  if (Dispense == false)
  currDispense = selection;
bool btnStatus = digitalRead(enCoder0Btn);
//Serial.print ("btnStatus : ");
//Serial.println(btnStatus);
enCoder();

  if (selection > 0 && btnStatus == LOW)
  Dispense = true;
SerialRead();
 //CombosDisplay(selection);
 if (Dispense)
   DrinkSelected();
}
void enCoder()
{
  delay(10);
   aState = digitalRead(encoder0PinA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     if (digitalRead(encoder0PinB) != aState) { 
       counter ++;
       selection = counter;
    CombosDisplay(selection);
     } else {
       counter --;
       selection = counter;
    CombosDisplay(selection);
     }
      if (counter >= 8 || counter <=0 )
    counter = 1;
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
     selection = counter;
}
void SerialRead(){
  if (Serial.available()>0) 
  {
   // DebuggerPrint("Serial aval intiated");
    // wait a bit for the entire message to arrive
     Data = Serial.read();   
     
     Serial.print("I received: ");
     Serial.println(Data);
      //DebuggerPrint(Data); 
     ConditionFun(Data);  
     if (Data == 'D'){
     DrinkSelected();
     Dispense = true;
     }
 }

}
void ConditionFun(char Data){
  switch (Data) {
    case 'A':
    selection= selection + 1;
   DebuggerPrint(String(selection));
    break;
    case 'B':
    if (selection != 0)
    selection = selection - 1 ;
    break ;
  }
  delay(200);
  CombosDisplay(selection);
//  selection = 0;
}
void CombosDisplay(int s) {
 // DebuggerPrint(String(sizeof(ComboArray)));
  int olds = s;
  
    lcd.setCursor(0,0);
    lcd.clear();
    switch (s) {
      case 1 :
      lcd.write(ComboArray[0]);
      break;
      case 2:
      lcd.write(ComboArray[1]);
      break;
      case 3 :
      lcd.write(ComboArray[2]);
      break;
      case 4 :
      lcd.write(ComboArray[3]);
      break;
      case 5 :
      lcd.write(ComboArray[4]);
      break;
      case 6 :
      lcd.write(ComboArray[5]);
      break;
      case 7 :
      lcd.write(ComboArray[6]);
      break;
      case ((sizeof(ComboArray))/2)+1:
      selection = 1;
      break;
    }
}
void DebuggerPrint(String D)
{
  Serial.print ("DeBugger Data: ");
  Serial.println(D);
}
void DrinkSelected()
{

  
   
    switch (currDispense) {
     case 1 :
     // Rum & Coke
      DrinkTimer(50000,0,0,0,0,15000,0,0);
      break;
      case 2:
      // Gin & Tonic
      DrinkTimer(0,50000,0,0,0,0,15000,0);
      break;
      case 3 :
      // Long Island
       DrinkTimer(15000,15000,15000,15000,0,10000,0,15000);
      break;
      case 4 :
      //Scewdriver
       DrinkTimer(0,0,50000,0,0,0,0,15000);
      break;
      case 5 :
        // Margarita
       DrinkTimer(0,0,0,50000,0,0,0,15000);
      break;
      case 6 :
        // Gin & Juice
       DrinkTimer(0,50000,0,0,0,15000,0,0);
      break;
      case 7 :
      // Tequila Sunrise
       DrinkTimer(0,0,0,50000,0,0,0,15000);
      break;
      case ((sizeof(ComboArray))/2)+1:
      selection = 1;
      break;
  }

}
void DrinkTimer (long T1,long T2,long T3,long T4,long T5,long T6,long T7,long T8) {
  unsigned long timer = millis();

Serial.println(timer - previousTimer);
if (T1 != 0) 
digitalWrite(R1,LOW);
if ((unsigned long)(timer - previousTimer) >= T1){
digitalWrite(R1,HIGH); 
T1 = 0 ;}
if (T2 != 0) 
digitalWrite(R2,LOW);
if ((unsigned long)(timer - previousTimer) >= T2){
digitalWrite(R2,HIGH);  
T2 = 0;}
if (T3 != 0) 
digitalWrite(R3,LOW);
if ((unsigned long)(timer - previousTimer) >= T3){
digitalWrite(R3,HIGH);  
T3 = 0;}
if (T4 != 0) 
digitalWrite(R4,LOW);
if ((unsigned long)(timer - previousTimer) >= T4){
digitalWrite(R4,HIGH);  
T4 = 0;}
if (T5 != 0) 
digitalWrite(R5,LOW);
if ((unsigned long)(timer - previousTimer) >= T5){
digitalWrite(R5,HIGH);  
T5 = 0;}
if (T6 != 0) 
digitalWrite(R6,LOW);
if ((unsigned long)(timer - previousTimer) >= T6){
digitalWrite(R6,HIGH);  
T6 = 0 ;}
if (T7 != 0) 
digitalWrite(R7,LOW);
if ((unsigned long)(timer - previousTimer) >= T7){
digitalWrite(R7,HIGH);  
T7 = 0;}
if (T8 != 0) 
digitalWrite(R8,LOW);
if ((unsigned long)(timer - previousTimer) >= T8){
digitalWrite(R8,HIGH);
T8 = 0;}
if ((T1+T2+T3+T4+T5+T6+T7+T8) == 0)
{
   Dispense = false;
   previousTimer = timer;
  Serial.print("PrevValue : ");
  Serial.println(previousTimer);
}
  
}
