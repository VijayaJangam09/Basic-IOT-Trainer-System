#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(2);

#define TFT_CS     14
#define TFT_RST    12
#define TFT_DC     13  // A0
#define TFT_SCLK   SCL // SCK
#define TFT_MOSI   SDA // SDA

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(115200);
  SPI.begin();

  // Initialize the TFT display
  Serial.println("Initializing TFT...");
  tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab
  tft.setTextWrap(false);     // Allow text to run off right edge
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);         // Set display rotation
  Serial.println("TFT Initialized.");

  // Initialize MCP2515
  Serial.println("Initializing MCP2515...");
  if (mcp2515.reset() != MCP2515::ERROR_OK) {
    Serial.println("Error resetting MCP2515");
    while (1);
  }
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  Serial.println("MCP2515 Initialized.");
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    if (canMsg.can_id == 0x036) {
      int t = canMsg.data[0];
      int h = canMsg.data[1];
      Serial.println("\nCAN Receiver.........\n");
      Serial.print("Temperature ==> ");
      Serial.println(t);
      Serial.print("Humidity ==> ");
      Serial.println(h);
      Serial.println("Reading CAN message Successful");
      tft.fillScreen(ST7735_BLACK); // BLACK -- Background

      tft.setCursor(0, 30);
      tft.println("\nCAN Receiver.........\n");
      tft.setTextColor(ST7735_YELLOW);
      tft.setTextSize(1.3); // Set text size
      tft.print("Temperature ==> ");
      tft.println(t);
      tft.print("Humidity ==> ");
      tft.println(h);
      tft.println("Reading CAN message Successful");
      delay(1000);
    }
  }
}
