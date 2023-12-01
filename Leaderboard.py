import json
from datetime import datetime as dt
import datetime
import requests
import sys
import re

y = str(datetime.datetime.now().year)

if len(sys.argv) >= 2:
	y = sys.argv[1]

cookie = {'session': "53616c7465645f5fc789412f3024b7bdecee8c292595386baca55914ca473bc02ca0efa392b1b4f36ec62bbf2e0f1ecbc29a81517f76ab85ef2ccbc81f7e0ac6"}
homepage = requests.get('https://adventofcode.com/'+y+'/leaderboard/private', cookies=cookie)
for id in re.compile(r"(?<=\/"+y+r"\/leaderboard\/private\/view\/)(\d+)").findall(homepage.content.decode()):
    print("\n"*5)
    data = json.loads(requests.get('https://adventofcode.com/'+y+'/leaderboard/private/view/'+id+'.json', cookies=cookie).content)
    i = 1
    while True:
        j = 1
        while True:
            tmp = {}
            for m in data['members'].values():
                try:
                    key = m['name'] if m['name'] is not None else m['id']
                    tmp[key] = dt.utcfromtimestamp(int(m['completion_day_level'][str(i)][str(j)]['get_star_ts']))
                except: pass
            if tmp:
                print("Day {0:>2}, part {1}:".format(i,j))
                for n, d in sorted(tmp.items(), key = lambda d: d[1]):
                    print("{0:>25}: {1}".format(n, d))
                j+=1
            else: break
        if j == 1: break
        else: i+=1