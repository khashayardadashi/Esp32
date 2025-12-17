#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 15
#define DHTTYPE DHT11
#define buzzer 4
unsigned long last_time;
LiquidCrystal lcd(23, 22, 21, 19, 18, 5);  //(rs, enable, d4, d5, d6, d7)
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  analogReadResolution(12);
  dht.begin();
  ledcAttachChannel(buzzer,1000,8,0);
  last_time = millis();
  pinMode(15, INPUT);
  lcd.begin(16, 2);
}

void loop() {
  double volt = 0, avg = 0, sum = 0;
  int humidity = dht.readHumidity();
  int temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    lcd.write("Error");
  } else {
    lcd.setCursor(0, 0);
    lcd.print(String("H=") + (String)humidity + "%," + String("T=") + (String)temperature + "C");
  }
  for (int i = 0; i <= 99; i++) {
    volt = analogReadMilliVolts(34) * (3300) / 4096;
    volt /= 1000;
    sum += volt;
  }
  if (millis() - last_time >= 1000) {
    avg = sum / 100;
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("VR=" + (String)volt + "v,V=" + (String)avg + "v");
    if (avg >= 0 && avg < 1) {
      ledcWrite(buzzer,255); // duty 100%
    } else if (avg >= 1 && avg < 2) {
      ledcWrite(buzzer,170); // duty 65%
    } else if (avg >= 2 && avg < 2.4) {
      ledcWrite(buzzer,90); // duty 35%
    } else if (avg >= 2.4) {
      ledcWrite(buzzer, 0); //duty 0%;
    }
    last_time = millis();
  }
}
