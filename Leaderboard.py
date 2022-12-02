import json
from datetime import datetime as dt
import datetime
import requests
import sys
import re

y = str(datetime.datetime.now().year)

if len(sys.argv) >= 2:
	y = sys.argv[1]

cookie = {'session': "53616c7465645f5f80ca48d9631222f9cc5e80866539b57afc1d56d4ea106a43e0a2ddc498134b5a5a1852c94aa28e7009c2883d35adcd11558cfbb88a5438ce"}
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