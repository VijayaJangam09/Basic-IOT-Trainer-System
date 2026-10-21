import adxl345
import time

while True:
    x, y, z = adxl345.read_ADXL345()
    print(f"X: {x} m/s², Y: {y} m/s², Z: {z} m/s²")
    time.sleep(1)

