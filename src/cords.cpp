#include "cords.h"

cords::cords(std::string cords)
{
    if(cords[0] >='A' && cords[0] <= 'E')
    {
        this->x=static_cast<int>(cords[0]-65);
    }
    else if(cords[0] >='a' && cords[0] <= 'e')
    {
        this->x=static_cast<int>(cords[0]-97);
    }

    if(cords[1]>='0'&&cords[1]<='4') this->y = static_cast<int>(cords[1]-48);


    else std::cout <<std::endl<< "Illegal coordinates.";

}

cords::cords(int x, int y): x(x), y(y)
{
}


cords::~cords()
{
}
