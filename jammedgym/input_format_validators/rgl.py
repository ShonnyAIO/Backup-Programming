#!/usr/bin/env python
import sys

n = int(raw_input())
assert 1 <= n <= 100

agenda = map(int, raw_input().split())
assert len(agenda) == n
for i in agenda:
  assert 1 <= i <= 100

m = int(raw_input())
assert 1 <= m <=100

stations = map(int, raw_input().split())
assert len(stations) == m
for i in stations:
  assert 1 <= i <= 100

stations = set(stations)
for i in agenda:
  assert i in stations

sys.exit(42)
