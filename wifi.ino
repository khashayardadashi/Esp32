#include <WiFi.h>
#include <HTTPClient.h>

// -------- WiFi Config --------
const char* ssid = "";
const char* password = "";

// -------- Server URL --------
const char* serverUrl = "http://192.168.1.10/esp32/index.php"; //local host

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP: " + WiFi.localIP().toString());
}

void loop() {

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int commaIndex = input.indexOf(',');
    if (commaIndex == -1) {
      Serial.println("Invalid format! Use name,status");
      return;
    }

    String name = input.substring(0, commaIndex);
    String status = input.substring(commaIndex + 1);

    sendDataGET(name, status);
  }
}
void sendDataGET(String name, String status) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    return;
  }

  // Encode URL
  name.replace(" ", "%20");
  status.replace(" ", "%20");

String url = String(serverUrl) + "?name=" + name + "&status=" + status + "&esp32=1";


  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("data send");
  } else {
    Serial.println("Error in HTTP request");
  }

  http.end();
}

