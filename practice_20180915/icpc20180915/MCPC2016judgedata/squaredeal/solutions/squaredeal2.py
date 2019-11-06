#!/usr/bin/env python3

p1, p2, p3 = p =[list(map(int, input().split())) for i in range(3)]
print('YES' if (sum((h*w for (h, w) in p)) == p1[0]**2 and (p1[0] == p3[0] or
	                 (p1[0]-p1[1] in set(p2).intersection(set(p3))))) 
            else 'NO')

