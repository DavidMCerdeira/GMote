import GraphData as gp
import SerialCom as sc
from enum import Enum
from PIL import Image

def findFirstNonAlph(str):
    for i in range(0,len(str)):
        if not str[i].isalpha():
            return i
    return len(str)

class GMoteCmd():
    def __init__(self):
        g_pictures = {"name":"pictures", "ID":0}
        g_video =  {"name":"video", "ID":1}
        g_music =  {"name":"music", "ID":2}
        g_system_settings = {"name":"settings", "ID":3}
        g_play_pause = {"name":"play_pause", "ID":4}
        g_fullscreen = {"name":"fullscreen", "ID":5}
        g_next = {"name":"next", "ID":6}
        g_previous = {"name":"previous", "ID":7}
        g_none = {"name":"none", "ID":8}

        c_MA = {"name":"Make Aquisition","ID":"ma","Handler": self.MA_command, "Help":"MA <starting sample number>" }
        c_SG = {"name":"Set Gesture","ID":"sg", "Handler": self.SG_command, "Help":"SG <gesture name>"}
        c_WG = {"name":"What Gesture?","ID":"wg", "Handler": self.WG_command, "Help":"WG"}
        c_SSG = {"name":"Show Sample Graph","ID":"ssg", "Handler":self.SSG_command, "Help":"SSG <gesture name> <sample number>"}
        c_FS = {"name": "Finish Session", "ID":"fs", "Handler":self.FS_command, "Help": "FS"}
        c_PC = {"name": "Print commands", "ID":"pc", "Handler":self.print_commands,"Help":"PC"}
        c_PG = {"name": "Print gestures", "ID":"pg", "Handler":self.print_gestures,"Help":"PG"}
        c_HLP = {"name": "Help", "ID":"hlp", "Handler":self.print_help,"Help":"HLP"}

        self.saveSamplesDirectory = ".\\..\\TrainingData\\%s\\"
        self.curGest = g_none["name"]
        self.commands = (c_MA, c_SG, c_WG, c_FS, c_SSG, c_PC, c_PG, c_HLP)
        self.gestures = (g_pictures, g_video, g_music, g_system_settings, g_play_pause, g_fullscreen, g_next, g_previous, g_none)
        self.On = True

    def Run_cmdLine(self):
        print("--------------------GMOTE Training Command Line--------------------\nTry 'HLP' for help\n")
        while self.On is True:
            print("\nWrite a command:")
            inputCmd = input("> ")
            firstNonAlph = findFirstNonAlph(inputCmd)
            cmdInd = self.which_command(inputCmd[0: firstNonAlph])
            if cmdInd is not None:
                self.commands[cmdInd]["Handler"](inputCmd[firstNonAlph : len(inputCmd)])

    def getArguments(self, in_Args):
        args = in_Args.split(" ")
        args_int = []
        args_str = []
        for val in args:
            if val.isdigit():
                args_int.append(int(val))
            else:
                args_str.append(val)
        return {"ints" : args_int, "strs" : args_str}

    def which_command(self, in_command):
        for i in range(0, len(self.commands)):
            if self.commands[i]["ID"] == in_command:
                return i
        print("# ERROR: Unknown Command\n")
        return None

    def isGesture(self, in_gest):
        for i in range(0, len(self.gestures)):
            if self.gestures[i]["name"] == in_gest:
                return True
        return False

    def MA_command(self, in_command):
        print("** Make An Aquisition\n")
        aqOn = True
        arg = self.getArguments(in_command)
        if not arg["ints"]:
            print("# ERROR: Doesn't know for which sample nr to start")
            return
        if self.curGest == "none":
            print("# ERROR: Current gesture is not defined")
            return
        sample_nr = arg["ints"][0]
        while aqOn:
            aq = sc.Aquisition()            #Probably when used with serial port will give some problems
            data = aq.make_an_aquisition()
            aline = gp.line(iData = data)
            graph = gp.graph(iLines_set = [aline])
            print("\t$ Aquired data: ")
            print(data)
            #graph.show()
            response = " "
            while response != 'y' and response !='n':
                response = input("\t$ Do you want to save this sample?(y/n) ")
            if response == 'y':
                tempdir = self.saveSamplesDirectory % self.curGest
                graph.save_graph(tempdir, str(sample_nr))
            response = ' '
            while response != 'y' and response != 'n':
                response = input("\t$ Make another Aquisition?(y/n) ")
            if response == 'n':
                aqOn = False
            else:
                sample_nr += 1
        print("\t  Aquisition Finished...")

    def SG_command(self, in_command):
        print("** Set Gesture\n")
        args = self.getArguments(in_command)
        if self.isGesture(args["strs"][1]):
            self.curGest = args["strs"][1]
            print("\tGesture Setted...")
        else:
            print("# ERROR: That's not a gesture")

    def WG_command(self, in_command):
        print("** Which Gesture?\n")
        temp_str = "\t$ Current Gesture : %s" % self.curGest
        print(temp_str)

    def SSG_command(self, in_command):
        print("** Show Sample Graph:")
        arg = self.getArguments(in_command)
        if not arg["ints"]:
            print("# ERROR: Sample number is missing\n")
            return
        sample = arg["ints"][0]
        if self.curGest == "none":
            print("# ERROR: Current gesture is not defined\n")
            return
        print("\t Showing Graph...")
        tempdir = self.saveSamplesDirectory % self.curGest
        f = Image.open(tempdir + str(sample) + ".png")
        f.show()

    def FS_command(self, in_command):
        print("** Finish Session\n")
        print("\tTraining Session is finished...")
        self.On = False

    def print_gestures(self, args):
        print("\n**These are the GMote's moves:\n")
        print("\n\t  <name> - <ID>")
        for i in range(0,len(self.gestures)):
            temp_str = "\t$ %(name)s - %(ID)s" % self.gestures[i]
            print(temp_str)

    def print_commands(self, args):
        print("\n**These are the GMote's Command line commands:\n")
        print("\n\t  <name> - <ID>")
        for i in range(0,len(self.commands)):
            temp_str = "\t$ %(name)s - %(ID)s" % self.commands[i]
            print(temp_str)

    def print_help(self,args):
        print("\n**This is the Help for GMOTE Command Line")
        print("\n\t  <command name> - <input cmd>")
        for i in range(0,len(self.commands)):
            temp_str = "\t$ %(name)s - '%(Help)s'" % self.commands[i]
            print(temp_str)


g = GMoteCmd()
g.Run_cmdLine()
