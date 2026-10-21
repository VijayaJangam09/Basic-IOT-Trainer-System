from machine import Pin

# Define LED and Button pins
led = Pin(0, Pin.OUT)  # LED connected to GPIO 2
button = Pin(15, Pin.IN, Pin.PULL_UP)  # Button connected to GPIO 15 with pull-up resistor

while True:
    if not button.value():  # Button pressed (value is LOW)
        led.on()  # Turn LED on
    else:
        led.off()  # Turn LED off
