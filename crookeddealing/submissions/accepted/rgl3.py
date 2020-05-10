#!/usr/bin/env python

from collections import Counter

n, x = map(int, raw_input().split())
c = Counter(map(int, raw_input().split()))

def solve(g):
    if g * x > n:
        return None

    res = [[] for i in range(g)]
    idx = 0
    for k in c:
        for l in range(min(c[k], g)):
            if len(res[idx]) < x:
                res[idx] += [k]
                idx = (idx + 1) % g

    return res if min([len(i) for i in res]) == x else None

g = 0
radius = 2 ** 30
while radius > 0:
    if solve(g + radius) is not None:
        g += radius
    radius /= 2

if g == 0:
    print 'impossible'
else:
    for i in solve(g):
        print ' '.join(map(str, i))
