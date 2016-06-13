# Raspberry Pi Wifi
#
#   purpose: designed to _____
#   created by: ______ all names here ____
#   completed (demo) on: _____ today hopefully _____


import webbrowser
import time
import Queue
import easygui
from Tkinter import Tk

def openPage(folderName):
	url = "http://130.64.95.38/slideshow.php?exhibit=" + folderName
	print url
	webbrowser.open(url,new=0)
	print('page opened')


while True:
	file = open('exhibits.txt', 'r')
	# TODO: remove the line from the .txt doc
	#	reset the .txt file?
        folderName = file.readline()
	file.close()	
	
	if (folderName != '') and (folderName != "\n") and (folderName != " "):
		openPage(folderName)
		file = open('exhibits.txt', 'w')
        	file.truncate()
        	file.close()

	# create message box using GUI
		#easygui.msgbox("Your Video request has been put in queue", title = "Request Status")
	# Close Message box
		

