#include <Cloudeck.h>

/*
  Basic MQTT Example using Cloudeck
  --------------------------------
  This example shows how to:
  - Connect WiFi
  - Connect MQTT broker
  - Keep connection alive
*/

WiFiAdapter wifi;

const char* WIFI_SSID   = "YOUR_WIFI_NAME";
const char* WIFI_PASS   = "YOUR_WIFI_PASSWORD";
const char* MQTT_BROKER = "BROKER_IP";   // e.g. 51.20.xxx.xxx
const uint16_t MQTT_PORT = 1883;

void setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println("🚀 Cloudeck Basic MQTT Example");

  IoT.begin(&wifi);
  IoT.connect(WIFI_SSID, WIFI_PASS, MQTT_BROKER, MQTT_PORT);

  Serial.println("✅ Connected to MQTT via Cloudeck");
}

void loop() {
  IoT.run();   // REQUIRED
}
