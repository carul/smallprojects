#!/usr/bin/python
# -*- coding: utf-8 -*-
#Karol Szustakowski 2016
import sys
import os
import Image

if len(sys.argv) < 2:
	print("No file specified. Please specify a file.")
	exit()
else:
	print("Searching for selected file: " + sys.argv[1])
	path = "./"
	path += sys.argv[1]
	if os.path.isfile(path) == 0:
		print("File not found. Please check input.")
		exit()
	else:
		print("Found specified file.")

if len(sys.argv) > 2:
	print("Output will be saved to: " + sys.argv[2])
else:
	temp = sys.argv[1];
	temp = temp.replace(temp[sys.argv[1].index('.'):len(temp)], ".txt")
	print("No output specified. Will be saved to default (" + temp + ")")

probe = 5

if len(sys.argv) > 3:
	for i in sys.argv[3]:
		if i in "0123456789":
			continue
		else:
			print("Please provide an integer as probe size")
			exit()
	print("Size of probe will set to: " + sys.argv[3])
	probe = int(sys.argv[3])

file = Image.open(sys.argv[1])
print("File size is: " + str(file.size[0]) + "x" + str(file.size[1]))
print("Probing...")
sizx = file.size[0]/probe
sizy = file.size[1]/probe
print("Output ASCII size: " + str(sizx) + "x" + str(sizy))

file = file.rotate(90)

parse = file.load()
if len(sys.argv) > 2:
	towrite = open(str(sys.argv[2]), 'w')
else:
	temp = sys.argv[1];
	temp = temp.replace(temp[sys.argv[1].index('.'):len(temp)], ".txt")
	towrite = open(str(temp), 'w')

for i in range(0, sizy, probe):
	for j in range(0, sizx, probe):
		r, g, b = file.getpixel((i*probe, j*probe))
		lightdensity = 0.2126*r + 0.7152*g + 0.0722*b
		if lightdensity < 25:
			towrite.write(" ")
		if lightdensity >= 25 and lightdensity < 50:
			towrite.write(".")
		if lightdensity >= 50 and lightdensity < 75:
			towrite.write(",")
		if lightdensity >= 75 and lightdensity < 100:
			towrite.write(":")
		if lightdensity >= 100 and lightdensity < 125:
			towrite.write(";")
		if lightdensity >= 100 and lightdensity < 125:
			towrite.write("+")
		if lightdensity >= 125 and lightdensity < 150:
			towrite.write("=")
		if lightdensity >= 150 and lightdensity < 175:
			towrite.write("H")
		if lightdensity >= 175 and lightdensity < 200:
			towrite.write("W")
		if lightdensity >= 200 and lightdensity < 225:
			towrite.write("@")
		if lightdensity >= 225:
			towrite.write("▓")
	towrite.write("\n")	

#revert
		#if lightdensity < 25:
		#	towrite.write("▓")
		#if lightdensity >= 25 and lightdensity < 50:
		#	towrite.write("@")
		#if lightdensity >= 50 and lightdensity < 75:
		#	towrite.write("W")
		#if lightdensity >= 75 and lightdensity < 100:
		#	towrite.write("H")
		#if lightdensity >= 100 and lightdensity < 125:
		#	towrite.write("=")
		#if lightdensity >= 100 and lightdensity < 125:
		#	towrite.write("+")
		#if lightdensity >= 125 and lightdensity < 150:
		#	towrite.write(";")
		#if lightdensity >= 150 and lightdensity < 175:
		#	towrite.write(":")
		#if lightdensity >= 175 and lightdensity < 200:
		#	towrite.write(",")
		#if lightdensity >= 200 and lightdensity < 225:
		#	towrite.write(".")
		#if lightdensity >= 225:
		#	towrite.write(" ")