#include <WiFi.h>
#include <PubSubClient.h>
#include <PZEM004Tv30.h>
#include <ArduinoJson.h>
#include <WiFiManager.h>
#include <time.h>

const char* DEVICE_ID   = "PZEM-01";
const char* mqtt_server = "109.122.247.177";

PZEM004Tv30 pzem(Serial2, 16, 17);
WiFiClient espClient;
PubSubClient client(espClient);
WiFiManager wm;

struct BufferedRead {
  float v, c, p, e, f, pf;
  time_t timestamp;
};

const size_t MAX_BUFFER = 50;
BufferedRead buffer[MAX_BUFFER];
size_t bufferHead = 0;
size_t bufferTail = 0;
size_t bufferCount = 0;

unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 5000;

unsigned long lastMqttAttempt = 0;
const unsigned long MQTT_RETRY_INTERVAL = 5000;

unsigned long lastWifiCheck = 0;
const unsigned long WIFI_CHECK_INTERVAL = 10000;

unsigned long wifiDownSince = 0;
const unsigned long WIFI_TIMEOUT = 3UL * 60UL * 1000UL;

void pushBuffer(const BufferedRead& item) {
  if (bufferCount < MAX_BUFFER) {
    buffer[bufferHead] = item;
    bufferHead = (bufferHead + 1) % MAX_BUFFER;
    bufferCount++;
  } else {
    buffer[bufferHead] = item;
    bufferHead = (bufferHead + 1) % MAX_BUFFER;
    bufferTail = (bufferTail + 1) % MAX_BUFFER;
  }
}

bool popBuffer(BufferedRead& item) {
  if (bufferCount == 0) return false;
  item = buffer[bufferTail];
  bufferTail = (bufferTail + 1) % MAX_BUFFER;
  bufferCount--;
  return true;
}

String getFormattedTime(time_t epoch) {
  struct tm timeinfo;
  localtime_r(&epoch, &timeinfo);
  char buf[9];
  snprintf(buf, sizeof(buf), "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  return String(buf);
}

void logSystem(const char* level, const char* message) {
  time_t now = time(nullptr);
  String timeStr = (now > 1704067200) ? getFormattedTime(now) : "00:00:00";

  Serial.printf("[%s] [%s] %s\n", timeStr.c_str(), level, message);

  if (client.connected()) {
    StaticJsonDocument<200> logDoc;
    logDoc["device_id"] = DEVICE_ID;
    logDoc["level"]     = level;
    logDoc["msg"]       = message;
    logDoc["ts"]        = timeStr;

    char buf[200];
    serializeJson(logDoc, buf);
    client.publish("pzem/logs", buf);
  }
}

void setup() {
  Serial.begin(115200);

  wm.setConfigPortalTimeout(180);
  if (!wm.autoConnect("PZEM01-SETUP")) {
    delay(2000);
    ESP.restart();
  }

  configTzTime("IRT-3:30", "pool.ntp.org", "time.nist.gov");
  client.setBufferSize(350);
  client.setServer(mqtt_server, 1883);

  logSystem("INFO", "System Boot Complete");
}

void handleWiFi() {
  if (millis() - lastWifiCheck < WIFI_CHECK_INTERVAL) return;
  lastWifiCheck = millis();

  if (WiFi.status() == WL_CONNECTED) {
    wifiDownSince = 0;
    return;
  }

  logSystem("WARN", "WiFi Disconnected");

  if (wifiDownSince == 0) {
    wifiDownSince = millis();
  }

  if (millis() - wifiDownSince >= WIFI_TIMEOUT) {
    wifiDownSince = 0;
    logSystem("ERROR", "WiFi Timeout. Launching Portal...");
    wm.setConfigPortalTimeout(180);
    if (!wm.autoConnect("PZEM01-SETUP")) {
      delay(2000);
      ESP.restart();
    }
  } else {
    WiFi.reconnect();
  }
}

void handleMqtt() {
  if (client.connected()) return;
  if (WiFi.status() != WL_CONNECTED) return;
  if (millis() - lastMqttAttempt < MQTT_RETRY_INTERVAL) return;

  lastMqttAttempt = millis();
  if (client.connect("ESP32_PZEM")) {
    logSystem("INFO", "MQTT Connected");
  } else {
    char errBuf[50];
    snprintf(errBuf, sizeof(errBuf), "MQTT Connect Failed (rc=%d)", client.state());
    logSystem("ERROR", errBuf);
  }
}

void sendBufferedData() {
  BufferedRead bData;
  while (bufferCount > 0 && client.connected()) {
    popBuffer(bData);

    StaticJsonDocument<256> bDoc;
    bDoc["device_id"]   = DEVICE_ID;
    bDoc["v"]           = bData.v;
    bDoc["c"]           = bData.c;
    bDoc["p"]           = bData.p;
    bDoc["e"]           = bData.e;
    bDoc["f"]           = bData.f;
    bDoc["pf"]          = bData.pf;
    bDoc["ts"]          = getFormattedTime(bData.timestamp);
    bDoc["is_buffered"] = true;

    char buf[256];
    serializeJson(bDoc, buf);

    if (!client.publish("pzem/data", buf)) {
      pushBuffer(bData);
      logSystem("WARN", "Publish Buffered Data Failed");
      break;
    }
    client.loop();
  }
}

void readAndPublish() {
  float v  = pzem.voltage();
  float c  = pzem.current();
  float p  = pzem.power();
  float e  = pzem.energy();
  float f  = pzem.frequency();
  float pf = pzem.pf();

  if (isnan(v)) {
    logSystem("ERROR", "PZEM Read Failed (v is NaN)");
    return;
  }

  c  = isnan(c)  ? 0.0f : c;
  p  = isnan(p)  ? 0.0f : p;
  e  = isnan(e)  ? 0.0f : e;
  f  = isnan(f)  ? 0.0f : f;
  pf = isnan(pf) ? 0.0f : pf;

  time_t now = time(nullptr);
  if (now < 1704067200) {
    logSystem("WARN", "NTP Sync Pending...");
    return;
  }

  String timeStr = getFormattedTime(now);

  if (client.connected()) {
    sendBufferedData();

    StaticJsonDocument<256> doc;
    doc["device_id"]   = DEVICE_ID;
    doc["v"]           = v;
    doc["c"]           = c;
    doc["p"]           = p;
    doc["e"]           = e;
    doc["f"]           = f;
    doc["pf"]          = pf;
    doc["ts"]          = timeStr;
    doc["is_buffered"] = false;

    char buf[256];
    serializeJson(doc, buf);

    if (!client.publish("pzem/data", buf)) {
      logSystem("ERROR", "Live Data Publish Failed");
    }
  } else {
    pushBuffer({v, c, p, e, f, pf, now});
    char bufLog[60];
    snprintf(bufLog, sizeof(bufLog), "Data Saved Offline (Buf Count: %u)", bufferCount);
    logSystem("WARN", bufLog);
  }
}

void loop() {
  handleWiFi();
  handleMqtt();

  if (client.connected()) {
    client.loop();
  }

  if (millis() - lastReadTime >= READ_INTERVAL) {
    lastReadTime = millis();
    readAndPublish();
  }
}
