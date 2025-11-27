#include <LiquidCrystal.h>


const int rs = 23, en = 22, d4 = 19, d5 = 18, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int readAnalog; // 0 - 4095
float Temp;
void setup(){
  lcd.begin(16, 2);
}
void loop(){
  readAnalog=analogRead(15);
  Temp= readAnalog * (3.3)/4096;
  Temp= Temp*100; // 1c -> 10mv
  lcd.setCursor(0,0);
  lcd.print("Temperature : ");
  lcd.setCursor(0,1);
  lcd.print((String) Temp + " C ");
  delay(1000);
}