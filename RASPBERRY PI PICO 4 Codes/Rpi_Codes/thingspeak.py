import Adafruit_DHT
import requests
import time

# ThingSpeak API information
channel_id = '2280722'
api_key = '4LNQSI5IW06BJ0CP'
base_url = f'https://api.thingspeak.com/update?api_key={api_key}'

# DHT sensor settings
sensor_type = Adafruit_DHT.DHT11  # DHT sensor type (DHT11 or DHT22)
pin = 4  # GPIO pin number where the DHT sensor is connected

def read_dht_sensor_data():
    humidity, temperature = Adafruit_DHT.read_retry(sensor_type, pin)
    if humidity is not None and temperature is not None:
        return temperature, humidity
    else:
        return None

def send_to_thingspeak(data):
    if data is not None:
        url = f"{base_url}&field1={data[0]:.2f}&field2={data[1]:.2f}"
        response = requests.post(url)
        if response.status_code == 200:
            print("Data sent to ThingSpeak successfully.")
        else:
            print("Failed to send data to ThingSpeak.")
    else:
        print("Failed to read data from DHT sensor.")


while True:
        sensor_data = read_dht_sensor_data()
        send_to_thingspeak(sensor_data)
        time.sleep(1 * 60)  # Send data every 15 minutes (adjust as needed)


