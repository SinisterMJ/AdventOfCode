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
	
cookies = dict(session='53616c7465645f5fa272dca963fd4b401cc690a7fa07b6a99b9bf547e336db44580aad51ef022f0bac10f58c2fad6b647e0f325a47889c62fd9d968fd64c09c8')
r = requests.get("https://adventofcode.com/" + str(year) + "/day/" + str(day) + "/input", cookies=cookies)
file = open(fileName, "w") 
file.write(r.text)
file.close()
