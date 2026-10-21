#include <HardwareSerial.h>

// Define the hardware serial port
HardwareSerial mySerial(1);

// Define the phone number and message
const char* phoneNumber = "+919448210594"; // Replace with the recipient's phone number
const char* message = "Hi this is 4g module";

void setup() {
  // Start the serial communication for debugging
  Serial.begin(115200);

  // Start the hardware serial for the A7670C module
  mySerial.begin(115200, SERIAL_8N1, 16, 17); // RX, TX pins

  // Initialize the A7670C module
  sendATCommand("AT");
    sendSMS(phoneNumber, message);
  delay(1000);
}

void loop() {
  // Send the SMS

  delay(10000); // Wait before sending the next message
}

void sendSMS(const char* number, const char* text) {
  sendATCommand("AT+CMGF=1"); // Set SMS to text mode
  delay(1000);
  
  String command = "AT+CMGS=\"";
  command += number;
  command += "\"";
  
  sendATCommand(command.c_str());
  delay(1000);
  
  mySerial.print(text); // Send the SMS text
  delay(100);
  
  mySerial.write(26); // Send CTRL+Z to indicate the end of the message
  delay(1000);

  // Check for a response
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}

void sendATCommand(const char* cmd) {
  mySerial.println(cmd);
  delay(1000);
  
  // Check for a response
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
