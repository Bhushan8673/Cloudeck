#include "Cloudeck.h"

/* =====================================================
   GLOBAL IoT INSTANCE (ONLY ONE, ONLY HERE)
   ===================================================== */
IoTCore IoT;

/* =====================================================
   WIFI ADAPTER IMPLEMENTATION
   ===================================================== */
#ifdef CLOUDLYNK_WIFI_BOARD

WiFiAdapter::WiFiAdapter() : mqttClient(wifiClient) {}

bool WiFiAdapter::connect(const char* ssid,
                          const char* pass,
                          const char* broker,
                          uint16_t port) {

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  mqttClient.setServer(broker, port);

  while (!mqttClient.connected()) {
    mqttClient.connect("Cloudeck-Device");
    delay(500);
  }

  return true;
}

bool WiFiAdapter::publish(const char* topic, const char* msg) {
  return mqttClient.publish(topic, msg);
}

bool WiFiAdapter::subscribe(const char* topic) {
  return mqttClient.subscribe(topic);
}

void WiFiAdapter::loop() {
  mqttClient.loop();
}

void WiFiAdapter::setCallback(
  void (*cb)(const char*, const uint8_t*, unsigned int)) {

  mqttClient.setCallback(
    [cb](char* topic, byte* payload, unsigned int len) {
      cb(topic, payload, len);
    }
  );
}

#endif

/* =====================================================
   IoT CORE (GENERIC FOR ALL PROJECTS)
   ===================================================== */
void IoTCore::begin(NetworkAdapter* net) {
  adapter = net;
}

bool IoTCore::connect(const char* ssid,
                      const char* pass,
                      const char* broker,
                      uint16_t port) {
  return adapter->connect(ssid, pass, broker, port);
}

bool IoTCore::publish(const char* topic, const char* msg) {
  return adapter->publish(topic, msg);
}

bool IoTCore::subscribe(const char* topic) {
  return adapter->subscribe(topic);
}

void IoTCore::run() {
  adapter->loop();
}

void IoTCore::onMessage(
  void (*cb)(const char*, const uint8_t*, unsigned int)) {
  adapter->setCallback(cb);
}

/* =====================================================
   🚗 OPTIONAL CAR FEATURE
   ===================================================== */
#ifdef CLOUDLYNK_ENABLE_CAR

static uint8_t CAR_IN1, CAR_IN2, CAR_IN3, CAR_IN4;
static bool carAttached = false;

void IoTCore::attachCarPins(uint8_t in1, uint8_t in2,
                            uint8_t in3, uint8_t in4) {
  CAR_IN1 = in1;
  CAR_IN2 = in2;
  CAR_IN3 = in3;
  CAR_IN4 = in4;

  pinMode(CAR_IN1, OUTPUT);
  pinMode(CAR_IN2, OUTPUT);
  pinMode(CAR_IN3, OUTPUT);
  pinMode(CAR_IN4, OUTPUT);

  carStop();
  carAttached = true;
}

void IoTCore::carStop() {
  if (!carAttached) return;

  digitalWrite(CAR_IN1, LOW);
  digitalWrite(CAR_IN2, LOW);
  digitalWrite(CAR_IN3, LOW);
  digitalWrite(CAR_IN4, LOW);
}

void IoTCore::carForward() {
  if (!carAttached) return;

  digitalWrite(CAR_IN1, HIGH);
  digitalWrite(CAR_IN2, LOW);
  digitalWrite(CAR_IN3, LOW);
  digitalWrite(CAR_IN4, HIGH);
}

void IoTCore::carBackward() {
  if (!carAttached) return;

  digitalWrite(CAR_IN1, LOW);
  digitalWrite(CAR_IN2, HIGH);
  digitalWrite(CAR_IN3, HIGH);
  digitalWrite(CAR_IN4, LOW);
}

void IoTCore::carLeft() {
  if (!carAttached) return;

  digitalWrite(CAR_IN1, LOW);
  digitalWrite(CAR_IN2, LOW);
  digitalWrite(CAR_IN3, LOW);
  digitalWrite(CAR_IN4, HIGH);
}

void IoTCore::carRight() {
  if (!carAttached) return;

  digitalWrite(CAR_IN1, HIGH);
  digitalWrite(CAR_IN2, LOW);
  digitalWrite(CAR_IN3, LOW);
  digitalWrite(CAR_IN4, LOW);
}

#endif
