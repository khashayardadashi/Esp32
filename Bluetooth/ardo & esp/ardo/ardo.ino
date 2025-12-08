#include "DHT.h"
DHT dht(8, DHT11);
int r;
int cal;
void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature(); 
  Serial.println((String)temperature + " c"); 
  delay(2000); 
}