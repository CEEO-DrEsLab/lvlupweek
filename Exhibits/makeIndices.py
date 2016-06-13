#!/usr/bin/env python

# makeIndices.py
# Last edited by Caleb Lucas-Foley on 2016-07-10
#
# Makes index.json files for videos and images
import os
import json

for project in next(os.walk('.'))[1]:
	for folder in ['images', 'videos']:
		mediaDirectory = './' + project + '/' + folder
		if not os.path.exists(mediaDirectory):
			os.makedirs(mediaDirectory)
		index = open(mediaDirectory + '/index.json', 'w')
		media = os.listdir(mediaDirectory)
		media = [item for item in media if not item.endswith('.json')]
		json.dump(media, index)
		index.close()
