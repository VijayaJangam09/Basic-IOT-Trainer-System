#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;

MCP2515 mcp2515(10);
#define TFT_CS     4
#define TFT_RST    3 
#define TFT_DC     2  //A0
#define TFT_SCLK   SCL   //SCK
#define TFT_MOSI   SDA   //SDA
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

void setup() {
  Serial.begin(9600);
  SPI.begin();

  // Initialize the TFT display
  tft.initR(INITR_BLACKTAB);                  /* initialize a ST7735S chip, black tab */
  tft.setTextWrap(false);                     /* Allow text to run off right edge */
  tft.fillScreen(ST7735_BLACK);

  mcp2515.reset();
  mcp2515.setBitrate (CAN_500KBPS,MCP_8MHZ); //Sets CAll at speed 500KBPS and Clock
  mcp2515.setNormalMode(); //Sets Call at normal mode

}

void loop() {
  
  if (mcp2515.readMessage(&canMsg) == MCP2515:: ERROR_OK) // To receive data (Poll Read)
  {
    if (canMsg.can_id==0x036)
    {
      int t=canMsg.data[0];
      int p=canMsg.data[1];
      tft.fillScreen(ST7735_BLACK);  /* BLACK -- Background */ 
      
      tft.setRotation(1);
      
      tft.setCursor(0, 30);
      tft.setTextColor(ST7735_YELLOW);
      tft.setTextSize(1.5);
      tft.print("Temperature ==> ");
      tft.println(t);
      tft.print("Pressure ==> ");
      tft.println(p);
      Serial.println("\nCAN Receiver.........\n");
      Serial.print("Temperature ==> ");
      Serial.println(t);
      Serial.print("Pressure ==> ");
      Serial.println(p);
      delay(1000);
    }
  }
  
}
