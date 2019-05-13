#! /usr/bin/python3
import serial
import io
import threading
import time

with serial.serial_for_url('/dev/ttyACM0', timeout=1) as ser:

    sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

    def readLoop():

        while True:

            if ser.in_waiting:

                print(ser.readline().decode("utf-8").replace("\n",""))

            time.sleep(0.1)

    threading.Thread(target=readLoop).start()
    while True:


        userInput = input("")
        sio.write(str(userInput + "\n"))
        sio.flush() 
