from machine import I2C, Pin
from bmp180 import BMP180
import time

# Initialize I2C
i2c = I2C(0, scl=Pin(9), sda=Pin(8), freq=100000)  # I2C0 with SCL on GPIO 9 and SDA on GPIO 8

# Initialize BMP180
bmp = BMP180(i2c)
bmp.oversample_sett = 2  # Set oversampling for better accuracy
bmp.sealevel = 1013.25  # Set sea-level pressure in hPa (standard value)

while True:
    temp = bmp.temperature  # Get temperature in Celsius
    pressure = bmp.pressure  # Get pressure in hPa
    altitude = bmp.altitude  # Calculate altitude based on pressure

    print(f"Temperature: {temp:.2f} °C")
    print(f"Pressure: {pressure:.2f} hPa")
    print(f"Altitude: {altitude:.2f} m")
    print("-" * 30)

    time.sleep(2)  # Wait for 2 seconds before the next reading
