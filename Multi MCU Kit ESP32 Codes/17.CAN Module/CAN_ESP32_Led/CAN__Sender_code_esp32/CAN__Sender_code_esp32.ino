#include <SPI.h>
#include <mcp_can.h>

#define CS_PIN 5  // Chip Select pin for MCP2515

MCP_CAN CAN0(CS_PIN);  // Create CAN instance

void setup() {
    Serial.begin(115200);
    delay(1000);

    if (CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) {
        Serial.println("CAN BUS Init OK!");
    } else {
        Serial.println("CAN BUS Init Failed!");
        while (1);
    }

    CAN0.setMode(MCP_NORMAL);
}

void loop() {
    unsigned char msg[2] = {0x54, 0x17};  // Data to send
    if (CAN0.sendMsgBuf(0x100, 0, 2, msg) == CAN_OK) {
        Serial.println("Sent: 0x5417");
    } else {
        Serial.println("Message Sending Failed!");
    }
  
    delay(5000);  // Wait 5 seconds
}
