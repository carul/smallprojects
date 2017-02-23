#include <iostream>

using namespace std;

int main(){
	int zmienna; //zmienna liczbowa
	zmienna = 5;
	int *wsk_na_zmienna; //wskaznik
	wsk_na_zmienna = &zmienna;
	// wskaznik bez gwiazdki - oznacza adres
	// wskaznik z gwiazdka - oznacza zmienna pod adresem
	// & <-- ten znaczek- pobranie adresu zmiennej
	//
	// 1. tworzenie zmiennej
	// 2. tworzenie wskaznika
	// 3. do wskaznika ladujemy adres zmiennej
	
	cout << *wsk_na_zmienna << endl;
	cout << wsk_na_zmienna << endl;
	cout << &zmienna << endl;

	// 1. wypisanie zmiennej spod adresu wskaznika
	// 2. wypisanie adresu we wskazniku
	// 3. "wyciagniecie" adresu ze zmiennej

}
