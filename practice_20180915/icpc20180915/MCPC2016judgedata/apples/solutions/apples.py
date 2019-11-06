#!/usr/bin/env python3 
'''apples'''
import sys 

def aToEnd(s): # seq with no '#';'a's to end
    aCount = s.count('a')
    return '.'*(len(s) -aCount)+ 'a'*aCount

def fall(columnList): # start with list of column char, return final col str
    return '#'.join((map(aToEnd, ''.join(columnList).split('#'))))
              
input()
print('\n'.join(map(''.join, 
                    zip(*map(fall, zip(*sys.stdin.read().split()))))))
