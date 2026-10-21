#define BLYNK_TEMPLATE_ID "TMPL3R_GK1JYj"
#define BLYNK_TEMPLATE_NAME "DHT"
#define BLYNK_AUTH_TOKEN "x0e3QDXzEl-xuymSmHg3Pr71JcAoj1R8"

#include <SPI.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define BLYNK_PRINT Serial
#define DHTPIN 4  // What digital pin we're connected to
#define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT22   // DHT 22

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
char auth[] = BLYNK_AUTH_TOKEN;  // Use the authentication token from your Blynk project
char ssid[] = "IobiT Solutions"; //enter the SSID(Wi-Fi Name)
char pass[] = "IobiT@2023";  // enter the password

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
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup() {
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
