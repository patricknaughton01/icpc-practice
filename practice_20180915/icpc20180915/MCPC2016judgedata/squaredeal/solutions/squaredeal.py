#!/usr/bin/env python3

(h1, w1), (h2, w2), (h3, w3) = [list(map(int, input().split()))
                                 for i in range(3)]
d = h1 - w1                                    
print('YES' if (h2*w2+h3*w3 == h1*d and (h1 == h3 # case 1
                  or h2==h3==d or w2==w3==d or w2==h3==d or h2==w3==d)) # 2
            else 'NO')

