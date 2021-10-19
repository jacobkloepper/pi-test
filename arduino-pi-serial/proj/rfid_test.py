#!/usr/bin/env python3
import serial
import csv
from hexutil import *

if __name__ == "__main__":
    ser = serial.Serial("/dev/ttyACM0", 115200, timeout=0.2)
    ser.flush()

    while True:
        valid = False # default: invalid key

        while True:
            if ser.in_waiting > 0:
                line = ser.readline().rstrip().decode('utf-8')
                uid = line # TODO: when reader fw is edited to provide zone code, must change (eg line[:-4])
                break;

        with open('data/users.csv') as f:
            reader = csv.reader(f)
            for row in reader:
                if row[0] == uid:
                    print(f"USER: {row[1]} {row[2]}")
                    valid = True
                    break

        if (not valid):
            print(f"UNKNOWN USER: 0x{hexuid(uid)}")
