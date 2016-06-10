# makeIndices.py
# Last edited by Caleb Lucas-Foley on 2016-07-10
import os
import json

for project in next(os.walk('.'))[1]:
	if not project == 'HOMEPAGE':
		for folder in ['images', 'videos']:
			index = open('./' + project + '/' + folder + '/index.json', 'w')
			media = os.listdir('./' + project + '/' + folder + '/')
			media = [item for item in media if not item.endswith('.json')]
			json.dump(media, index)
			index.close()