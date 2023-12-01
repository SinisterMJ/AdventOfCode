import requests
import sys
import datetime
import os
from pathlib import Path

day = datetime.datetime.now().day
year = datetime.datetime.now().year

if len(sys.argv) >= 2:
	year = sys.argv[1]
	
if len(sys.argv) == 3:
	day = sys.argv[2]

fileName = r"./inputs/" + str(year) + "/input_" + str(day) + ".txt"
filePath = r"./inputs/" + str(year) + "/"

Path(filePath).mkdir(parents=True, exist_ok=True)

if os.path.isfile(fileName):
    print ("File exist. No request should be done.")
	
cookies = dict(session='53616c7465645f5fc789412f3024b7bdecee8c292595386baca55914ca473bc02ca0efa392b1b4f36ec62bbf2e0f1ecbc29a81517f76ab85ef2ccbc81f7e0ac6')
r = requests.get("https://adventofcode.com/" + str(year) + "/day/" + str(day) + "/input", cookies=cookies)
file = open(fileName, "w") 
file.write(r.text)
file.close()
print(r.text)