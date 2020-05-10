#!/usr/bin/env pypy
from random import randint, seed, shuffle
from bisect import bisect_left

magic_seed = 314151617181

def shuffled(arr):
  arr = arr[:]
  shuffle(arr)
  return arr

def generate(inf, fi):
  n_colours = inf[0]
  n_path = inf[1]
  n_circle = inf[2]

  path = []
  while len(path) < n_path:
    path += [randint(1,n_colours)]
  fi.write('%d\n' % n_path)
  fi.write('%s\n' % ' '.join(map(str, path)))

  assert n_colours <= n_circle
  circle = list(range(1,n_colours+1))
  while len(circle) < n_circle:
    circle += [randint(1,n_colours)]
  circle = shuffled(circle)

  fi.write('%d\n' % n_circle)
  fi.write('%s\n' % ' '.join(map(str, circle)))

cases = {
  1: [3, 10, 10],
  2: [4, 20, 10],
  3: [5, 30, 10],
  4: [10, 100, 50],
  5: [10, 100, 100],
  6: [20, 100, 100],
  7: [30, 100, 100],
  8: [40, 100, 100],
}

for tseed,tid in enumerate(cases.keys()):
  tinf = cases[tid]
  seed(magic_seed ^ tseed)
  with open('secret/%02d.in' % tid, 'w') as fi:
    generate(tinf, fi)
