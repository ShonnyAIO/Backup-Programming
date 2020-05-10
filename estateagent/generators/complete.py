#!/usr/bin/env python

import random
import sys

seed = int(sys.argv[1])
random.seed(seed)

n = int(sys.argv[2])

sys.stdout.write('%d %d\n' % (n, n*(n-1)))
for i in range(n):
    for j in range(n):
        if i == j:
            continue
        sys.stdout.write('%d %d %d\n' % (i+1,j+1,random.randint(0,10**6)))

