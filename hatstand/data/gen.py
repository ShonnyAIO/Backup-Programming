#!/usr/bin/env python
from random import randint

c = randint(1, 10**5)
n = randint(1, 10**5)
print c, n

res = []
while len(res) < n:
  x = randint(c*52/60, c*55/60)
  if len(res) == 0 or res[-1] != x:
    res += [x]

print ' '.join(map(str, res))
