/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>

#define WIDTH 70
#define HEIGHT 20

class controll{
	public:
		void fill(char tab [][WIDTH]){

			for (int line = 0; line < HEIGHT; line++){
				for(int chr = 0; chr < WIDTH; chr++){
					if(line == 0){
						tab[line][chr] = '-';
						continue;
					}
					if(chr == 0){
						tab[line][chr] = '|';
						continue;
					}
					if(chr == WIDTH-1){
						tab[line][chr] = '|';
						continue;
					}
					if(line == HEIGHT-1){
						tab[line][chr] = '-';
						continue;
					}
					tab[line][chr] = ' ';
				}
			}
			tab[0][0] = '/';
			tab[0][WIDTH-1] = '\\';
			tab[HEIGHT-1][0] = '\\';
			tab[HEIGHT-1][WIDTH-1] = '/';
		}
		std::string tostring(char tab [][WIDTH], std::string a){
			for (int line = 0; line < HEIGHT; line++){
				for(int chr = 0; chr < WIDTH; chr++){
					a += tab[line][chr];
				}
				a += "\n";
			}
			return a;
		}
		void gotoxy(int x, int y){
			COORD c;
			c.X = x - 1;
			c.Y = y - 1;
			SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
		}
};


int main(int argc, char** argv) {
	int points = 0;
		srand( time( NULL ) );
		COORD pointpos;
		COORD nowpos[2];
		COORD posof[1000];
		for(int i = 0; i < 1000; i++){
			posof[i].X = 0;
			posof[i].Y = 0;
		}
		char tab[HEIGHT][WIDTH];
		std::string content;
		controll controll;
		int g = 0;
		short unsigned int dir = 4;
		int c = 0;
		int waitSecond = 2;
		bool finished = 0;


		/*  2
		    ^
		    |
		1<=====>3
		    |
		    v
		    4
		*/




		//tymczasowe

		int n = 0;

		pointpos.X = 0;
		pointpos.Y = 0;

		int x = 200;

		posof[0].X = 3;
		posof[0].Y = 6;
		posof[1].X = 3;
		posof[1].Y = 5;
		posof[2].X = 4;
		posof[2].Y = 5;
		posof[3].X = 5;
		posof[3].Y = 5;
		posof[4].X = 6;
		posof[4].Y = 5;
		posof[5].X = 7;
		posof[5].Y = 5;
		posof[6].X = 8;
		posof[6].Y = 5;
		int snakelength = 5;
		bool newpart;
		int selected = 1;

		bool start = false;

		HANDLE Ht;
		Ht = GetStdHandle( STD_OUTPUT_HANDLE );
	while(true){
        system("mode 71, 24");
		controll.gotoxy(1,1);
		SetConsoleTextAttribute( Ht, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "                                                                    " << std::endl;
		std::cout << "      ########    #     #    ######    ##  #    ######              " << std::endl;
		std::cout << "      #           ##    #    #    #    ## #     #                   " << std::endl;
		std::cout << "      ########    # #   #    ######    ###      ######              " << std::endl;
		std::cout << "             #    #  ## #    #    #    ## #     #                   " << std::endl;
		std::cout << "      ########    #    ##    #    #    ##  #    ######              " << std::endl;
		std::cout << "                               ULTRA                                " << std::endl;
		std::cout << "                                                                    " << std::endl;
		std::cout << "      copyright Karol Szustakowski                                  " << std::endl;
		std::cout << "                                                                    " << std::endl;
		std::cout << "                                                                    " << std::endl;
		std::cout << "                      ";if(selected == 1)std::cout << ">"; else std::cout << " "; std::cout <<"START"; if(selected == 1)std::cout << "<"; else std::cout << " "; std::cout << "                                       " << std::endl;
		std::cout << "                      ";if(selected == 2)std::cout << ">"; else std::cout << " "; std::cout <<"WYJDZ"; if(selected == 2)std::cout << "<"; else std::cout << " "; std::cout << "                                       " << std::endl;
		std::cout << "                                                                    " << std::endl;
		std::cout << "    Ostatnio uzyskane punkty: "; std::cout << points; std::cout << "   ";if(points > 99) std::cout << " ";std::cout<< "                                  " << std::endl;
		std::cout << "                                                                    " << std::endl;
		c = getch();
		if (c == 72 and selected !=1)
			selected--;
		if (c == 80 and selected !=2)
			selected++;
		if (c == 13 and selected == 1)
			start = true;
		if (c == 13 and selected == 2)
			break;
		SetConsoleTextAttribute( Ht, BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

		if(start == true)
			points = 0;
		if(start == true)
			while(true){
				g = 1;
				newpart = true;
				if(pointpos.X == posof[0].X and pointpos.Y == posof[0].Y){
					pointpos.X = 0;
					pointpos.Y = 0;
					points+=10;
					snakelength++;
					newpart = true;
					Beep(400, 100);
				}

				if(pointpos.X == 0 and pointpos.Y == 0){
					pointpos.X = ( rand() % (WIDTH - 10) ) + 5;
					pointpos.Y = ( rand() % HEIGHT - 3 ) + 3;
					if (pointpos.Y < 2)
						pointpos.Y = ( rand() % HEIGHT - 3 ) + 3;
					if (pointpos.Y > 18)
						pointpos.Y = ( rand() % HEIGHT - 3 ) + 3;
				}


				while(1){

					SetConsoleTextAttribute( Ht, BACKGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					if(posof[0].X == posof[g].X and posof[0].Y == posof[g].Y){
						std::cout << "GRA SKONCZONA! ZJADLES SIEBIE! " << std::endl;
						finished = 1;
						break;
					}
					g++;
					if(g >= 499){
						break;
					}
				}

				if (finished == 1)
					break;

				SetConsoleTextAttribute( Ht, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				if(posof[0].Y == HEIGHT-1)
					posof[0].Y = 1;
				if(posof[0].Y == 0)
					posof[0].Y = HEIGHT-2;
				if(posof[0].X == 0)
					posof[0].X = WIDTH-2;
				if(posof[0].X == WIDTH-1)
					posof[0].X = 1;
				g = 100;
				while(true){

					if ((posof[g-1].X == 0 and posof[g-1].Y == 0) || (posof[g].X == 0 and posof[g].Y == 0)){
						g--;
						continue;
					}
					posof[g].X = posof[g-1].X;
					posof[g].Y = posof[g-1].Y;
					g--;

					if (g == 0)
						break;
				}


				if(newpart == true){
					posof[snakelength+2].X = posof[snakelength+1].X;
					posof[snakelength+2].Y = posof[snakelength+1].Y;
				}

				g = 0;
				while (true){
					if (posof[g].X == 0 and posof[g].Y == 0)
						break;
					g++;
				}
				n = g;
				content.clear();
				controll.fill(tab);
				g = 0;
				while(true){
					if(posof[g].X == 0 && posof[g].Y == 0)
						break;
					tab[posof[g].Y][posof[g].X]= '#';
					g++;
				}
				if (dir == 1)
					tab[posof[0].Y][posof[0].X]= '<';
				if (dir == 2)
					tab[posof[0].Y][posof[0].X]= '^';
				if (dir == 3)
					tab[posof[0].Y][posof[0].X]= '>';
				if (dir == 4)
					tab[posof[0].Y][posof[0].X]= 'v';

				tab[pointpos.Y][pointpos.X]= 'O';

				content = controll.tostring(tab, content);
				controll.gotoxy(1,1);
				std::cout << content << std::endl;

				if (snakelength > 9)
					x = 150;
				if (snakelength > 19)
					x = 100;
				if (snakelength > 30)
					x = 50;
				waitSecond = 2;
				while(true){
		            if(kbhit()){
		                c=getch();
			            if(c == 75 && (nowpos[0].Y != nowpos[1].Y))
							dir = 1;
						if(c == 80 && (nowpos[0].X != nowpos[1].X))
							dir = 4;
						if(c == 72 && (nowpos[0].X != nowpos[1].X))
							dir = 2;
						if(c == 77 && (nowpos[0].Y != nowpos[1].Y))
							dir = 3;
		                continue;
		            }
		            Sleep(x);
		            --waitSecond;

		            if(waitSecond==0){
						if (dir == 1)
							posof[0].X--;
						if (dir == 2)
							posof[0].Y--;
						if (dir == 3)
							posof[0].X++;
						if (dir == 4)
							posof[0].Y++;
		                break;
		            }
		        }
		        nowpos[0] = posof[0];
				nowpos[1] = posof[1];
				SetConsoleTextAttribute( Ht, BACKGROUND_BLUE | BACKGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				std::cout << "Punkty: " << points << " pkt." << std::endl;
				std::cout << "Dlugosc weza: " << snakelength << " jednostek" << std::endl;
			}
		if (finished == true){
			dir = 2;
			getch();
			for(int i = 0; i < 1000; i++){
				posof[i].X = 0;
				posof[i].Y = 0;
			}
			posof[0].X = 3;
			posof[0].Y = 6;
			posof[1].X = 3;
			posof[1].Y = 7;
			posof[2].X = 3;
			posof[2].Y = 8;
			posof[3].X = 3;
			posof[3].Y = 9;
			posof[4].X = 3;
			posof[4].Y = 10;
			posof[5].X = 3;
			posof[5].Y = 11;
			posof[6].X = 3;
			posof[6].Y = 12;
			x = 200;
			snakelength = 5;
			start = false;
			n = 0;
			pointpos.X = 0;
			pointpos.Y = 0;
			finished = 0;
			system("cls");
		}
	}
	return 0;
}
