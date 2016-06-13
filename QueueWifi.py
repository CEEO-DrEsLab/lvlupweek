# Raspberry Pi Wifi
#
#   purpose: designed to _____
#   created by: ______ all names here ____
#   completed (demo) on: _____ today hopefully _____

#TODO: edit repetitive videos in queue

import webbrowser
import time
import Queue
import easygui
from Tkinter import Tk

def openPage(folderName):
	url = "http://130.64.95.38/wrapper.php?exhibit=" + folderName
	print url
	webbrowser.open(url,new=0)
	print('page opened')

QUEUE_SIZE = 3
PiQueue = Queue.Queue(QUEUE_SIZE)

condition = True

while condition:
	file = open('exhibits.txt', 'r')
	# TODO: remove the line from the .txt doc
	#	reset the .txt file?
        folderName = file.readline()
	file_contents = file.read()
        print folderName
	print "and here's the rest!"
	print file_contents
	file.close()
        file = open('exhibits.txt', 'w')
	file.write(file_contents)
        file.close()
        if (folderName == '') or (folderName is "\n") or (folderName is " "):
                print "blank"
                openPage("")
                print "opened page"
                
        if (folderName not in PiQueue.queue) and (folderName is not None):
		PiQueue.put(folderName)
		with tk(timeout=3):
			# create message box using GUI
			easygui.msgbox("Your Video request has been put in queue", title = "Request Status")
		# Close Message box
		
		# get first item in queue
		toPlay = PiQueue.get(0)
		openPage(toPlay)
		time.sleep(30)
		# start to play video; send signal, whatnot - DO
		while PiQueue.qsize() != 0:
			continue
      
                #else:
		# open default page
		#openPage("")
		#time.sleep(5)


