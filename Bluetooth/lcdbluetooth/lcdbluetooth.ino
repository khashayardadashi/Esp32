#include <LiquidCrystal.h>
#include "BluetoothSerial.h"
const int rs = 15, en = 18, d4 = 19, d5 = 21, d6 = 22, d7 = 23;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
BluetoothSerial BT;
String w;
void setup() {
  lcd.begin(16, 2);
  BT.begin("LCD"); 
}

void loop() {
  lcd.setCursor(0, 1);
  if(BT.available()){
    w=BT.readString();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(w);
  }
}
