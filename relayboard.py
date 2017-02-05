import Adafruit_BBIO.GPIO as gpio
import time

pins = ["P8_8", "P8_10", "P8_12"]

for pin in pins:
    gpio.setup(pin, gpio.OUT)
    gpio.output(pin, gpio.LOW)


def control(r1, r2, r3):
    gpio.output(pins[0], r1)
    gpio.output(pins[1], r2)
    gpio.output(pins[2], r3)


def pattern1(d):
    control(1,0,0)
    time.sleep(d)
    control(0,1,0)
    time.sleep(d)
    control(0,0,1)
    time.sleep(d)
    control(0,0,0)
    time.sleep(d)

