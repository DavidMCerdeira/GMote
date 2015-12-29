import serial as ps
import sys

class Aquisition():
    def __init__(self):
        self.ser = ps.Serial()
        self.Aqs = {}
        self.fileTest = open(".\\Text.csv", 'r')

    def serialPortInit(self, i_baudrate = 2000000, i_port = 2, i_datasize = 8, i_stopbits = 1, i_parity = 'N'):
        #self.ser.baudrate = i_baudrate
        #self.ser.port = i_port
        #self.ser.bytesize = i_datasize
        #self.ser.parity = i_parity
        #self.ser.open()

        self.fileTest.open(".\\Text.csv", 'r')
		#self.ser.write("ati")
		#self.ser.close()

    def make_an_aquisition(self, number_of_lines = 1):
        aqDataInt = []
        aqDataChars = []
        aqDataChars = self.fileTest.readline().split(" ")
        for val in aqDataChars:
            aqDataInt.append(int(val))
        return aqDataInt

#a = Aquisition()
#a.serialPortInit()
#a.make_an_aquisition()
