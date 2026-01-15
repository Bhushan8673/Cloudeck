#ifndef CLOUDECK_H
#define CLOUDECK_H

#include <Arduino.h>

/* =====================================================
   FEATURE FLAGS (ENABLE ONLY WHAT YOU NEED)
   ===================================================== */
// Uncomment only if project needs CAR feature
#define CLOUDLYNK_ENABLE_CAR

/* =====================================================
   BOARD DETECTION
   ===================================================== */
#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #define CLOUDLYNK_WIFI_BOARD
#elif defined(ESP32)
  #include <WiFi.h>
  #define CLOUDLYNK_WIFI_BOARD
#else
  #define CLOUDLYNK_BASIC_BOARD
#endif

#ifdef CLOUDLYNK_WIFI_BOARD
  #include <PubSubClient.h>
#endif

/* =====================================================
   NETWORK ADAPTER (CORE – USED BY ALL PROJECTS)
   ===================================================== */
class NetworkAdapter {
public:
  virtual bool connect(const char*, const char*, const char*, uint16_t) = 0;
  virtual bool publish(const char*, const char*) = 0;
  virtual bool subscribe(const char*) = 0;
  virtual void loop() = 0;
  virtual void setCallback(
    void (*)(const char*, const uint8_t*, unsigned int)) = 0;
};

/* =====================================================
   WIFI ADAPTER
   ===================================================== */
#ifdef CLOUDLYNK_WIFI_BOARD
class WiFiAdapter : public NetworkAdapter {
public:
  WiFiAdapter();

  bool connect(const char*, const char*, const char*, uint16_t) override;
  bool publish(const char*, const char*) override;
  bool subscribe(const char*) override;
  void loop() override;
  void setCallback(
    void (*)(const char*, const uint8_t*, unsigned int)) override;

private:
  WiFiClient wifiClient;
  PubSubClient mqttClient;
};
#endif

/* =====================================================
   IoT CORE (GENERIC – USED BY ALL PROJECTS)
   ===================================================== */
class IoTCore {
public:
  void begin(NetworkAdapter*);
  bool connect(const char*, const char*, const char*, uint16_t);
  bool publish(const char*, const char*);
  bool subscribe(const char*);
  void run();
  void onMessage(
    void (*)(const char*, const uint8_t*, unsigned int));

#ifdef CLOUDLYNK_ENABLE_CAR
  /* ------------------ 🚗 CAR FEATURE (OPTIONAL) ------------------ */
  void attachCarPins(uint8_t, uint8_t, uint8_t, uint8_t);
  void carForward();
  void carBackward();
  void carLeft();
  void carRight();
  void carStop();
#endif

private:
  NetworkAdapter* adapter = nullptr;
};

/* =====================================================
   GLOBAL INSTANCE (DECLARATION ONLY)
   ===================================================== */
extern IoTCore IoT;

#endif
