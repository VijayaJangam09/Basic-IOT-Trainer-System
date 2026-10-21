import network
import urequests
import random
import dht
from machine import Pin
from time import sleep

#Network Initialization
ssid = "IobiT Solutions"
password = "IobiT@2023"

sensor = dht.DHT11(Pin(15))
def ConnectWiFi():
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)
    while wlan.isconnected() == False:
        print('Waiting for connection...')
        sleep(1)
    ip = wlan.ifconfig()[0]
    print(f'Connected on {ip}')
    return ip

#Connect to Network
ip = ConnectWiFi()

#ThingSpeak Initialization
server = "http://api.thingspeak.com/"
apikey = "18GXM50CZ7DZV3SW"
field = 1

#Main Program
while True:
    sensor.measure()
    temp = sensor.temperature()
    hum = sensor.humidity()
    
    print('Temperature: %3.1f C' %temp)
    print('Humidity: %3.1f %%' %hum)
    print("")
    
    url = f"{server}/update?api_key={apikey}&field{field}={temp}"
    request = urequests.post(url)
    request.close()
    
    sleep(20)