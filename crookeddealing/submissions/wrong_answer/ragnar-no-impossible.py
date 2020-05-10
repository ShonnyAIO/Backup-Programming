#!/usr/bin/env python3

n, h = [int(x) for x in input().split()]
v = [int(x) for x in input().split()]
vm = dict()
for x in v:
    if x not in vm: vm[x] = 0
    vm[x] += 1

t = sum(v)
mink = 1
maxk = t//h

while mink < maxk:
    k = (mink+maxk)//2+1
    c = sum(min(k, vm[x]) for x in vm)
    if c >= h*k: mink = k
    else: maxk = k-1

k = mink
ans = [[] for _ in range(k)]
i = 0
for x in vm:
    for j in range(min(vm[x], k)):
        ans[i].append(x)
        i = (i+1)%k
        if i==0 and len(ans[0]) == h: break;
    if i==0 and len(ans[0]) == h: break;
for a in ans: print(*a)
