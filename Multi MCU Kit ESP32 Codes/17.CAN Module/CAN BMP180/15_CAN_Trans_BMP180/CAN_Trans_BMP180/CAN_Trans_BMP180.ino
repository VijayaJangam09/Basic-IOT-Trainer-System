#include <SPI.h>          //Library for using SPI Communication
#include <mcp2515.h>      //Library for using CAN Communication
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp;  

struct can_frame canMsg;
MCP2515 mcp2515(10); // chip select CS pin 10

void setup()
{
  Serial.begin(9600);
  SPI.begin();    //Begins SPI communication
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and
  mcp2515.setNormalMode();

  canMsg.can_id =0x036;//CAN id 0x036
  //CAll data length as i byte
  canMsg.can_dlc =2;
}

void loop()
{
  float pres = bmp.readPressure();
  float temp = bmp.readTemperature();
  Serial.println("\nCAN Transmitter.........\n");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("C ");
  Serial.print("Pressure: ");
  Serial.println(pres);

  canMsg.data[0] = temp;
  canMsg.data[1] = pres;
  mcp2515.sendMessage(&canMsg);
  delay (1000);
}
