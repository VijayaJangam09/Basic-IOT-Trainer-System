import RPi.GPIO as GPIO
import time

# Set GPIO mode to BCM
GPIO.setmode(GPIO.BCM)

# Define LED pin
LED_PIN = 18

# Set LED pin as output
GPIO.setup(LED_PIN, GPIO.OUT)

while True:
        GPIO.output(LED_PIN, GPIO.HIGH)  # LED ON
        time.sleep(1)  # 1-second delay
        GPIO.output(LED_PIN, GPIO.LOW)   # LED OFF
        time.sleep(1)  # 1-second delay

