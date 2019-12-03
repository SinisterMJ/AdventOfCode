import requests
import sys
import datetime

if len(sys.argv) < 2:
	print("Wrong number of arguments")
	exit()
	
day = sys.argv[1]
year = datetime.datetime.now().year

if len(sys.argv) == 3:
	year = sys.argv[2]

fileName = r"./input" + str(year) + "_" + str(day) + ".txt"

if os.path.isfile(fileName):
    print ("File exist. No request should be done.")
	
cookies = dict(session='..yourID..')
r = requests.get("https://adventofcode.com/" + str(year) + "/day/" + str(day) + "/input", cookies=cookies)
file = open(fileName, "w") 
file.write(r.text)
file.close()
  