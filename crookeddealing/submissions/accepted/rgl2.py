#!/usr/bin/env python

from collections import Counter

n, x = map(int, raw_input().split())
c = Counter(map(int, raw_input().split()))
c = sorted([(c[i], i) for i in c])

i, good, groups, bg = 0, 0, 0, None
while True:
    if i < len(c) and c[i][0] <= groups:
        good += c[i][0]
        i += 1
    elif good + groups * (len(c) - i) >= groups * x:
        bg = groups
        groups += 1
    else:
        break

if bg is None:
    print 'impossible'
else:
    res = sum([[j[1] for _ in range(min(j[0], bg))] for j in c], [])
    for i in range(bg):
        print ' '.join(map(str, res[i:x*bg:bg]))
