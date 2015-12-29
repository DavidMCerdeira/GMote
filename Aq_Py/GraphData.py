import matplotlib.pyplot as plt
import numpy as np
from PIL import Image

class line():
    def __init__(self,iLabel="Aquired data",iLine_color="r",iData = []):
        self.label = iLabel
        self.color = iLine_color
        self.data  = iData

    def plot_it(self):
        self.plot,= plt.plot(self.data,self.color,label = self.label)

class graph():
    def __init__(self,iTitle = "Sample",iXLabel="t",iYLabel="Idx",iLines_set = []):
        self.title  = iTitle
        self.xlabel = iXLabel
        self.ylabel = iYLabel
        self.lines_set = iLines_set
        self.figure = None

    def show(self):
        self.plot_lines()
        self.figure = plt.gcf()
        plt.show()

    def lines_set_insert(line):
        self.lines_set.append(line)

    def plot_lines(self):
        plt.xlabel(self.xlabel)
        plt.ylabel(self.ylabel)
        plt.title(self.title)
        legend_plot = []
        for i in (self.lines_set):
            i.plot_it()
            legend_plot.append(i.plot)
        plt.legend(handles=legend_plot)

    def save_graph(self,directory,file_name):
        direcPlusFile = directory + file_name
        graphCsvFile = open(directory + file_name + ".csv",'w')
        if self.figure is not None:
            self.figure.savefig(direcPlusFile)
            self.figure = None
        else:
            self.plot_lines()
            plt.savefig(direcPlusFile)
        writeLine = ""
        for i in range( 0,len(self.lines_set[0].data)):
            for j in range( 0,len(self.lines_set)):
                writeLine = writeLine + str(self.lines_set[j].data[i])
                if j != len(self.lines_set) - 1 :
                    writeLine  = ", "
            writeLine = writeLine + "\n"
        graphCsvFile.write(writeLine)
'''
#Making some tests
y2 = [7,6,5,4,3,2,1]
y3 = [3,3,3,3,3,3,3]
l1 = line('accelx','r',[1,2,3,4,5,6,7])
l2 = line('accely','b',y2)

l3 = line('acclez','g',y3)
h = graph('mygraph','x','y',[l1,l2,l3])
h.show()
h.save_graph('.\\Graphs\\',' ')
'''
'''
class command():
    def __init__(self, ID, name, handler):
        self.commandID = ID
        self.commandName = name
        self.handler = handler

class command_set(enum):
'''
