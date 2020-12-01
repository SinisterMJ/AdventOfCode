import requests
import sys
import datetime
import os
	
day = datetime.datetime.now().day
year = datetime.datetime.now().year

if len(sys.argv) >= 2:
	year = sys.argv[1]
	
if len(sys.argv) == 3:
	year = sys.argv[2]

fileName = r"./inputs/input_" + str(year) + "_" + str(day) + ".txt"

if os.path.isfile(fileName):
    print ("File exist. No request should be done.")
	
cookies = dict(session='53616c7465645f5fa4afdc8e21d3e374b3cd916c9712115ac698fc8e9bf02cc6c2a4d03e7e18083208b0b457d38f895a')
r = requests.get("https://adventofcode.com/" + str(year) + "/day/" + str(day) + "/input", cookies=cookies)
file = open(fileName, "w") 
file.write(r.text)
file.close()
