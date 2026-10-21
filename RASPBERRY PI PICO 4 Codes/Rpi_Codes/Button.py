import RPi.GPIO as GPIO
import time

# Pin configuration
LED_PIN = 18  # GPIO pin for LED
SWITCH_PIN = 17  # GPIO pin for switch

# GPIO setup
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.setup(SWITCH_PIN, GPIO.IN)  # Enable pull-up resistor

while True:
        switch_state = GPIO.input(SWITCH_PIN)  # Read switch state
        if switch_state == GPIO.LOW:  # If switch is pressed
            GPIO.output(LED_PIN, GPIO.HIGH)  # Turn on LED
        else:
            GPIO.output(LED_PIN, GPIO.LOW)  # Turn off LED
        time.sleep(0.1)  # Small delay to avoid bouncing issues

