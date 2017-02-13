#!/usr/bin/python3
import binascii
import sys

if len(sys.argv) == 1:
		print("No arguments specified")
		exit()

filename = sys.argv[1]

try:
		content = open(filename, 'rb')
except IOError:
		print("File not found")
		exit()

content = content.read()

hexstring = str(binascii.hexlify(content).upper())
hexarray = []

def ciccn(hdig):
	return{
			'C2': 5,
			'C1': 6,
			'C0': 7,
			'CF': 8,
			'CE': 9,
			'CD': 10,
			'CC': 11,
			'CB': 12,
			'CA': 13,
			'C9': 14,
			'C8': 15,
		}.get(hdig, 0)

def checkzeroes(arr):
	for j in range(0, len(arr)):
		if j == "00":
			return False

	return True

for i in range(0,len(hexstring)-1, 2):
	s = hexstring[i] + hexstring[i+1]
	hexarray.append(s)

for i in range(0,len(hexarray)):
	g= ciccn(hexarray[i])
	if g:
		if len(hexarray) > i+g+1 and checkzeroes(hexarray[i:i+g]) and hexarray[i+g+1] == "00":
			print("Prawidlowe haslo na pozycji: " + str(i*2) + " o dlugosci " + str(g))
			print("  Hex zakodowanego hasla: " + ' '.join(hexarray[i+1:i+g+1]) + "\n")

