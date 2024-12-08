import requests
import sys
import datetime
import os
from pathlib import Path

day = datetime.datetime.now().day
year = datetime.datetime.now().year

start_year = 2015
max_day = 25


for y in range(start_year, year + 1):
    for d in range(1, max_day + 1):
        if d > day and y == year:
            continue

        fileName = r"./inputs/" + str(y) + "/input_" + str(d) + ".txt"
        filePath = r"./inputs/" + str(y) + "/"

        Path(filePath).mkdir(parents=True, exist_ok=True)

        if os.path.isfile(fileName):
            continue
            
        cookies = dict(session='53616c7465645f5fb39dce8967cd5f0d658dc39f2f1e1c303b16864af0d7ccc501f191948b416e25e68cc0dad5f9606a273ad47b8c3228b968e3389cb8bf4208')
        r = requests.get("https://adventofcode.com/" + str(y) + "/day/" + str(d) + "/input", cookies=cookies)
        file = open(fileName, "w") 
        file.write(r.text)
        file.close()
        print(r.text)