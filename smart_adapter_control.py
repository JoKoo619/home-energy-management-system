import Adafruit_BBIO.UART as UART
import serial

UART.setup("UART1")
ser = serial.Serial(port = "/dev/ttyO1", baudrate=9600)
ser.close()
ser.open()
if ser.isOpen():
    ser.write('r')

ser.close()
