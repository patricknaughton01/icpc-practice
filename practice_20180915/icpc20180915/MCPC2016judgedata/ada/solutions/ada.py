#!/usr/bin/env python3
import operator

n, *seq = map(int, input().split())
tot = seq[-1]
while len(set(seq)) > 1:
    seq = list(map(operator.sub, seq[1:], seq))
    tot += seq[-1]
print(n - len(seq), tot)
