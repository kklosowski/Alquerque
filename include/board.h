#ifndef BOARD_H
#define BOARD_H
#include "pawns.h"
#include "cords.h"
#include <cmath>
#include <windows.h>
#include <vector>
#include <iostream>
#include <cstring>

class board
{
    public:
        board();
        ~board();
        void draw();
        void setCursor(int, int);
        void setCursor(cords*);
        void createPawns();
        bool cordInBoard(int, int);
        bool takedownPermission(pawns*, cords*);
        std::vector<cords*> possibleTakdowns(cords *);
        std::vector<cords*> checkViableMoves(cords *);
        std::vector<cords*> candidatesForTakedown(cords*);
        void movePawn(cords *, cords*);
        int avg(int, int);
        pawns * pawns_board_ptr[5][5];
        bool isFree(cords*);
        int pawnsLeft(char);
        int canBeTakenDown(cords*, cords*);
        void multiplyTakedowns(cords * cord);

};

#endif // BOARD_H
