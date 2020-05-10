#!/usr/bin/env python2
from random import randint,shuffle

maxn = 3*10**5
sqrtn = 50

lengths = set()
for i in range(sqrtn):
  lengths.add(randint(4, sqrtn*10))
lengths = sorted(list(lengths))

next_id = 2
edges = []
def gen(parent_id, all_l, cur_l):
  global next_id
  global edges

  if len(all_l) == 0:
    return

  my_id = next_id; next_id += 1
  edges += [[parent_id, my_id]]
  if cur_l >= all_l[-1]:
    return

  fork = (len(all_l) > 2) and (cur_l+1 < all_l[0] and randint(1,9) == 1)
  if not fork:
    gen(my_id, all_l, cur_l+1)
  else:
    s = randint(1,len(all_l)-1)
    shuffle(lengths)
    a = sorted(filter(lambda x: x > cur_l, lengths[:s]))
    b = sorted(filter(lambda x: x > cur_l, lengths[s:]))
    gen(my_id, a, cur_l+1)
    gen(my_id, b, cur_l+1)

gen(1, lengths, 1)
assert(len(edges)+1 <= maxn)
print len(edges)+1
for i in edges:
  print i[0],i[1]
