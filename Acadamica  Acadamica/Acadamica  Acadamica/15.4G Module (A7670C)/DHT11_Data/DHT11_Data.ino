#include <HardwareSerial.h>
#include <DHT.h>

// DHT11 Sensor settings
#define DHTPIN 4           // Pin where the DHT11 is connected
#define DHTTYPE DHT11      // DHT 11 sensor type
DHT dht(DHTPIN, DHTTYPE);

// Define the hardware serial port for A7670C
HardwareSerial mySerial(1);

// Define the phone number to send the message to
const char* phoneNumber = "+918073978976"; // Replace with the recipient's phone number

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);

  // Start hardware serial for the A7670C module
  mySerial.begin(115200, SERIAL_8N1, 16, 17); // RX, TX pins

  // Initialize the DHT11 sensor
  dht.begin();

  // Check if the module is responding
  sendATCommand("AT", 1000); // Send AT to check communication

  // Check if the module is registered on the network
  sendATCommand("AT+CREG?", 2000); // Check network registration
  
  // Check signal strength
  sendATCommand("AT+CSQ", 2000); // Check signal quality

  // Set SMS mode
  sendATCommand("AT+CMGF=1", 1000); // Set SMS to text mode
}

void loop() {
  // Read humidity and temperature from the DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if the readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Create the message with the sensor data
  String message = "DHT11 Sensor Data:\n";
  message += "Temperature: " + String(temperature) + " C\n";
  message += "Humidity: " + String(humidity) + " %";

  // Send the SMS with DHT11 data
  sendSMS(phoneNumber, message.c_str());

  // Wait for 10 minutes before sending the next SMS
  delay(10000); // 600000 ms = 10 minutes
}

void sendSMS(const char* number, const char* text) {
  // Construct the AT command to send SMS
  String command = "AT+CMGS=\"";
  command += number;
  command += "\"";
  
  // Send the command to the module
  sendATCommand(command.c_str(), 1000);
  
  // Send the actual message text
  mySerial.print(text);
  delay(100);
  
  // Send Ctrl+Z (ASCII 26) to indicate the end of the message
  mySerial.write(26); // Ctrl+Z
  delay(3000); // Wait for the message to send

  // Read and print the response from the module
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}

void sendATCommand(const char* cmd, unsigned long waitTime) {
  // Send the AT command to the module
  mySerial.println(cmd);
  delay(waitTime);

  // Read and print the response for debugging
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
