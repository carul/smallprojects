#include <iostream>
#include <ctime>

using namespace std;

int main(){
	srand (time(NULL)); //ustawia ziarno pseudolosowosci
	int tab[10];
	for(int i = 0; i < 10; i++){
		tab[i] = rand()%200 + 1;
	}
	for(int i = 0; i < 10; i++){
		cout << tab[i] << endl;
	}
	
	for(int i =0; i < 10; i++){
		for(int j= 0; j < 10-1; j++){
			if( tab[j] > tab[j+1]){
				int tymczasowa = tab[j+1];
				tab[j+1] = tab[j];
				tab[j] = tymczasowa;
			}
		}
	}
	cout << endl << endl;
	for(int i = 0; i < 10; i++){
		cout << tab[i] << endl;
	}
}
