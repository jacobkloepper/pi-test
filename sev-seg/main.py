#!/usr/bin/python3.7
import RPi.GPIO as GPIO
import time
from lut import *

def turn_off_GPIOs(channels):
    for i in range(len(channels)):
        GPIO.output(channels[i], GPIO.LOW)

def turn_on_GPIOs(channels):
    for i in range(len(channels)):
        GPIO.output(channels[i], GPIO.HIGH)

if __name__ == "__main__":
    # setup
    GPIO.setmode(GPIO.BCM)
    channels = [5,6,17,22,23,24,25,27]

    for chan in channels:
        GPIO.setup(chan, GPIO.OUT)

    # accept input, print on 7seg
    inp = input()
    while(inp != "-1"):
        turn_off_GPIOs(channels)

        try:
            input_channels = sevseg[inp]
        except:
            input_channels = sevseg["?"] 

        turn_on_GPIOs(input_channels)
        inp = input()

    print("Exiting normally")
    turn_off_GPIOs(channels)
    GPIO.cleanup()
