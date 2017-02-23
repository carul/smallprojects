#include <iostream>
#include <string>

using namespace std;

int tab[3] = {1, 4, 12};

struct koordynaty{
	int x; int y;
};

struct struktura{
	int pierwszy = 1;
	int drugi;
	int trzeci;
	string nazwa;
	koordynaty koordy;
};

int main(){
	//tablice mozna od razu uzyc 
	cout << tab[0] << endl;
	//strukture najpierw trzeba stworzyc
	struktura obiekt;
	//typ obiektu, nazwa obiektu;
	obiekt.pierwszy = 1;
	obiekt.drugi = 4;
	obiekt.trzeci = 12;
	//tablica moze trzymac rozne elementy
	obiekt.nazwa = "jakas nazwa";
	cout << obiekt.pierwszy << endl;
	cout << obiekt.nazwa << endl;
	obiekt.koordy.x = 12;
	obiekt.koordy.y = 43;
	cout << obiekt.koordy.x << endl;
}
