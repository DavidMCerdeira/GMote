import serial as ps
import sys

class Aquisition():
    def __init__(self):
        self.ser = ps.Serial()
        self.Aqs = {}

    def serialPortInit(self, i_baudrate = 2000000, i_port = "COM3", i_datasize = 8, i_stopbits = 1, i_parity = 'N'):
        self.ser.baudrate = i_baudrate
        self.ser.port = i_port
        self.ser.bytesize = i_datasize
        self.ser.parity = i_parity
        self.ser.open()
		#self.ser.close()

    def make_an_aquisition(self, number_of_lines = 1):
        self.serialPortInit()
        aqDataInt = []
        aqDataChars = []
        aqDataChars = self.ser.readline().decode("utf-8").rsplit(" ")
        #print(aqDataChars)
        for val in aqDataChars:
            if val.isdigit():
                aqDataInt.append(int(val))
        self.ser.close()
        return aqDataInt

#a = Aquisition()
#a.make_an_aquisition()
