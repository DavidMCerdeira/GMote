import serial as ps
import sys

class Aquisition():
    def __init__(self):
        self.ser = ps.Serial()
        self.Aqs = {}
        self.testFile = open('Text.csv', 'r')


    def serialPortInit(self, i_baudrate = 2000000, i_port = "COM3", i_datasize = 8, i_stopbits = 1, i_parity = 'N'):
        self.ser.baudrate = i_baudrate
        self.ser.port = i_port
        self.ser.bytesize = i_datasize
        self.ser.parity = i_parity
        self.ser.open()
		#self.ser.close()

    def testInit(self):
        pass

    def make_an_aquisition(self, number_of_lines = 1):
        #self.serialPortInit()
        aqDataChars = []
        #aqDataChars = self.ser.readline().decode("utf-8").rsplit(" ")
        aqDataChars = self.testFile.readline().rsplit(" ") # Testando com ficheiros
        #self.ser.close()
        dataLen = len(aqDataChars)
        if not (dataLen % number_of_lines):
            aqDataInt = [[0 for x in range(int(dataLen/number_of_lines))] for x in range(number_of_lines)]
            for i in range(0, dataLen):
                if aqDataChars[i].isdigit():
                    sample_nr = int(i / number_of_lines)
                    axe = i % number_of_lines
                    aqDataInt[axe][sample_nr] = int(aqDataChars[i])
                    return aqDataInt
        else:
            print("# ERROR: Aquisition Failed\n\tThe length of the data array or the number of axes is not correct (DataLen % number of axes != 0)")
            return None



a = Aquisition()
ret = a.make_an_aquisition( 5)
print(ret)
