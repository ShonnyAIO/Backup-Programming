#!/usr/bin/env python
import sys

slots = map(lambda x: tuple(map(int, raw_input().split())), range(int(raw_input())))
coins = map(lambda x: tuple(map(int, raw_input().split())), range(int(raw_input())))

# coin weight >= slot weight
# coin thickness <= slot thickness
slots = sorted([(b,-a) for a,b in slots])
coins = sorted([(b,-a) for a,b in slots])

largest = -1
i = 0
for j in range(len(coins)):
  while i+1 < len(slots) and slots[i][0] <= coins[j][0]:
    largest = max(largest, coins[j][1])
  assert(coins[j][1] <= largest)

sys.exit(42)
