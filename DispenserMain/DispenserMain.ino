/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13

int R1 = 2;
int R2 = 3;
int R3 = 4;
int R4 = 5;
int R5 = 6;
int R6 = 7;
int R7 = 8;
int R8 = 9;
char Data = 0;
  int selection = 0;
   char *ComboArray[] = {"Rum & Coke", "Gin & Tonic", "Long Island", "Scredriver","Margarita","Gin & Juice","Tequila Sunrise"};
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

                        
 
}

void loop()
{
SerialRead();

 if (Data == 'D')
     DrinkSelected();
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
     if (Data == 'D')
     DrinkSelected();
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
    switch (selection) {
     case 1 :
     // Rum & Coke
      DrinkTimer(50000,0,0,0,0,150000,0,0);
      break;
      case 2:
      // Gin & Tonic
      DrinkTimer(0,50000,0,0,0,0,150000,0);
      break;
      case 3 :
      // Long Island
       DrinkTimer(15000,15000,15000,15000,0,100000,0,150000);
      break;
      case 4 :
    DrinkTimer(0,0,50000,0,0,0,0,150000);
      break;
      case 5 :
        // Margarita
       DrinkTimer(0,0,0,50000,0,0,0,150000);
      break;
      case 6 :
        // Gin & Juice
       DrinkTimer(0,50000,0,0,0,150000,0,0);
      break;
      case 7 :
      // Tequila Sunrise
       DrinkTimer(0,0,0,50000,0,0,0,150000);
      break;
      case ((sizeof(ComboArray))/2)+1:
      selection = 1;
      break;
  }
}
void DrinkTimer (long T1,long T2,long T3,long T4,long T5,long T6,long T7,long T8) {
  unsigned long timer = millis();
  Serial.println(timer);
    if (T1 != 0) 
      digitalWrite(R1,LOW);
      if (timer >= T1)
        digitalWrite(R1,HIGH);

     if (T2 != 0) 
                  digitalWrite(R2,LOW);
      if (timer >= T2)
        digitalWrite(R2,HIGH);  

            if (T3 != 0) 
                  digitalWrite(R3,LOW);
      if (timer >= T3)
        digitalWrite(R3,HIGH);  

            if (T4 != 0) 
                  digitalWrite(R4,LOW);
      if (timer >= T4)
        digitalWrite(R4,HIGH);  

            if (T5 != 0) 
                  digitalWrite(R5,LOW);
      if (timer >= T5)
        digitalWrite(R5,HIGH);  

            if (T6 != 0) 
                  digitalWrite(R6,LOW);
      if (timer >= T6)
        digitalWrite(R6,HIGH);  

            if (T7 != 0) 
                  digitalWrite(R7,LOW);
      if (timer >= T7)
        digitalWrite(R7,HIGH);  

            if (T8 != 0) 
                  digitalWrite(R8,LOW);
      if (timer >= T8)
        digitalWrite(R8,HIGH);         
}
