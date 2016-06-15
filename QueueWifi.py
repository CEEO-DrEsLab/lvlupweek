#!/usr/bin/env python

# Raspberry Pi Wifi
#
#   purpose: designed to _____
#   created by: ______ all names here ____
#   completed (demo) on: _____ today hopefully _____


import selenium.webdriver as webdriver
from time import sleep
#import Queue
#import easygui
#from Tkinter import Tk

b = webdriver.Firefox()

def openPage(folderName):
	host = "localhost" # or 130.64.95.38 (this Raspberry Pi's IP)
	url = "http://" + host + "/slideshow.php?exhibit=" + folderName
	print url
	b.maximize_window()
	b.get(url)
	print('page opened')


while True:
	sleep(0.5)
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
		

