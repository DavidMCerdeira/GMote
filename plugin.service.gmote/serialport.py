
import sys
sys.path.append("C:\Python27\Lib\site-packages")
import serial as ps

def serialPortInit(i_baudrate = 2000000, i_port = "COM3", i_datasize = 8, i_stopbits = 1, i_parity = 'N'):
	ser = ps.Serial()
	ser.baudrate = i_baudrate
	ser.port = i_port
	ser.bytesize = i_datasize
	ser.parity = i_parity
	#ser.open()
	#self.ser.close()
	return ser

def getstr(ser, itimeout):
	ser.timeout = itimeout 
	ser.open()
	#char = ' '
	#mstr=""
	#while char is not '\n':
	mstr = ser.readline().decode("utf-8")
	ser.reset_input_buffer()
	ser.close()
	return mstr

#mySer = serialPortInit()
#print(mySer.timeout)
#str = getstr(mySer, None)
#print(str)
#str = getstr(mySer, 0.5)
#print(ord(str))
#print("Finish")

