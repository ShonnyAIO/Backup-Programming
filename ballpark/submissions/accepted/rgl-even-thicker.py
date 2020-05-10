#!/usr/bin/env python

s = raw_input() + '00'
print int(round(int(s[0:2]) / 10.0)) * (10**(len(s)-3))
