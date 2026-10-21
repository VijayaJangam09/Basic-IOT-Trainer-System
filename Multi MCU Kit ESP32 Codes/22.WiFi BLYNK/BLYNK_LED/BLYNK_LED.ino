#define BLYNK_TEMPLATE_ID "TMPL3aQHpfmaD"
#define BLYNK_TEMPLATE_NAME "led"
#define BLYNK_AUTH_TOKEN "F_FEKTjhs1CYfQ2q2Z1D4uQ0AkYYuByW"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;  // Use the authentication token from your Blynk project
char ssid[] = "E";
char pass[] = "12345678";

#define RELAY_PIN 2  // Digital pin connected to the relay control

void setup() {
  Blynk.begin(auth, ssid, pass);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(2) {
  int relayState = param.asInt();
  digitalWrite(RELAY_PIN, relayState);
}
