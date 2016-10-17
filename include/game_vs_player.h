#ifndef GAME_VS_PLAYER_H
#define GAME_VS_PLAYER_H
#include <iostream>
#include <fstream>
#include <windows.h>
#include <cmath>
#include "board.h"
#include "pawns.h"
#include "game.h"

class game_vs_player : public game
{
    public:
        game_vs_player(bool=0);
        ~game_vs_player();

    bool load;

    protected:
    virtual void saveToFile();
    virtual void playerMove();
    virtual bool winCondition();
    virtual void readFromFile();
    private:
};

#endif // GAME_VS_PLAYER_H
