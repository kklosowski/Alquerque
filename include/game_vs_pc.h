#ifndef GAME_VS_PC_H
#define GAME_VS_PC_H
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cmath>
#include <vector>
#include "board.h"
#include "pawns.h"
#include "game.h"

class game_vs_pc : public game
{
    public:
        game_vs_pc(int, bool = 0);
        ~game_vs_pc();

    int level;
    bool load;

    private:
    void computerMoveEasy();
    void computerMoveNormal();
    void computerMoveHard();

    protected:
    virtual void saveToFile();
    virtual void readFromFile();
    virtual void playerMove();
    virtual bool winCondition();
};

#endif // GAME_VS_PC_H
