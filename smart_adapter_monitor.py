import Adafruit_BBIO.UART as UART
import serial
import time

UART.setup("UART1")

ser = serial.Serial(port = "/dev/ttyO1", baudrate=9600)
ser.close()
ser.open()

while True:
    if ser.isOpen():
     ser.write('c')
     response = ser.readline().strip()
     print("Current: {}".format(response))
     time.sleep(0.5)



