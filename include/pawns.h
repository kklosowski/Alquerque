#ifndef PAWNS_H
#define PAWNS_H
#include "cords.h"
#include <iostream>


class pawns
{
    public:
        pawns();
        pawns(int, int, char);
        pawns(cords*, char);
        ~pawns();

    char sign;
    int x;
    int y;


    protected:
    private:
};

#endif // PAWNS_H
