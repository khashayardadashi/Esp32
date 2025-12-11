#include "BluetoothSerial.h"
BluetoothSerial BT2; 

void setup() { 
  BT2.begin("slave"); 
  Serial.begin(115200);
}

void loop() {
  if (BT2.available()) {
    String receivedData = BT2.readStringUntil('\n'); 
    Serial.println(receivedData);
  }
}