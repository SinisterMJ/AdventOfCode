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
	
cookies = dict(session='53616c7465645f5f3b355fbfbe0feb640d9d308c0f16501f3e11d34c4f1b4e506b00db17636a53b21a2f63809254c528f751de1c859a5c7c177c738356c48f85')
r = requests.get("https://adventofcode.com/" + str(year) + "/day/" + str(day) + "/input", cookies=cookies)
file = open(fileName, "w") 
file.write(r.text)
file.close()
