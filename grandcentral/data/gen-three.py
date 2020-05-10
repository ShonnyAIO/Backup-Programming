#!/usr/bin/env python2
from random import randint,shuffle

maxn = 3*10**5

next_id = 2
edges = []
def gen(my_id, parent_id, cur_l):
  assert my_id <= maxn
  global next_id
  global edges

  if parent_id <> -1:
    edges += [[parent_id, my_id]]

  children = 0
  if cur_l < 1:     children = 10110
  elif cur_l < 2:   children = 11
  elif cur_l == 2:  children = randint(0,2)
  elif cur_l == 3:  children = randint(0,1)

  for i in range(children):
    cid = next_id; next_id += 1
    gen(cid, my_id, cur_l+1)

gen(1, -1, 0)
assert(len(edges)+1 <= maxn)
print len(edges)+1
for i in edges:
  print i[0],i[1]
