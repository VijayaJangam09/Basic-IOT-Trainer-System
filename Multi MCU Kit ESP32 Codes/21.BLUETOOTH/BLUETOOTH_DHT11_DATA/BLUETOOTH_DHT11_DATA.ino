#include <BluetoothSerial.h>
#include <DHT.h>
#define dhtPin 2
#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);
BluetoothSerial SerialBT; 
void setup() {
  Serial.begin(115200);  dht.begin();
  SerialBT.begin("ESP32test"); // Set a name for Bluetooth server
}
void loop() {
  float temperature = dht.readTemperature(); // Read temperature value in 
  float humidity = dht.readHumidity(); // Read humidity value
  if (isnan(temperature) || isnan(humidity)) {
     Serial.println("Failed to read from DHT sensor!");
     SerialBT.println("Failed to read from DHT sensor!");
    return;
  } 
    SerialBT.print("Temperature: ");SerialBT.print(temperature);
    SerialBT.println(" °C");
    SerialBT.print("Humidity: ");    SerialBT.print(humidity);
    SerialBT.println(" %");
    SerialBT.println("");
     delay(2000);
}
