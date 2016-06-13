#!/usr/bin/env python

# Raspberry Pi Wifi
#
#   purpose: designed to _____
#   created by: ______ all names here ____
#   completed (demo) on: _____ today hopefully _____

import webbrowser
import time
from sys import argv
import os
import pwd

def openPage(folderName):
        url = "http://130.64.95.38/slideshow.php?exhibit=" + folderName
        print url
        webbrowser.open(url,new=1,autoraise=True)
        print('page opened')

print len(argv)
print "UID: " + str(os.getuid())
print "User: "
print pwd.getpwuid(os.getuid())

if len(argv) < 2:
	exit("Error: You done goof'd! Should be 2: %d" % len(argv))

folderName = argv[1]
print folderName
openPage(folderName)
#time.sleep(3)
