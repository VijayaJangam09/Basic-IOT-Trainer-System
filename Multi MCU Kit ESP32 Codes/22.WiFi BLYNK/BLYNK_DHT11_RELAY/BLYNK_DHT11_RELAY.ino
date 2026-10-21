#define BLYNK_TEMPLATE_ID "TMPL3nzIz1zMf"
#define BLYNK_TEMPLATE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "BTqx1GfswYDP2XReD04FMii05N6_RpCc"
#include <SPI.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#define DHTPIN 4  // What digital pin we're connected to
#define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT22   // DHT 22
#define RELAY_PIN 2  // Digital pin connected to the relay control

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
char auth[] = BLYNK_AUTH_TOKEN;  // Use the authentication token from your Blynk project
char ssid[] = "Raj"; //enter the SSID(Wi-Fi Name)
char pass[] = "12345678";  // enter the password

// This function sends Arduino's up time every second to Virtual Pin (5)
void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V0, t);
}

void setup() {
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
