import json
from datetime import datetime as dt
import requests
import re
y = str(2020)
cookie = {'session': "53616c7465645f5f89c3b7e16683ddd949a7e0ad4148e7bca3e580bc9b33164e9da938e025b48ea1d966a9727fada7ed"}
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