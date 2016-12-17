#!/usr/bin/python
# -*- coding: utf-8 -*-
#Karol Szustakowski 2016

import random

zajakniecia = ["eee", "yy", "noo", "tutaj", "nie wiem czy ale chyba", "ej Rząsa"]
poczatki = ["No Rząsy nie ma, wiec", "Dzisiaj zrobimy sobie", "Typrowicz co tam robisz teraz? Pewnie", "Co my to robiliśmy ostatnio? Zaraz nam powiesz, tylko", "Proszę wejść na elearning, bo ostatnio"]
rdzen = ["zacznijmy od plików bat,", "zamknijcie już okno i teraz hmm,", "wy myślicie, że ja tego nie widzę, chyba nie,", "jak skończymy z tym to zrobimy sprawdzianik,", "co dalej to zaraz powiem,", "w zeszycie oczywiście to zapisujecie,", "tutaj patrz na tablicę a nie w Facebooka,", "noo, trochę żeście się nie pouczyli, ale"]
stwierdzenia = ["można", "pewnie", "ale mi wieje po plecach", "nadążacie za tym co robię? to,", "nie wiem, czy", "to już powinniście umieć, że", "zaraz sobie zapiszemy jak", "otwórzcie sobie pdfy i", "zaraz się dowiemy"]
zakonczenia = ["więc skończcie już gadanie", "no, mam nadzieję, że to jest zrozumiałe", "komputery możecie już wyłączyc", "dobra, jeszcze 30 sekund i możecie isć", "można wyjśc na przerwę"]

out = ""
lastrand = 0

out += poczatki[random.randint(0,len(poczatki)-1)] + " "

for _ in range(0, random.randint(1, 10)):
	i = random.randint(1, 2)
	if i == 1:
		out += zajakniecia[random.randint(0,len(zajakniecia)-1)] + " "
	i = random.randint(1, 4)
	j = random.randint(0, len(rdzen)-1)
	while j == lastrand:
		j = random.randint(0, len(rdzen)-1)
	if i == 1:
		out += stwierdzenia[random.randint(0, len(stwierdzenia)-1)] + " " + rdzen[j] + " "
	if i == 2:
		out += rdzen[j] + " " + stwierdzenia[random.randint(0, len(stwierdzenia)-1)] + " "
	if i == 3:
		out += rdzen[j] + " "
	if i == 4:
		out += stwierdzenia[random.randint(0, len(stwierdzenia)-1)] + " " + rdzen[j] + " " + stwierdzenia[random.randint(0, len(stwierdzenia)-1)] + " "
	lastrand = j

out += zakonczenia[random.randint(0, len(zakonczenia)-1)] + "."

print(out)