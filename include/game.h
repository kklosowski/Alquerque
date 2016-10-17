#ifndef GAME_H
#define GAME_H
#include "board.h"

class game
{
    public:
        game();
        ~game();

    board * board_ptr;

    protected:
    virtual void saveToFile() = 0;
    virtual void readFromFile() = 0;
    virtual void playerMove() = 0;
    virtual bool winCondition() = 0;
};

#endif // GAME_H
