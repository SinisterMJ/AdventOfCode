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
	
cookies = dict(session='53616c7465645f5f89c3b7e16683ddd949a7e0ad4148e7bca3e580bc9b33164e9da938e025b48ea1d966a9727fada7ed')
r = requests.get("https://adventofcode.com/" + str(year) + "/day/" + str(day) + "/input", cookies=cookies)
file = open(fileName, "w") 
file.write(r.text)
file.close()
