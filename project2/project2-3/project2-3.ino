#include <LiquidCrystal.h>
const int rs = 4, en = 5, d4 = 18, d5 = 19, d6 = 21, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int in1 = 35;
int in2 = 32;
int ena = 34;
int in3 = 33;
int in4 = 25;
int enb = 26;
int ry;
int rx;
int dutyRight;
int dutyLeft;
int dutyUp;
int dutyDown;
int speed;
int speed1;
int speed2;
void setup() {
  lcd.begin(16, 2);
  analogReadResolution(10);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  ledcAttachChannel(ena, 500, 8, 0);
  ledcAttachChannel(enb, 500, 8, 0);
}
void loop() {
  ry = analogRead(14);
  rx = analogRead(27);
  if (ry > 720 && rx == 720) {
    dutyUp = map(ry, 720, 1023, 0, 255);
    speed = map(dutyUp, 0, 255, 0, 100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("L:" + (String)speed + "R:" + (String)speed);
    lcd.setCursor(0, 1);
    lcd.print("Dir : Up");
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    digitalWrite(in3, 1);
    digitalWrite(in4, 0);
    ledcWrite(enb, dutyUp);
    ledcWrite(ena, dutyUp);
    delay(500);
  } 
  else if (ry > 720 && rx > 720) {
    dutyUp = map(ry, 720, 1023, 0, 255);
    speed = map(dutyUp, 0, 255, 0, 100);
    dutyRight = map(rx, 720, 1023, 0, 255);
    speed1 = map(dutyRight, 0, 255, 0, 100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("L:" + (String)speed + "R:" + (String)speed1);
    lcd.setCursor(0, 1);
    lcd.print("Dir : Up & R");
    digitalWrite(in1, 1);
    digitalWrite(in2, 0);
    digitalWrite(in3, 1);
    digitalWrite(in4, 0);
    ledcWrite(enb, dutyRight);
    ledcWrite(ena, dutyUp);
  } 
  else if (ry > 720 && rx < 720) {
    dutyUp = map(ry, 720, 1023, 0, 255);
    speed = map(dutyUp, 0, 255, 0, 100);
    dutyLeft = map(rx, 720, 0, 0, 255);
    speed2=map(dutyLeft,0,255, 0,100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("L:" + (String)speed2 + "R:" +(String)speed );
    lcd.setCursor(0,1);
    lcd.print( "Dir : Up & L");
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    digitalWrite(in3,1);
    digitalWrite(in4,0);
    ledcWrite(enb,dutyUp);
    ledcWrite(ena,dutyLeft);
  } 
    else if (ry == 720 && rx > 720) {
    dutyRight = map(rx, 720, 1023, 0, 255);
    speed1 = map(dutyRight, 0, 255, 0, 100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("L:0 R:" + (String)speed1);
    lcd.setCursor(0, 1);
    lcd.print("Dir : R");
    digitalWrite(in1, 0);
    digitalWrite(in2, 0);
    digitalWrite(in3, 1);
    digitalWrite(in4, 0);
    ledcWrite(enb, dutyRight);
    ledcWrite(ena, 0);
  } 
    else if (ry == 720 && rx < 720) {
    dutyLeft = map(rx, 720, 0, 0, 255);
    speed2=map(dutyLeft,0,255, 0,100);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("L:" + (String)speed2 + "R:stop" );
    lcd.setCursor(0,1);
    lcd.print( "Dir : L");
    digitalWrite(in1,1);
    digitalWrite(in2,0);
    digitalWrite(in3,0);
    digitalWrite(in4,0);
    ledcWrite(ena,dutyLeft);
    ledcWrite(enb,0);
  } 
  else if (ry < 720 && rx == 720) {
    dutyDown = map(ry, 720, 0, 0, 255);
    speed = map(dutyDown, 0, 255, 0, 100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("L:" + (String)speed + "R:" + (String)speed);
    lcd.setCursor(0, 1);
    lcd.print("Dir : Down");
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);
    ledcWrite(enb, dutyDown);
    ledcWrite(ena, dutyDown);
  } 
  else if (ry < 720 && rx >720) {
    dutyDown = map(ry, 720, 0, 0, 255);
    speed = map(dutyDown, 0, 255, 0, 100);
    dutyRight = map(rx, 720, 1023, 0, 255);
    speed1 = map(dutyRight, 0, 255, 0, 100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("L:" + (String)speed + "R:" + (String)speed1);
    lcd.setCursor(0, 1);
    lcd.print("Dir : Down & R");
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);
    ledcWrite(enb, dutyRight);
    ledcWrite(ena, dutyDown);
  } 
  else if (ry < 720 && rx < 720) {
    dutyDown = map(ry, 720, 0, 0, 255);
    speed = map(dutyDown, 0, 255, 0, 100);
    dutyLeft = map(rx, 720, 0, 0, 255);
    speed2=map(dutyLeft,0,255, 0,100);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("L:" + (String)speed2 + "R:" + (String)speed);
    lcd.setCursor(0, 1);
    lcd.print("Dir : Down & L");
    digitalWrite(in1, 0);
    digitalWrite(in2, 1);
    digitalWrite(in3, 0);
    digitalWrite(in4, 1);
    ledcWrite(enb, dutyDown);
    ledcWrite(ena, dutyLeft);
  } else {
    lcd.setCursor(0, 0);
    lcd.print("MOTORS STOP");
  }
}
