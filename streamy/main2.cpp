#include <iostream>

using namespace std;

int main(){
	//tablica
	int tab[5] = {1, 3, 5, 7, 10};
	//to samo tylko ze inaczej zapisane
	int a = 1; //tab[0] -- wskaznika nie zwiekszamy
	int b = 3; //tab[1] -- wskaznika dodajemy 1
	int c = 5; //tab[2] -- +2 ...
	int d = 7;
	int e = 10;
	int *pocz_tabl = &a;
	//jak wypisac takie cos?
	for(int i = 1; i < 6; i++){
		cout << *(pocz_tabl + i) << endl;
	}


	for(int i = 0; i < 5; i++){
//		cout << tab[i] << endl;
		//w taki sposob wypisywalismy tablice
	}

}
