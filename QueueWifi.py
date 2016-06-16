#!/usr/bin/env python

# Raspberry Pi Wifi
#
#   purpose: designed to open php pages specified by a local file at regular
#            intervals
#   created by: ___ all names here ____
#   completed (demo) on: _____ today hopefully _____


import selenium.webdriver as webdriver
from time import sleep

browser = webdriver.Firefox()
browser.maximize_window()
browser.get("http://localhost/slideshow.php")

while True:
	sleep(0.5)
	file = open('/var/www/html/exhibits.txt', 'r+')
        folderName = file.readline().strip()
        file.truncate(0)
	file.close()
	
	if folderName:
		host = "localhost" # or 130.64.95.38 (this Raspberry Pi's IP)
                url = "http://" + host + "/slideshow.php?exhibit=" + folderName
                print url
                browser.get(url)
                print('page opened')
                sleep(4)
