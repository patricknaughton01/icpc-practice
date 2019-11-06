#!/usr/bin/env python3 
#gravity

def fall(seq):
    ''' bottom is at higher indices.
    return column after fallen:
    'a's moved up to '#' or end 
    '''
    s = ''.join(seq)
    fallen = ''
    while s:
        i = s.find('#')
        if i < 0:
            i = len(s)
        n = s[:i].count('a')
        more = (i-n)*'.' + n*'a' + ('#' if i < len(s) else '')
        fallen += more
        s = s[len(more):]
    return fallen
              
r, c = input().split()
r = int(r)
# input and output in rows, but work on columns, flip via zip twice
for row in zip(*map(fall, zip(*[input() for i in range(r)]))):
    print(''.join(row))
