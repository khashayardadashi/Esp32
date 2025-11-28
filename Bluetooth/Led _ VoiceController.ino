#include "BluetoothSerial.h"
BluetoothSerial BT;
String word;
void setup(){
  BT.begin("Esp32");
  Serial.begin(115200);
  pinMode(23, OUTPUT);
  pinMode(15, INPUT);
}
void loop(){
  if(BT.available()){
    w=BT.readString();
    if(word == "روشن شو"){
      digitalWrite(23,1);
      BT.print ("led turn on");
    }
    else if (word == "خاموش شو"){
      digitalWrite(23, 0);
      BT.print("led turn off");
    }
    else{
      digitalWrite(23,0);
    }
  }

}
