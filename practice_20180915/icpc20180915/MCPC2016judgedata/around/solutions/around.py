#!/usr/bin/env python3 
'''Around - round text display  Andy Harrington'''

SEP= '_'
EMPTY = '/'

def do(wait, inLines):
    '''inLines is input lines after first'''
    inLines = list(map(str.split, inLines))
    inLines.reverse() # so easy pop
    words = []  # will be list of all words 
    beats = []  # will be full list of beats/word
    lineTot = [] # will be cumulative times at end of each line
    tot = 0
    while inLines:
        words += inLines.pop()
        lineBeats = list(map(int, inLines.pop()))
        tot += sum(lineBeats)
        lineTot.append(tot)
        beats += lineBeats
    tup = [] # will contain list of (start time, voice 0/1, word) 
    time = 0
    for b, w in zip(beats, words):
        tup.append((time, 0, w+SEP))
        tup.append((time+wait, 1, w+SEP))
        time += b
    tup.sort()
    tup.reverse()     # for easy pop
    lineTot.reverse()
    timeLim = 0 # for last line at top of loop, then current line
    while lineTot:
        col = 0 
        lastTime =  timeLim 
        timeLim = lineTot.pop()
        vStr = ['', ''] # parts of two voices on current line so far
        while tup and tup[-1][0] < timeLim: # more for this line
            t, vn, w = tup.pop()
            col = max(len(vStr[vn]), col + t - lastTime) #rule 3
            if tup and tup[-1][0] == t:  # rule 2
               col = max(col, len(vStr[1])) 
            vStr[vn] += (col-len(vStr[vn]))*SEP + w  # w starts at col
            lastTime = t # record data for later rule 3
        for voice in vStr:
            print(voice.rstrip(SEP) if voice else EMPTY) 

def hotCross(): # simple test
    hc ='''Hot cross buns! = Hot cross buns! =
    2 2 2 2 2 2 2 2
    One a pen- ny, Two a pen- ny, Hot cross buns!
    1 1 1 1 1 1 1 1 2 2 2 2'''
    do(8, hc.splitlines())

def fromInput():
    L, wait = map( int, input().split())
    do (wait, [input() for i in range(2*L)])

##hotCross()
fromInput()
