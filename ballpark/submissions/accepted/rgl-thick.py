#!/usr/bin/env python

n = float(raw_input())
p = 1
while n > 10:
    n /= 10.0
    p *= 10

print int(round(n)) * p
