import os
import serial
import sys
import time

# ARDUINO MUST BE RUNNING FIRST

def send_data(animation, size, arduino):
    animation.seek(5)
    sent = 5
    while sent < size:                  # Send bytes as long as there are more to send
        try:                            # Let arduino tell us how many bytes are needed
            available = int.from_bytes(arduino.read(1), 'big')
        except:
            available = 0
            continue
        #print("Available: " + str(available))
        rcv = animation.read(available) # Send the number of bytes the arduino requested
        #print("Sent: " + str(rcv))
        sent += len(rcv)
        if rcv:
            arduino.write(rcv)

def run(filename='out'):
    arduino = serial.Serial('/dev/ttyUSB0', 38400, timeout=0.1)
    animation = open(filename, 'rb')    # Open the animation
    size = os.stat(filename).st_size    # Get how long the animation is
    time.sleep(2)                       # Wait for the arduino to be ready
    arduino.write(bytes('a', 'utf-8'))  # Send a dummy byte
    while arduino.in_waiting < 5:       # Wait for a response
        continue
    data = arduino.read(5)              # Grab response
    if data != b'begin':                # Check for good response
        sys.exit("begin failed to be sent correctly")
    data = animation.read(1)            # Get number of times the animation should run
    repeats = int.from_bytes(data, 'big')
    animation.seek(0)
    while arduino.in_waiting < 1:
        continue
    arduino.read(1)
    data = animation.read(5)
    arduino.write(data)
    if repeats != 0:
        for i in range(repeats):
            send_data(animation, size, arduino)
    else:
        while True:
            send_data(animation, size, arduino)
    animation.close()

if __name__ == "__main__":
    run()
