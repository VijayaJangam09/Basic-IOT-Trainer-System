import smbus
import time

DEVICE = 0x53  # ADXL345 I2C address
bus = smbus.SMBus(1)

def init_ADXL345():
    bus.write_byte_data(DEVICE, 0x2D, 0x08)  # Enable measurement mode
    bus.write_byte_data(DEVICE, 0x31, 0x08)  # Set range to ±2g

def read_raw_data(reg):
    data0 = bus.read_byte_data(DEVICE, reg)
    data1 = bus.read_byte_data(DEVICE, reg + 1)
    value = (data1 << 8) | data0
    if value > 32767:
        value -= 65536  # Convert to signed value
    return value

def read_ADXL345():
    x = read_raw_data(0x32) * 0.004 * 9.81  # Convert to m/s²
    y = read_raw_data(0x34) * 0.004 * 9.81
    z = read_raw_data(0x36) * 0.004 * 9.81
    return round(x, 2), round(y, 2), round(z, 2)

init_ADXL345()

