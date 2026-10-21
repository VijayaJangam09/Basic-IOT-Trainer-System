from machine import I2C, Pin

# Initialize I2C
i2c = I2C(0, scl=Pin(9), sda=Pin(8), freq=100000)

# Scan for devices
devices = i2c.scan()

if devices:
    print("I2C devices found:", devices)
else:
    print("No I2C devices found. Check connections.")
