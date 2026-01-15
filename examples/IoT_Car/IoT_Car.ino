#include <Cloudeck.h>

/*
  IoT Car Example using Cloudeck
  -----------------------------
  - MQTT controlled car
  - L298N motor driver
  - Commands via MQTT:
    F, B, L, R, S
*/

WiFiAdapter wifi;

/* WiFi & MQTT */
const char* WIFI_SSID   = "YOUR_WIFI_NAME";
const char* WIFI_PASS   = "YOUR_WIFI_PASSWORD";
const char* MQTT_BROKER = "BROKER_IP";   // EC2 / EMQX IP
const uint16_t MQTT_PORT = 1883;
const char* CONTROL_TOPIC = "cloudlynk/car/control";

/* Motor pins (L298N) */
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4

/* MQTT message handler */
void onMessage(const char* topic,
               const uint8_t* payload,
               unsigned int length) {

  if (length == 0) return;

  char cmd = (char)payload[0];
  Serial.print("📩 CMD: ");
  Serial.println(cmd);

  switch (cmd) {
    case 'F': IoT.carForward();  break;
    case 'B': IoT.carBackward(); break;
    case 'L': IoT.carLeft();     break;
    case 'R': IoT.carRight();    break;
    case 'S': IoT.carStop();     break;
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println("🚗 Cloudeck IoT Car Starting");

  IoT.begin(&wifi);

  /* Attach motor pins */
  IoT.attachCarPins(IN1, IN2, IN3, IN4);

  /* MQTT callback */
  IoT.onMessage(onMessage);

  /* Connect */
  IoT.connect(WIFI_SSID, WIFI_PASS, MQTT_BROKER, MQTT_PORT);
  IoT.subscribe(CONTROL_TOPIC);

  Serial.println("✅ IoT Car ready");
}

void loop() {
  IoT.run();   // REQUIRED
}
