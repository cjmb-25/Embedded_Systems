import serial
import time

try:
    arduino = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    time.sleep(2)  # Wait for Arduino to reset

    while True:
        line = arduino.readline().decode().strip()
        if line:
            print("Received:", line)

            if line.startswith("[DISTANCE]"):
                distance = line.split("]")[1].strip()
                print("Distance:", distance)

            elif line.startswith("[UID]"):
                uid = line.split("]")[1].strip()
                print("Card UID:", uid)

            elif line.startswith("[ACCESS]"):
                status = line.split("]")[1].strip()
                print("Access Status:", status)

except Exception as e:
    print("Error:", e)

