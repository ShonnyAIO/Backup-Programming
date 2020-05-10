#!/usr/bin/env python3

n,k = map(int, input().split())
items = list(map(int, input().split()))

residence = [i for i in range(n)]
knocks = [[0, i] for i in range(n)]
held = items[0]-1
for i in items[1:]:
  knocks[i-1][0] += 1
  residence[held] = residence[i-1]
  held = i-1

knocks = [(a, -b) for a, b in knocks]
knocks = list(sorted(knocks, reverse=True))
knocks = [(a, -b) for a, b in knocks]
knocks = [i for i in knocks if i[1]+1 != items[0]]

pos = {}
for i in range(len(knocks)):
    pos[knocks[i][1]+1] = i

cost = 0
held = items[0]
pos[held] = 0
for i in items[1:]:
    cost += 1 + pos[i]
    pos[held] = pos[i]
    pos[i] = 0
    held = i

knocks = [i[1]+1 for i in knocks if i[1]+1 != items[0]]

print(cost)
print(' '.join(map(str,knocks)))
