#ifndef CORDS_H
#define CORDS_H
#include <iostream>

class cords
{
    public:
        cords(std::string);
        cords(int, int);
        ~cords();

        int x;
        int y;
    protected:
    private:
};

#endif // CORDS_H
