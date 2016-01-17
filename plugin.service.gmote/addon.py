import xbmc
import xbmcgui
import serialport as sp

class GMoteCmds():
	def __init__(self):
		#Actions
		index = 0
		cmd_Vplus 	  = {"ID": index, "name":"VolumeUp", "builtin":"Action(%s)"}
		index += 1
		cmd_Vless 	  = {"ID": index, "name":"VolumeDown", "builtin":"Action(%s)"}
		index += 1
		cmd_OK 	  	  = {"ID": index, "name":"Select", "builtin":"Action(%s)"}
 		index += 1
		cmd_FF	  	  = {"ID": index, "name":"FastForward", "builtin":"Action(%s)"}
		index += 1
		cmd_Rewind    = {"ID": index, "name":"Rewind", "builtin":"Action(%s)"}
		index += 1
		cmd_Up 		  = {"ID": index, "name":"Up", "builtin":"Action(%s)"}
		index += 1
		cmd_Down 	  = {"ID": index, "name":"Down", "builtin":"Action(%s)"}
		index += 1
		cmd_Left 	  = {"ID": index, "name":"Left", "builtin":"Action(%s)"}
		index += 1
		cmd_Right 	  = {"ID": index, "name":"Right", "builtin":"Action(%s)"}
		index += 1
		cmd_PlayPause = {"ID": index, "name":"PlayPause", "builtin":"Action(%s)"}

		#Windows
		index += 1
		cmd_Fullscrn  =	{"ID": index, "name":"FullScreen", "builtin":"Action(%s)"}
		index += 1
		cmd_Pic 	  =	{"ID": index, "name":"Pictures", "builtin":"ActivateWindow(%s)"}
		index += 1
		cmd_Video 	  =	{"ID": index, "name":"Videos", "builtin":"ActivateWindow(%s)"}
		index += 1
		cmd_Music 	  =	{"ID": index, "name":"Music", "builtin":"ActivateWindow(%s)"}
		index += 1
		cmd_SysSet 	  =	{"ID": index, "name":"Settings", "builtin":"ActivateWindow(%s)"}
		index += 1
		cmd_Next	  = {"ID": index, "name":"SkipNext", "builtin":"Action(%s)"}
		index += 1
		cmd_Previous  = {"ID": index, "name":"SkipPrevious","builtin":"Action(%s)"}
		#WindowsLimit  = 16

		self.NR_OF_CMDS = index + 1
		self.Cmds =(cmd_Vplus, cmd_Vless, cmd_OK, cmd_FF, cmd_Rewind, cmd_Up, cmd_Down, cmd_Left, cmd_Right, cmd_PlayPause, cmd_Fullscrn, cmd_Pic, cmd_Video, cmd_Music, cmd_SysSet, cmd_Next, cmd_Previous)

if __name__ == '__main__':
    monitor = xbmc.Monitor()
    ser = sp.serialPortInit()
    dialog = xbmcgui.Dialog()
    g_cmds = GMoteCmds()
    dialog.notification("GMOTE", "Hello! You're Using GMOTE!!", xbmcgui.NOTIFICATION_INFO,2000)
    while not monitor.abortRequested():
		cmd = sp.getstr(ser, None)
		cmdInt = int(cmd)
		for i in range(0, len(g_cmds.Cmds)):
				if(g_cmds.Cmds[i]["ID"] == cmdInt):
					cmdIndex = i
					break
		#dialog.notification("GMOTE", "cmdIndex: %d" % cmdIndex, xbmcgui.NOTIFICATION_INFO,2000)
		if cmdInt < len(g_cmds.Cmds) and cmdInt > 2:
			xbmc.executebuiltin(g_cmds.Cmds[cmdIndex]["builtin"] % g_cmds.Cmds[cmdIndex]["name"])
			if(cmdInt > 8):
				dialog.notification("GMOTE", "Command: %d\n" % g_cmds.Cmds[cmdIndex]["ID"], xbmcgui.NOTIFICATION_INFO,2000)
		elif cmdInt == 0 or cmdInt == 1:
			for i in range(0, 10):
				xbmc.executebuiltin(g_cmds.Cmds[cmdIndex]["builtin"] % g_cmds.Cmds[cmdIndex]["name"])
		elif cmdInt == 2:
			cmd = sp.getstr(ser, 0.5)
			if len(cmd) is not 0:
				if int(cmd) == 2 :
					xbmc.executebuiltin("Action(Back)")
			else:
				xbmc.executebuiltin(g_cmds.Cmds[cmdIndex]["builtin"] % g_cmds.Cmds[cmdIndex]["name"])
		elif cmdInt == 30:
			dialog.notification("GMOTE", "Gesture Not recognized!", xbmcgui.NOTIFICATION_INFO, 2000)
		elif cmdInt == 21:
			dialog.notification("GMOTE", "Accelerometer Control unactive", xbmcgui.NOTIFICATION_INFO, 2000)
		elif cmdInt == 20:
			dialog.notification("GMOTE", "Accelerometer Control active", xbmcgui.NOTIFICATION_INFO, 2000)
