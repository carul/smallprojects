#!/usr/bin/python3

import sys
import math

if len(sys.argv) <2:
    print ("Podaj plik zrodlowy i wynikowy jako argumenty")
    exit()

resultstring = "";
resinfile = "";

print("Sprawdzanie wyniku działania programu obliczającego trasę:")

with open(sys.argv[2], 'r') as outfile:
    resultstring = outfile.read().replace(',',' ')

with open(sys.argv[1], 'r') as infile:
    resinfile = infile.read().replace(',',' ')

resultstring = resultstring.split(' ')
resinfile = resinfile.split('\n')

score = 0;
time = 0;

for i in resinfile:
    onestring = i
    onestring = onestring.split(' ')
    for g in resultstring:
        if g == onestring[0]:
            score += int(onestring[4])

print("Uzyskany wynik: ")
print(score)

for i in range(0, len(resultstring)-1):
    tnext = resultstring[i+1]
    tnow = resultstring[i]
    posxnow, posynow, posxnext, posynext = 0,0,0,0
    staytime = 0
    for j in resinfile:
        g = j
        g = str(g)
        g = g.split(' ')
        if g[0] == tnow:
            posxnow = g[1]
            posynow = g[2]
        if g[0] == tnext:
            staytime = g[3]
            posxnext = g[1]
            posynext = g[2]
    ttime = math.sqrt(math.pow(int(posxnow)-int(posxnext), 2) + math.pow(int(posynow)-int(posynext), 2)) + float(staytime)
    print (ttime)
    time += ttime

print("Czas przejscia: ")
print(time)
