import RPi.GPIO as GPIO
import time

# Pin configuration
LED_PIN = 18  # GPIO pin for LED
IR_PIN = 17  # GPIO pin for switch

# GPIO setup
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.setup(IR_PIN, GPIO.IN)  # Enable pull-up resistor

while True:
        IR_state = GPIO.input(IR_PIN)  # Read switch state
        if IR_state == GPIO.LOW:  # If switch is pressed
            GPIO.output(LED_PIN, GPIO.HIGH)  # Turn on LED
        else:
            GPIO.output(LED_PIN, GPIO.LOW)  # Turn off LED
        time.sleep(0.1)  # Small delay to avoid bouncing issues


