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
  digitalWrite(ledPin, HIGH); // LED on
  delay(100);
  digitalWrite(ledPin, LOW);  // LED off

  canMsg.can_id  = 0x100;
  canMsg.can_dlc = 1;
  canMsg.data[0] = 1; // Send 1 to blink

  mcp2515.sendMessage(&canMsg);
  delay(900); // repeat every second
}

