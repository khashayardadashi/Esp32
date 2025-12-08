#include "BluetoothSerial.h"
BluetoothSerial BT2;
#define RXD2 16  
#define TXD2 17  

void setup() { 
  BT2.begin("Esp"); 
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); 
}

void loop() {
  if (Serial2.available()) {
    String receivedData = Serial2.readStringUntil('\n'); 
    BT2.print(receivedData);
  }
}

