import BlynkLib
import RPi.GPIO as GPIO
import time

BLYNK_AUTH_TOKEN = 'niI1WlHFgJ8kaUNPHnN5uS5xyCi8PdiE'  # Replace with your actual Blynk Auth Token

# LED Pin Setup
LED_PIN = 27  # GPIO pin for the LED

# Initialize GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, GPIO.LOW)

# Initialize Blynk
blynk = BlynkLib.Blynk(BLYNK_AUTH_TOKEN)

# Function to control LED state via Virtual Pin V2
@blynk.on("V5")
def control_led(value):
    if int(value[0]) == 1:
        GPIO.output(LED_PIN, GPIO.HIGH)
    else:
        GPIO.output(LED_PIN, GPIO.LOW)

@blynk.on("connected")
def blynk_connected():
    print("Raspberry Pi Connected to Blynk")

# Run the Blynk loop
while True:
    blynk.run()
    time.sleep(0.1)

