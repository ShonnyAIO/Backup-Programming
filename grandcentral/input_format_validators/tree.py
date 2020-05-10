#!/usr/bin/env pypy
import sys

n = int(raw_input())
assert 1 <= n <= 3 * 10**5

p = [x for x in range(n)]
r = [0 for x in range(n)]
def findroot(a):
  global p,r
  if p[a] <> a:
    p[a] = findroot(p[a])
  return p[a]
def join(a, b):
  global p,r
  a = findroot(a)
  b = findroot(b)
  if a == b:
    return False
  if r[a] < r[b]:
    a,b = b,a
  p[b] = a
  r[a] += 1
  return True

for i in range(n-1):
  a,b = map(int, raw_input().split())
  assert 1 <= a <= n
  assert 1 <= b <= n
  assert a <> b
  assert join(a-1,b-1)

sys.exit(42)
