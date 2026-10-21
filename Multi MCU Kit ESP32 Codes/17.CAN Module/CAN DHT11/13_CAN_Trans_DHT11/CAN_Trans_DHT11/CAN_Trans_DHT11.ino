#include <SPI.h>          // Library for using SPI Communication
#include <mcp2515.h>      // Library for using CAN Communication
#include "DHT.h"

#define DHT11PIN 4
DHT dht(DHT11PIN, DHT11);

struct can_frame canMsg;
MCP2515 mcp2515(2); // chip select CS pin 10

void setup() {
  Serial.begin(115200);
  SPI.begin();    // Begins SPI communication
  dht.begin();

  Serial.println("Initializing MCP2515...");
  if (mcp2515.reset() != MCP2515::ERROR_OK) {
    Serial.println("Error resetting MCP2515");
    while (1);
  }
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); // Sets CAN at speed 500KBPS and Clock
  mcp2515.setNormalMode();
  Serial.println("MCP2515 Initialized.");
  delay(2000);
  canMsg.can_id = 0x036; // CAN id 0x036
  canMsg.can_dlc = 2;    // Data length code is 2 bytes
}

void loop() {
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humi) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.println("\nCAN Transmitter.........\n");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("C ");
  Serial.print("Humidity: ");
  Serial.println(humi);

  canMsg.data[0] = temp;
  canMsg.data[1] = humi;

  if (mcp2515.sendMessage(&canMsg) != MCP2515::ERROR_OK) {
    Serial.println("Error Sending Message...");
  }
  else {
    Serial.println("Message Sent Successfully");
  }
  delay(1000);
}
