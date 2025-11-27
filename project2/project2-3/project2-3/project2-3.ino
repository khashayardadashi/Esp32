#include <LiquidCrystal.h>
const int rs = 4, en = 5, d4 =18 , d5 = 19, d6 =21 , d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int in1 =35;
int in2=32;
int ena=34;
int in3 =33;
int in4=25;
int enb=26;
int ry;
int dutyUp;
int dutyDown;
int speed;
void setup(){
  lcd.begin(16,2);
  analogReadResolution(10);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  ledcAttachChannel(ena,500,8,0);
  ledcAttachChannel(enb,500,8,0);
}
void loop(){
  ry=analogRead(14);
  if(ry >720){
    dutyUp = map(ry, 720, 1023, 0, 255);
    speed = map(dutyUp , 0,255,0,100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SPEED:" + (String)speed );
    lcd.setCursor(0,1);
    lcd.print( "Direction : Up");
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    digitalWrite(in3,1);
    digitalWrite(in4,0);
    ledcWrite(enb,dutyUp);
    ledcWrite(ena,dutyUp);
    delay(500);
  }
  else if( ry < 720){
    dutyDown = map(ry, 720,0, 0, 255);
    speed = map(dutyDown , 0,255,0,100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SPEED:" + (String)speed );
    lcd.setCursor(0,1);
    lcd.print( "Direction : Down");
    digitalWrite(in1,0);
    digitalWrite(in2,1);
    digitalWrite(in3,0);
    digitalWrite(in4,1);
    ledcWrite(enb,dutyDown);
    ledcWrite(ena,dutyDown);
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("MOTORS STOP");
  }
}

