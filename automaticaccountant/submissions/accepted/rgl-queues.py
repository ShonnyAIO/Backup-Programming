#!/usr/bin/env python

slots = map(lambda _: tuple(map(int, raw_input().split()) + [_]), range(int(raw_input())))
coins = map(lambda _: tuple(map(int, raw_input().split()) + [_]), range(int(raw_input())))

max_size = max(map(lambda i: i[0], coins)) + 1
used = set()

groups = dict()
def insert(l,r,s,v):
  for i in range(20):
    lr = l * (2**20) + r
    if lr not in groups: groups[lr] = [v]
    else: groups[lr] += [v]

    if l+1 <> r:
      m = (l+r) / 2
      if s < m: r = m
      else: l = m
    else:
      return

def trim(l,r):
  lr = l * (2**20) + r
  if lr in groups:
    while len(groups[lr]) > 0 and groups[lr][-1][1][2] in used:
      groups[lr].pop()

def findmax(l,r,a,b):
  if b <= l or r <= a: return None

  trim(l,r)
  lr = l * (2**20) + r
  if lr not in groups or len(groups[lr]) == 0: return None
  if a <= l and r <= b: return groups[lr][-1][1]

  if l+1 <> r:
    m = (l+r) / 2
    u = findmax(l,m,a,b) if a < m else None
    v = findmax(m,r,a,b) if b > m else None
    return u if v is None or u is not None and u[1] > v[1] else v
  else:
    return None

for i in coins:
  insert(0,max_size,i[0],(i[1],i))

for i in groups.values(): i.sort()

res = 0

for i,s in zip(range(len(slots)), slots):
  while True:
    x = findmax(0,max_size,0,s[0]+1)
    if x is None or x[1] < s[1]:
      break
    else:
      used.add(x[2])
      # print 'coin',x,'into slot',i+1,'=',s
      res += i+1

print res
