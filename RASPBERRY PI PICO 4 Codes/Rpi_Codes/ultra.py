import RPi.GPIO as GPIO
import time

# Define GPIO pins
TRIG = 23
ECHO = 24

# GPIO setup
GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

def get_distance():
    # Ensure TRIG is low
    GPIO.output(TRIG, False)
    time.sleep(0.1)  # Small delay to settle the sensor

    # Send 10us pulse to TRIG
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    # Wait for echo response
    while GPIO.input(ECHO) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO) == 1:
        pulse_end = time.time()

    # Calculate time difference
    pulse_duration = pulse_end - pulse_start

    # Calculate distance in cm (speed of sound = 34300 cm/s)
    distance = (pulse_duration * 34300) / 2

    return round(distance, 2)

while True:
        dist = get_distance()
        print(f"Distance: {dist} cm")
        time.sleep(1)

