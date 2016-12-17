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
#include <conio.h>
#include <windows.h>>
#include <string>
using namespace std;
#define HORIBORDER 205
#define VERBORDER 186
#define UPRIGHT 187
#define UPLEFT 201
#define DOWNRIGHT 188
#define DOWNLEFT 200

void gotoxy(int x, int y)
{
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

void filltable(char tab[][24]){
    for (int i = 0; i < 80; i++)
        for (int j = 0; j < 25; j++)
            tab[i][j] = ' ';
    for (int i = 1; i < 78; i++)
        tab[i][0] = HORIBORDER;
    for (int i = 1; i < 78; i++)
        tab[i][23] = HORIBORDER;
    for (int i = 1; i < 24; i++)
        tab[0][i] = VERBORDER;
    for (int i = 0; i < 24; i++)
        tab[78][i] = VERBORDER;
    tab[0][0]  = UPLEFT;
    tab[78][0] = UPRIGHT;
    tab[0][23] = DOWNLEFT;
    tab[78][23]= DOWNRIGHT;
}

string tabtostring(char tab[][24]){
    string a;
    a = "";
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 79; j++)
            a+=tab[j][i];
        a+="\n";
    }
    return a;
}

class ptaszysko{
    int posy;
    bool dead;
    short int movementphase;
    public:
        void inicjalizuj(){
            dead = false;
            posy = 13;
            movementphase = 1;
        }
        int pozycja(){
            return posy;
        }
        int phase(){
            return movementphase;
        }
        void zabij(){
            dead = true;
        }
        void skocz(){
            movementphase=1;
        }
        bool isdead(){
            return dead;
        }
        void rusz(){
            switch(movementphase){
            case 1:
                posy--;
                posy--;
                movementphase++;
                break;
            case 2:
                posy--;
                movementphase++;
                break;
            case 3:
                movementphase++;
                break;
            case 4:
                posy--;
                movementphase++;
                break;
            case 5:
                posy--;
                movementphase++;
                break;
            case 6:
                movementphase++;
                break;
            case 7:
                movementphase++;
                break;
            default:
                posy++;

            }
        }
};

class slupek{
    int peakbot;
    int peaktop;
    int posx;
    public:
        void init(){
            peakbot = 15;
            peaktop = 5;
        }
        int gettop(){
            return peaktop;
        }
        int getbot(){
            return peakbot;
        }
        void setpos(int pos){
            posx = pos;
        }
        int getpos(){
            return posx;
        }
        void forw(){
            posx--;
        }
        void setdimensions(){
            int a = (rand()%7)+14;
            peakbot = a;
            peaktop = a-10;
        }
};

int main(){
    srand(time(NULL));
    char towrite[79][24];
    ptaszysko ptaszor;
    slupek s[4];
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("mode 80,25");
    int score;
    while("start programu"){
        score = 0;
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        ptaszor.inicjalizuj();
        filltable(towrite);
        s[0].setpos(70);
        s[1].setpos(90);
        s[2].setpos(110);
        s[3].setpos(130);
        for (int i =0; i< 4; i++){
            s[i].init();
            s[i].setdimensions();
        }
        while("glowna petla"){
            gotoxy(0,0);
            cout << tabtostring(towrite);
            filltable(towrite);
            if(score < 5){
                towrite[25][ptaszor.pozycja()] = ' ';
                towrite[24][ptaszor.pozycja()] = ':';
                towrite[26][ptaszor.pozycja()] = '(';
            }
            else if(score < 10){
                towrite[25][ptaszor.pozycja()] = ' ';
                towrite[24][ptaszor.pozycja()] = ':';
                towrite[26][ptaszor.pozycja()] = '/';
            }
            else if(score < 15){
                towrite[25][ptaszor.pozycja()] = ' ';
                towrite[24][ptaszor.pozycja()] = ':';
                towrite[26][ptaszor.pozycja()] = '|';
            }
            else if(score < 20){
                towrite[25][ptaszor.pozycja()] = ' ';
                towrite[24][ptaszor.pozycja()] = ':';
                towrite[26][ptaszor.pozycja()] = ')';
            }
            else if(score < 25){
                towrite[25][ptaszor.pozycja()] = '-';
                towrite[24][ptaszor.pozycja()] = ':';
                towrite[26][ptaszor.pozycja()] = 'D';
            }
            else{
                towrite[25][ptaszor.pozycja()] = ' ';
                towrite[24][ptaszor.pozycja()] = 'x';
                towrite[26][ptaszor.pozycja()] = 'D';
            }
            if(ptaszor.phase() < 8){
                towrite[25][ptaszor.pozycja()+1] = '/';
                towrite[25][ptaszor.pozycja()-1] = '\\';
            }
            for(int i = 0; i < 4; i++){
                if(s[i].getpos() == 24){
                    score++;
                }
                if(s[i].getpos() < 78){
                    towrite[s[i].getpos()][s[i].gettop()] = 'v';
                    for(int j = 1; j < s[i].gettop(); j++){
                        towrite[s[i].getpos()][j] = '|';
                        if ((s[i].getpos() == 24 && ptaszor.pozycja() < s[i].gettop()+1) || (s[i].getpos() == 23 && ptaszor.pozycja() < s[i].gettop()+2) || (s[i].getpos() == 25 && ptaszor.pozycja() < s[i].gettop()+1))
                            ptaszor.zabij();
                    }
                }
                if(s[i].getpos() < 78){
                    towrite[s[i].getpos()][s[i].getbot()] = '^';
                    for(int j = 22; j > s[i].getbot(); j--){
                        towrite[s[i].getpos()][j] = '|';
                       if ((s[i].getpos() == 24 && ptaszor.pozycja() > s[i].getbot()-1) || (s[i].getpos() == 23 && ptaszor.pozycja() > s[i].getbot()-2) || (s[i].getpos() == 25 && ptaszor.pozycja() > s[i].getbot()-1))
                            ptaszor.zabij();
                    }
                }
            }
            for (int i =0; i< 4; i++){
                s[i].forw();
                if(s[i].getpos() < 2){
                    s[i].setpos(80);
                    s[i].setdimensions();
                }
            }
            ptaszor.rusz();
            if(kbhit() && getch()){
                ptaszor.skocz();
            }
            if(ptaszor.pozycja() == 0 || ptaszor.pozycja() == 24)
                ptaszor.zabij();
            if(ptaszor.isdead())
                break;
            Sleep(100);

        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        gotoxy(20, 13);
        cout << "You are dead, score: " << score << endl;
        getch();
    }
    return 0;
}
