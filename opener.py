import sys
import webbrowser

print 'running program'

while True:
	file = open('exhibits.txt', 'r')
	folderName = file.readline()
	if len(folderName) > 1:
		print folderName
		url = "http://172.16.95.216/handler1.php?exhibit=" + folderName
		print url
		webbrowser.open(url)
		print('finished')
	file.close()
