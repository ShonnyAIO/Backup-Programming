#!/usr/bin/env python3

import collections

n, m = map(int, input().split())
ordering = list(map(int, input().split()))

access = dict()
for i in range(1, n):
    access[i] = 0

def swap(positions, current, target):
    global access

    access[positions[target]] += 1
    positions[current], positions[target] = positions[target], positions[current]

    return positions[current]

def simulate(positions, ordering):
    positions = positions.copy()
    current, ordering = ordering[0], ordering[1:]
    dist = 0
    for x in ordering:
        dist += swap(positions, current, x)
        current = x
    return dist

def nth(y):
    return lambda x: x[y]

positions, snoitisop = dict(), dict()
for i in range(1, n+1):
    positions[i] = i if i < ordering[0] else i-1 if i > ordering[0] else 0
    snoitisop[positions[i]] = i
simulate(positions, ordering)

initial = [0] + list(map(nth(0), sorted(access.items(), key=nth(1), reverse=True)))
for i in range(n):
    positions[snoitisop[initial[i]]] = i
print(simulate(positions, ordering))

del positions[ordering[0]]
result = list(map(nth(0), sorted(positions.items(), key=nth(1), reverse=True)))
print(' '.join(map(str, result)))
