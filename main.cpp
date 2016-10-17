#include <iostream>
#include <windows.h>
#include <ctime>
#include <cctype>
#include "board.h"
#include "pawns.h"
#include "pawns.h"
#include "game_vs_player.h"
#include "game_vs_pc.h"
using namespace std;

void readGameType(){

    std::ifstream fileIn;
    fileIn.open("save.txt");
    int tmp1,tmp2;
    fileIn >> tmp1;
    fileIn >> tmp2;
    game * gm;
    if (tmp1 == 0) gm = new game_vs_player(true);
    if (tmp1 == 1) gm = new game_vs_pc(tmp2, true);

}

int menu(){
    system("cls");
    cout << "1. New Game" << endl;
    cout << "2. Load Unfinished Game" << endl;
    cout << "3. Rules" << endl;
    cout << "4. Quit" << endl;
    char chTmp[20];
    int tmp;
    cin >> chTmp;
    if(isdigit(chTmp[0]) && chTmp[1]==NULL) tmp = static_cast<int>(*chTmp-48);
    else return 0;
    switch(tmp){

        case 1:
                system("cls");
                cout << "1. Game vs. Computer" << endl;
                cout << "2. Game vs. Player" << endl;
                cin >> tmp;
                game * gm;

                    if(tmp == 1){
                        system("cls");
                        cout << "1. Easy" << endl;
                        cout << "2. Normal" << endl;
                        cout << "3. Hard" << endl;
                        cin >> tmp;
                        gm = new game_vs_pc(tmp-1);
                        break;
                    }
                    else if(tmp == 2){
                        system("cls");
                        gm = new game_vs_player;
                        break;
                    }
                    else break;

        case 2:
                readGameType();
                break;
        case 3:

                system("cls");

                cout << "A piece can move from its point to any empty adjacent point that is connected by a line." << endl
                << "A piece can jump over an opposing piece and remove it from the game," << endl
                << "if that opposing piece is adjacent and the point beyond it is empty." << endl
                << "Multiple capturing jumps are permitted, and indeed compulsory if possible." << endl
                << "If a capture is possible it must be made, or else the piece is removed (or huffed)." << endl
                << "The goal of the game is to eliminate the opponent's pieces." << endl;
                system("pause");
            break;

        case 4:
            break;

    }
    return tmp;
}




int main()
{
    srand(time(NULL));
    int choice;
    do{
    choice = menu();
    }while(choice!=4);

    return 0;

}








