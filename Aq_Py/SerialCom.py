import serial as ps
import sys

class Aquisition():
    def __init__(self):
        self.ser = ps.Serial()
        self.Aqs = {}
        #self.testFile = open('Text.csv', 'r')


    def serialPortInit(self, i_baudrate = 2000000, i_port = "COM4", i_datasize = 8, i_stopbits = 1, i_parity = 'N'):
        self.ser.baudrate = i_baudrate
        self.ser.port = i_port
        self.ser.bytesize = i_datasize
        self.ser.parity = i_parity
        self.ser.open()

    def make_an_aquisition(self, number_of_lines = 1):
        self.serialPortInit()
        aqDataChars = []
        aqDataChars = self.ser.readline().decode("utf-8").rsplit(" ")
        #aqDataChars = self.testFile.readline().rsplit(" ") # Testando com ficheiros
        #self.ser.close()
        dataLen = len(aqDataChars)
        rest = (dataLen - 1) % number_of_lines
        #~3print(rest)
        #if not (rest):
        aqDataInt = [[0 for x in range(int(dataLen/number_of_lines))] for x in range(number_of_lines)]
        #print(aqDataInt[len(aqDataInt)-1])
        for i in range(0, dataLen-1):
            if aqDataChars[i].isdigit():
                sample_nr = int(i / number_of_lines)
                axe = i % number_of_lines
                aqDataInt[axe][sample_nr] = int(aqDataChars[i])
                if (aqDataInt[axe][sample_nr] > 32):
                    return None
        self.ser.close()
        return aqDataInt



#a = Aquisition()
#ret = a.make_an_aquisition(6)
#print(ret)
