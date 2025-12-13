#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

BLEServer* server;
BLECharacteristic* characteristic;

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32_BLE");

  server = BLEDevice::createServer();

  BLEService* service = server->createService("1234");

  characteristic = service->createCharacteristic(
    "Test",
    BLECharacteristic::PROPERTY_READ |
    BLECharacteristic::PROPERTY_WRITE
  );

  characteristic->setValue("Hello BLE");

  service->start();

  BLEAdvertising* advertising = BLEDevice::getAdvertising();
  advertising->start();

  Serial.println("BLE Ready!");
}

void loop() {
  delay(2000);
  characteristic->setValue("Hello");
}

