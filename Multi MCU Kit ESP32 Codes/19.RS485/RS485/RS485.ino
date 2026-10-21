  #include <HardwareSerial.h>

// Define the serial port and the control pin for RS485
HardwareSerial RS485Serial(3);
// RS485 Pin Configuration while DE/RE as default pins
// #define RS485_DE 22   // Driver Enable pin
// #define RS485_RE 23   // Receiver Enable pin  
// RS485 Pin Configuration while DE/RE as single pin
#define RS485ControlPin 4//  DE/RE to GPIO 4 , DI to GPIO 17 , RO to GPIO 16
#define LEDPin  15
/*
* ---------------------    
 * | RS485   | Connecter|    
 * ---------------------    
 * |   Vcc   |   5V     |    
 * |   A     |   A      |  
 * |   B     |   B      |    
 * |   Gnd   |   GND    |    
 * ---------------------
 */
// Function to control the RS485 DE/RE pins
void RS485Transmit() {
  digitalWrite(RS485ControlPin, HIGH);
}

void RS485Receive() {
  digitalWrite(RS485ControlPin, LOW);
}

void setup() {
  Serial.begin(9600);
  // Initialize the RS485 control pin
  pinMode(RS485ControlPin, OUTPUT);
  RS485Receive();

  // Initialize LED pin
  pinMode(LEDPin, OUTPUT);

  // Begin serial communication at a baud rate of 9600
  RS485Serial.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  // Example code to send data
  RS485Transmit();
  delay(100); // Short delay
  RS485Receive();
  String message = "";
  
  // Example code to receive data
  if(RS485Serial.available()){
    while(RS485Serial.available()>0) {
      char receivedData = RS485Serial.read();
      if (receivedData != '\n'){
        message += String(receivedData);
      }
    }
    
    // Trim the message to remove any extra spaces or newline characters
    message.trim();
    
    // Debug print to see the exact message received
    Serial.println("Message received: '" + message + "'");
    
    // Processing the received message
    if (message == "1") {
      digitalWrite(LEDPin, HIGH); // Turn on LED
      Serial.println("LED Turned on");
    } else if (message == "0") {
      digitalWrite(LEDPin, LOW); // Turn off LED
      Serial.println("LED Turned off");
    }
  }
  
  delay(1000); // Adjust the delay as needed
}
