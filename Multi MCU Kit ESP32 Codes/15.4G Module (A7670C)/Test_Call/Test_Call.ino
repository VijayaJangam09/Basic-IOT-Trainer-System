#include <HardwareSerial.h>

// Define the hardware serial port
HardwareSerial mySerial(1);

// Define the phone number to call
const char* phoneNumber = "+919036500765"; // Replace with the number you want to call

void setup() {
  // Start the serial communication for debugging
  Serial.begin(115200);

  // Start the hardware serial for the A7670C module
  mySerial.begin(115200, SERIAL_8N1, 16, 17); // RX, TX pins

  // Initialize the A7670C module
  sendATCommand("AT");
  delay(1000);
  sendATCommand("AT+CSCS=\"GSM\""); // Set character set to GSM
  delay(1000);

  // Make the call
  makeCall(phoneNumber);
}

void loop() {
  // Optionally, you can check for call status or hang up after some time
  delay(10000); // Keep the call for 10 seconds (optional)
  hangUp(); // Hang up the call
}

// Function to make a call
void makeCall(const char* number) {
  String command = "ATD";
  command += number;
  command += ";"; // Semicolon indicates to dial the number
  sendATCommand(command.c_str());
}

// Function to hang up the call
void hangUp() {
  sendATCommand("ATH"); // Hang up command
}

// Function to send AT commands and print the response
void sendATCommand(const char* cmd) {
  mySerial.println(cmd);
  delay(1000);

  // Check for a response
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
