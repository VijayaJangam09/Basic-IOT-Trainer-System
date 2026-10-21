#include <SPI.h>
#include <mcp2515.h>

MCP2515 mcp2515(5);
struct can_frame canMsg;

const int ledPin = 2; // GPIO 2

void setup() {
  SPI.begin();
  pinMode(ledPin, OUTPUT);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x100 && canMsg.data[0] == 1) {
      digitalWrite(ledPin, HIGH); // LED blink
      delay(100);
      digitalWrite(ledPin, LOW);
    }
  }
  delay(10);
}
