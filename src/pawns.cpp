#include "pawns.h"

pawns::pawns(int x, int y, char sign)
{
    this->x = x;
    this->y = y;
    this->sign = sign;
}

pawns::pawns(cords * cords, char sign)
{
	this->x = cords->x;
	this->y = cords->y;
	this->sign = sign;
}


pawns::~pawns()
{
    //dtor
}



