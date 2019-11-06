#!/usr/bin/env python3 
'''Delivery ACM Mid-Central Regional  Andy Harrington'''

def oneSide(K, pairs):
    '''big x to small, all positive, return total dist
    essential point - start far from origin'''
    tot = 0 # 1 way - double at end
    if not pairs: return 0
    xFar, t = pairs.pop()
    while(1):
        tot += xFar*(t // K)
        t %= K
        if not pairs: 
            return tot + (xFar if t > 0 else 0)
        if t == 0:
            xFar, t = pairs.pop()
            continue
        while pairs  and t < K:
            x, tn = pairs.pop()
            t += tn
        if t >= K:
            tot += xFar
            t = t - K
            xFar = x

def fromInput():
    N, K = map( int, input().split())
    pairs = [map( int, input().split()) for i in range(N)]
    do(K, pairs)

def do(K, pairs):
    neg = []
    pos = []
    for x,t in pairs:
        if x <0:
            neg.append((-x, t))
        else:
            pos.append((x, t))
    neg.reverse()
    print(2*(oneSide(K, neg) + oneSide(K, pos)))

##do(100, [(-10, 50), (10, 175), (25, 10)])
##do (2, [(-20, 1000), (-10, 1000)])
##do (2, [
##(-1002, 1000),
##(-1001, 1000),
##(-1000, 1000),
##(-999, 1000),
##(-998, 1000)])
#do(100, [(-40, 2), (-25, 25), (-10, 175), (10, 175), (25, 25), (40, 2)])
fromInput()
