#!/usr/bin/env pypy
import sys
import random

n = int(raw_input())
assert 1 <= n <= 3 * 10**5

new_labels = [i for i in range(n)]
random.shuffle(new_labels)

new_edges = []
for i in range(n-1):
  a,b = map(int, raw_input().split())
  if random.randint(0, 1) == 0:
    new_edges += [(new_labels[a-1]+1, new_labels[b-1]+1)]
  else:
    new_edges += [(new_labels[b-1]+1, new_labels[a-1]+1)]
random.shuffle(new_edges)

print n
for a,b in new_edges:
  print a,b
