# Raspberry Pi Wifi
#
#   purpose: designed to _____
#   created by: ______ all names here ____
#   completed (demo) on: _____ today hopefully _____


import webbrowser
import time

QUEUE_SIZE = 3
PiQueue.Queue(QUEUE_SIZE)

condition = True
playing = False

while condition:
    if serial.read == 'file name' and playing == True:
        # 'playing right now' clause; otherwise triggered after each button
        if serial.read not in PiQueue.__item_pool:
            PiQueue.put(serial.read)
        time.sleep(180)
        # get first item in queue
        PiQueue.get(0)
        # start to play video; send signal, whatnot - DO
        while PiQueue.queuesize != 0:
            continue
        playing = False
    else if serial.read == 'file name':
        # only automatic is playing
        # stop automatic video - DO
        PiQueue.put(serial.read)
        playing = True
        PiQueue.get(0)
        # play this video
    else
        # play waiting video here
        time.sleep(60)