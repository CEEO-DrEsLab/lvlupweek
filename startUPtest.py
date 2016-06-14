# startUPtest.py

import selenium.webdriver as webdriver
from time import sleep

if __name__ == "__main__":
	urls = ['http://www.google.com', 'http://www.yahoo.com']

b = webdriver.Firefox()

while True:
	for idx, url in enumerate(urls):
		b.maximize_window()
		b.get(url)
		sleep(5)
