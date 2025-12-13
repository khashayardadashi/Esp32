#include "BluetoothSerial.h"
BluetoothSerial BT;
String w;
void setup() {
  BT.begin("Slave");
  pinMode(18, OUTPUT);
  pinMode(22, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  if (BT.available()) {
    w = BT.readString();
    if (w == "ON1") {
      digitalWrite(18, 1);
    } else if (w == "OFF1") {
      digitalWrite(18, 0);
    } else if (w == "ON2") {
      digitalWrite(22, 1);
    } else if (w == "OFF2") {
      digitalWrite(22, 0);
    }
  }
}