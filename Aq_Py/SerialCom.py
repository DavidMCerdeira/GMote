import serial as ps
import sys

class Aquisition():
    def __init__(self):
        self.ser = ps.Serial()
        self.Aqs = {}

    def serialPortInit(self, i_baudrate = 2000000, i_port = 2, i_datasize = 8, i_stopbits = 1, i_parity = 'N'):
        self.ser.baudrate = i_baudrate
        self.ser.port = i_port
        self.ser.bytesize = i_datasize
        self.ser.parity = i_parity
        self.ser.open()
		#self.ser.write("ati")
		#self.ser.close()

    def make_an_aquisition(self, number_of_lines = 1):
        aqDataInt = []
        aqDataStr = ""

        for i in range(0, number_of_lines): #prepares de aqDataInt for the number of axes that we want
            aqDataInt.append([])

        received = ' '
        while received is not '\r':
            received = self.ser.read()
            aqDataStr += received[]

        print(aqDataStr)

a = Aquisition()
a.serialPortInit()
a.make_an_aquisition()
