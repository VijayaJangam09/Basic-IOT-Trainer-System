import Adafruit_DHT
import time

# Define sensor type and GPIO pin
SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 4  # Change this if using another GPIO pin

while True:
    humidity, temperature = Adafruit_DHT.read_retry(SENSOR, DHT_PIN)

    if humidity is not None and temperature is not None:
        print(f"Temperature: {temperature:.1f}°C  Humidity: {humidity:.1f}%")
    else:
        print("Failed to retrieve data from the sensor")

    time.sleep(2)  # Wait for 2 seconds before the next reading

