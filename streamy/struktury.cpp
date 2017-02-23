#include <iostream>
#include <string>
using namespace std;

struct typ_dzialania{
	string plus = "dodawanie";
	string minus = "odejmowanie";
	string gwiazdka = "mnozenie";
	string slash = "dzielenie"; 
};

struct dzialanie{
	double liczba1;
	double liczba2;
	typ_dzialania typ;
	char rodzaj;
};

double corobimy(char znak, double l1, double l2){
	switch (znak){
		case '*':
			return l1*l2;
		case '+':
			return l1+l2;
		case '-':
			return l1-l2;
		case '/':
			return l1/l2;
	}
}

int main(){
	dzialanie tab[3];
	for(int i = 0; i < 3; i++){
		cout << "podaj liczbe 1: " << endl;
		cin >> tab[i].liczba1;
		cout << "podaj liczbe 2: " << endl;
		cin >> tab[i].liczba2;
		cout << "podaj rodzaj dzialania: " << endl;
		cin >> tab[i].rodzaj;
		cout << endl;
	}
	for(int i = 0; i < 3; i++){
		cout << endl;
		cout << "dzialanie " << i+1 << ": " << endl;
		cout << "wynik: " << corobimy(tab[i].rodzaj, tab[i].liczba1, tab[i].liczba2) << endl;
		switch(tab[i].rodzaj){
		case '*':
			cout << tab[i].typ.gwiazdka;
			break;
		case '+':
			cout << tab[i].typ.plus;
			break;
		case '-':
			cout << tab[i].typ.minus;
			break;
		case '/':
			cout << tab[i].typ.slash;
		}
		cout << endl;
	}
	return 0;
}
