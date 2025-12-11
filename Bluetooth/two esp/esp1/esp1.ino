#include "BluetoothSerial.h"
BluetoothSerial BT1;
void setup() {
  Serial.begin(115200);
  BT1.begin("master", true);  //Master
  if (BT1.connect("slave")) {
    Serial.println("Connected to Slave");
  } else {
    Serial.println("Failed to connect");
  }
}
void loop() {
  if (!BT1.connected()) {
    Serial.println("Reconnect.......");
    if (BT1.connect("slave")) {
      Serial.println("Reconnected successfully!");
    }
    delay(3000);
    return;
  }
  if (BT1.connected()) {
    BT1.print("message From esp1");
    delay(1000);
  }
}