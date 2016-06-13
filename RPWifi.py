#!/usr/bin/env python

# Raspberry Pi Wifi
#
#   purpose: designed to open a web page in the current browser tab
#   created by: ______ all names here ____
#   completed (demo) on: _____ today hopefully _____

import webbrowser
from sys import argv

if len(argv) < 2:
	exit("Error: You done goof'd! Should be 2: %d" % len(argv))

folderName = argv[1]
url = "http://130.64.95.38/slideshow.php?exhibit=" + folderName
webbrowser.open(url)
