#!/usr/bin/env python3

'''
If all remaining point are on the same side,
then any choice will give the same direction for the chosen pt,
so look ahead one further:  If choose most ccw, next sure 
to be right; if choose most cw, next sure to be left,
plus the condition that all point be on one side of the
line of the last segment holds up inductively.

In this version start from pt with minimum (x, y), p0,
so can add initial pt underneath so all points on 
same side of the line between those two points.
'''
import math, sys

def dif(p0, p1):
    return p0[0] - p1[0],  p0[1] - p1[1]

def ang(p0, p1, p2): # angle p1-p0 to p2-p1, -pi to pi
    (x,y), (x1, y1) = dif(p1, p0), dif(p2, p1)
    return math.atan2(x*y1 - x1*y, x*x1 + y*y1)

def do(s):
    lines = s.splitlines()
    dir = lines.pop()
    lines.pop(0) # N implicit
    pts = [tuple(map(int, line.split())) for line in lines]
    (x, y) = p0 = min(pts)
    ordered = [(x, y-1), p0] # first is dummy, later removed
    rest = pts[:] # points not yet used
    rest.remove(p0)
    for d in dir:
        (a, pm) = max([(ang(ordered[-2], ordered[-1], p) *
                         (1 if d=='R' else -1), p) for p in rest])
        ordered.append(pm)
        rest.remove(pm)
    # one element left in rest after loop - only choice left
    perm = [pts.index(p)+1 for p in ordered[1:] + rest]
    print(' '.join((map(str, perm))))
#    print(*[pts[i-1] for i in perm], dir)

s5 = '''5
2 5
1 6
4 4
5 0
4 2
RLL'''
s3 = '''3
4 2
2 3
1 1
R'''

s4 = '''4
1 1
2 1
2 2
1 2
RL'''

do(sys.stdin.read())
