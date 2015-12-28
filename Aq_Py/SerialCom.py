import serial as ps

class Aquisition():
    def __init__(self):
        self.ser = ps.Serial()
        self.Aqs = {}

    def serialPortInit(self, i_baudrate = 2000000, i_port = 2, i_datasize = 8, i_stopbits = 1, i_parity = 'N'):
        self.ser.baudrate = i_baudrate
        self.ser.port = i_port
        self.ser.bytesize = i_datasize
        self.ser.parity = i_parity

    def make_an_aquisition(self, number_of_lines = 1):
        aqDataInt = []
        aqDataStr = ""

        for i in range(0, number_of_lines): #prepares de aqDataInt for the number of axes that we want
            aqDataInt.append([])

        received = ' '
        while received is not '\n':
            received = self.ser.readline()
            aqDataStr += received

        print(aqData)

a = Aquisition()

a.make_an_aquisition()
