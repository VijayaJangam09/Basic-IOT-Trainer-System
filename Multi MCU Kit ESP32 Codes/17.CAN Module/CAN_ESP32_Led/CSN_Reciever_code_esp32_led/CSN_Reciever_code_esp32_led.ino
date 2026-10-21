#include <SPI.h>
#include <mcp_can.h>

#define CS_PIN 5   // Chip Select pin for MCP2515
#define INT_PIN 4  // Interrupt pin for MCP2515
#define LED_PIN 2  // LED to control via CAN message

MCP_CAN CAN0(CS_PIN);  // Create CAN instance

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
  
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
    if (!digitalRead(INT_PIN)) {  // Check if data is available
        unsigned long id;
        unsigned char len;
        unsigned char buf[8];

        CAN0.readMsgBuf(&id, &len, buf);  // Read message
        Serial.print("Received: ID=0x");
        Serial.print(id, HEX);
        Serial.print(" Data=");

        for (int i = 0; i < len; i++) {
            Serial.print(buf[i], HEX);
            Serial.print(" ");
        }
        Serial.println();

        // **Control LED based on received message**
        if (buf[0] == 0x54 && buf[1] == 0x17) {  // If data is 0x5417, toggle LED
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
            delay(2000);
            Serial.println("LED TOGGLED");
        }
    }
}
