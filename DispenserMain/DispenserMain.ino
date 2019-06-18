/*
 * Displays text sent over the serial port (e.g. from the Serial Monitor) on
 * an attached LCD.
 */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13

int R1 = 31;
int R2 = 33;
int R3 = 35;
int R4 = 37;
int R5 = 39;
int R6 = 41;
int R7 = 43;
int R8 = 45;
char Data = 0;
  int selection = 0;
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
  char *ComboArray[] = {"Rum & Coke", "Gin & Tonic", "Long Island", "Scredriver","Margarita","Gin & Juice","Tequila Sunrise"};
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
void DrinkSelected(int sel)
{
  
}
