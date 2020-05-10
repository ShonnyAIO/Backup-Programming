#!/usr/bin/env python

# This one is really the thickest out of all of the solutions.

def generate(to):
  v = 1
  while v <= to:
    yield v
    v += v / int(str(v)[0])
  yield v

n = int(raw_input())
r = list(generate(n))[-2:]
print r[-2 if abs(r[-2]-n) < abs(r[-1]-n) else -1]
