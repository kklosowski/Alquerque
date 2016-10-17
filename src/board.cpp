#include "board.h"


board::board()
{
}



board::~board()
{
        delete pawns_board_ptr;
}

void board::createPawns(){
//FUNCTION FILLING THE BOARD WITH PAWN OBJECTS
         for(int j=0,tmp=0; j<5; j++){
            for(int i=0; i<5; i++,tmp++){
                    if(tmp<12)      this->pawns_board_ptr[i][j]= new pawns(i,j,'*');
                    else if(tmp>12) this->pawns_board_ptr[i][j]= new pawns(i,j,'o');
                    else this->pawns_board_ptr[i][j]= NULL;

            }
    }
  }

void board::setCursor( int X, int Y ){
    //FUNCTION SETTING THE CONSOLE CURSOR IN GIVEN POSITION
	COORD position;
	position.X = X;
	position.Y = Y;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),position);
}

void board::setCursor(cords * cords){

    COORD position;
	position.X = cords->x*2+5;
	position.Y = cords->y*2+4;
	SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),position);
}

void board::draw(){
//FUNCTION DRAWING THE BOARD
system("cls");

    for (int i=0; i<6;i++){
            for(int j=0; j<5; j++){

            setCursor(2*i+3, 2*j+2);

             if (!i){
            setCursor(2*i+3,2*j+4);
            std::cout <<  char('0'+j);
            }

            if(!j && !(!i && !j)){
            std::cout << char('A'+i-1);
            }

        }
    }


         for(int i=0; i<5; i++){
            for(int j=0; j<5; j++){
                    if(pawns_board_ptr[i][j]==NULL) continue;
                    setCursor(pawns_board_ptr[i][j]->x*2+5,  pawns_board_ptr[i][j]->y*2+4);
                    std::cout << pawns_board_ptr[i][j]->sign;
                }
            }


    for (int i=0; i<4;i++){
            for(int j=0; j<5; j++){

            setCursor(i*2+6, 2*j+4);
            std::cout << '-';
        }
    }

    for (int i=0; i<5;i++){
            for(int j=0; j<4; j++){

            setCursor(i*2+5, 2*j+5);
            std::cout << '|';
        }
    }

    for (int i=0; i<2;i++){
            for(int j=0; j<2; j++){

            setCursor(i*4+6, 4*j+5);
            std::cout << '\\';

            setCursor(i*4+8, 4*j+7);
            std::cout << '\\';

            setCursor(i*4+8, 4*j+5);
            std::cout << '/';

            setCursor(i*4+6, 4*j+7);
            std::cout << '/';
        }
    }


    setCursor(0,20);

}

int  board::avg(int a, int b){
    return (a+b)/2;
}

void board::movePawn(cords * start_cords, cords * destination_cords ){

//---CLEANING THE CONSOLE ALERT-----
    setCursor(20,10);
    std::cout << "\t\t\t\t\t\t";
//--------------------------------------
    setCursor(start_cords);
    std::cout << ' ';

    this->pawns_board_ptr[start_cords->x][start_cords->y]->x = destination_cords->x;
    this->pawns_board_ptr[start_cords->x][start_cords->y]->y = destination_cords->y;



    int avgx,avgy;
    avgx = avg(start_cords->x, destination_cords->x);
    avgy = avg(start_cords->y, destination_cords->y);

    if(((destination_cords->x > avgx && avgx > start_cords->x) || (start_cords->x > avgx && avgx > destination_cords->x))|| ((destination_cords->y > avgy && avgy > start_cords->y )||(start_cords->y > avgy && avgy > destination_cords->y)))
    {
        delete this->pawns_board_ptr[avgx][avgy];
        this->pawns_board_ptr[avgx][avgy] = NULL;
        setCursor(new cords(avgx, avgy));
        std:: cout << " ";
    }

    setCursor(destination_cords);
    std::cout << pawns_board_ptr[start_cords->x][start_cords->y]->sign;


    std::swap(pawns_board_ptr[start_cords->x][start_cords->y], pawns_board_ptr[destination_cords->x][destination_cords->y]);


    setCursor(0,20);
}

std::vector<cords*> board::checkViableMoves(cords * tmp){
//FUNCTION CHECKING ALL THE POSSIBLE MOVES OF A GIVEN PAWN

    int x = tmp->x;
    int y = tmp->y;
    std::vector<cords*> viable;
    std::vector<cords*> permitted;
    std::vector<cords*> takedowns;


        if ((x>0 && x<4)&&(y>0 && y<4))
        {

            if ((x%2 && y%2)||(x==2 && y==2))
            {
                for(int i=-1;i<2;i++){
                    for(int j=-1; j<2; j++){
                        if(!i && !j) continue;
                        if(cordInBoard(x+i,y+j)) permitted.push_back(new cords(x+i, y+j));

                        if(cordInBoard(x+i*2,y+j*2)) takedowns.push_back(new cords(x+i*2, y+j*2));
                    }
                }
            }

            if((x==2&&(y==1||y==3))||(y==2&&(x==1||x==3)))
            {
                    for(int i=-1;i<2;i+=2){
                        if(cordInBoard(x+i,y)) permitted.push_back(new cords(x+i,y));
                        if(cordInBoard(x+i*2,y)) takedowns.push_back(new cords(x+i*2,y));
                    }
                    for(int j=-1; j<2; j+=2){
                        if(cordInBoard(x,y+j)) permitted.push_back(new cords(x, y+j));
                        if(cordInBoard(x,y+j*2))takedowns.push_back(new cords(x,y+j*2));
                    }
            }
        }

        else {
                for(int i=-1;i<2;i++)
                {
                    for(int j=-1; j<2; j++)
                    {
                        if(!i && !j) continue;

                        if((y%2 && (x==0 || x==4)) ||  (x%2 && (y==0 || y==4))) {
                            if(cordInBoard(x+i,y+j)) permitted.push_back(new cords(x+i, y));
                            if(cordInBoard(x+i*2,y)) takedowns.push_back(new cords(x+i*2,y));

                            if(cordInBoard(x+i,y+j)) permitted.push_back(new cords(x, y+j));
                            if(cordInBoard(x,y+j*2)) takedowns.push_back(new cords(x,y+j*2));
                            }
                        else{
                            if(cordInBoard(x+i,y+j)) permitted.push_back(new cords(x+i, y+j));
                            if(cordInBoard(x+i*2,y+j*2)) takedowns.push_back(new cords(x+i*2, y+j*2));
                            }
                    }
                }
            }



        for(std::vector<cords*>::iterator it = takedowns.begin(); it!=takedowns.end() ;it++ )
        {
            if(takedownPermission(pawns_board_ptr[x][y], (*it) ))
            {
                viable.push_back(*it);
            }
        }


        for(std::vector<cords*>::iterator it = permitted.begin(); it!=permitted.end() ;it++ )
        {
            if(isFree(*it))
            {
                viable.push_back(*it);
            }

        }




    return viable;
}

std::vector<cords*> board::possibleTakdowns(cords *tmp){
//FUNCTION CHECKING POSSIBLE TAKEDOWNS OF A GIVEN PAWN
    int x = tmp->x;
    int y = tmp->y;
    std::vector<cords*> takedowns;
    std::vector<cords*> viable;


        if ((x>0 && x<4)&&(y>0 && y<4))
        {

            if ((x%2 && y%2)||(x==2 && y==2))
            {
                for(int i=-1;i<2;i++){
                    for(int j=-1; j<2; j++){
                        if(!i && !j) continue;
                        if(cordInBoard(x+i*2,y+j*2)) takedowns.push_back(new cords(x+i*2, y+j*2));
                    }
                }
            }

            if((x==2&&(y==1||y==3))||(y==2&&(x==1||x==3)))
            {
                    for(int i=-1;i<2;i+=2){
                        if(cordInBoard(x+i*2,y)) takedowns.push_back(new cords(x+i*2,y));
                    }
                    for(int j=-1; j<2; j+=2){
                        if(cordInBoard(x,y+j*2))takedowns.push_back(new cords(x,y+j*2));
                    }
            }
        }

        else {
                for(int i=-1;i<2;i++)
                {
                    for(int j=-1; j<2; j++)
                    {
                        if(!i && !j) continue;

                        if((y%2 && (x==0 || x==4)) ||  (x%2 && (y==0 || y==4))) {
                            if(cordInBoard(x+i*2,y)) takedowns.push_back(new cords(x+i*2,y));

                            if(cordInBoard(x,y+j*2)) takedowns.push_back(new cords(x,y+j*2));
                            }
                        else{
                            if(cordInBoard(x+i*2,y+j*2)) takedowns.push_back(new cords(x+i*2, y+j*2));
                            }
                    }
                }
            }



        for(std::vector<cords*>::iterator it = takedowns.begin(); it!=takedowns.end() ;it++ )
        {
            if(takedownPermission(pawns_board_ptr[x][y], (*it) ))
            {
                viable.push_back(*it);
            }
        }


    return viable;
}

std::vector<cords*> board::candidatesForTakedown(cords * tmp){
//FUNCTION CHECKING POSSIBILITIES OF A GIVEN PAWN BEING TAKEN BY DIFFERENT PAWNS
    int x = tmp->x;
    int y = tmp->y;
    std::vector<cords*> tmpPermitted;
    std::vector<cords*> permitted;



        if ((x>0 && x<4)&&(y>0 && y<4))
        {

            if ((x%2 && y%2)||(x==2 && y==2))
            {
                for(int i=-1;i<2;i++){
                    for(int j=-1; j<2; j++){
                        if(!i && !j) continue;
                        if(cordInBoard(x+i,y+j)) tmpPermitted.push_back(new cords(x+i, y+j));
                    }
                }
            }

            if((x==2&&(y==1||y==3))||(y==2&&(x==1||x==3)))
            {
                    for(int i=-1;i<2;i+=2){
                        if(cordInBoard(x+i,y)) tmpPermitted.push_back(new cords(x+i,y));
                    }
                    for(int j=-1; j<2; j+=2){
                        if(cordInBoard(x,y+j)) tmpPermitted.push_back(new cords(x, y+j));
                    }
            }
        }

        else {
                for(int i=-1;i<2;i++)
                {
                    for(int j=-1; j<2; j++)
                    {
                        if(!i && !j) continue;

                        if((y%2 && (x==0 || x==4)) ||  (x%2 && (y==0 || y==4))) {
                            if(cordInBoard(x+i,y+j)) tmpPermitted.push_back(new cords(x+i, y));

                            if(cordInBoard(x+i,y+j)) tmpPermitted.push_back(new cords(x, y+j));
                            }
                        else{
                            if(cordInBoard(x+i,y+j)) tmpPermitted.push_back(new cords(x+i, y+j));
                            }
                    }
                }
            }
            for(std::vector<cords*>::iterator it = tmpPermitted.begin(); it!=tmpPermitted.end() ;it++ )
            {
                    if(!isFree((*it))) permitted.push_back((*it));
            }
        return permitted;
}

bool board::isFree(cords * cords){
//FUNCTION CHECKING IF A GIVEN PLACE ON THE BOARD IS OCCUPIED
return pawns_board_ptr[cords->x][cords->y]==NULL;
}

bool board::cordInBoard(int x, int y){
//FUNCTION CHECKING IF GIVEN COORDINATES ARE PLACED ON THE BOARD
    if((x<=4 && x>=0)&&(y<=4 && y>=0)) return true;
    else return false;
}

bool board::takedownPermission(pawns* pawn1, cords * cords){
//FUNCTION CHECKING IF THE TAKEDOWN ISN'T MADE ON ONE OF YOUR OWN PAWNS
int tmpx, tmpy;
if(cords->x > pawn1->x) tmpx = avg(pawn1->x,cords->x);
else tmpx = ceil((cords->x + pawn1->x)/2);

if(cords->y > pawn1->y) tmpy = avg(pawn1->y,cords->y);
else tmpy = ceil((cords->y + pawn1->y)/2);


if(pawns_board_ptr[tmpx][tmpy]!=NULL && isFree(cords))
{
    if(pawn1->x == tmpx && pawn1->y == tmpy) return false;
    else if (pawn1->sign == pawns_board_ptr[tmpx][tmpy]->sign) return false;
    else return true;
}
return false;
}

int  board::pawnsLeft(char sign){
//FUNCTION COUNTING PAWNS OF A GIVEN COLOR (USED FOR WIN CONDITION)
  int PawnsLeft = 0;
    for(int i=0; i<5;i++)
    {
        for(int j=0; j<5; j++)
        {
            if(pawns_board_ptr[i][j]!=NULL)
            {
                if(pawns_board_ptr[i][j]->sign==sign)
                PawnsLeft++;
            }
        }
    }

    return PawnsLeft;
}

int board::canBeTakenDown(cords * cords1, cords * startcords){
//FUNCTION CHECKING THE NUMBER OF TAKEDOWN THREATS FOR A GIVEN MOVE
    int tmpx,tmpy;
    pawns * pawns_tab [5][5];

    for(int j=0; j<5; j++){
            for(int i=0; i<5; i++){
                    if(pawns_board_ptr[i][j]!=NULL)
                    {
                        pawns_tab[i][j]= new pawns(pawns_board_ptr[i][j]->x,pawns_board_ptr[i][j]->y,pawns_board_ptr[i][j]->sign);
                    }
                    else pawns_tab[i][j]= NULL;
            }
    }


    char sign = '*';
    std::vector<cords*> permitted = candidatesForTakedown(cords1);
    int CanBeTakenDown = 0;

     for(std::vector<cords*>::iterator it = permitted.begin(); it!=permitted.end() ;it++ )
        {
            for(int i = -1; i<2 ; i++){
                for (int j = -2; j<2 ; j++){

                    if((*it)->x == cords1->x+i && (*it)->y == cords1->y+j )
                        if(pawns_tab[cords1->x+i][cords1->y+j]->sign != '*')
                            if(isFree(new cords(cords1->x-i,cords1->y-j)) || (cords1->x-i==startcords->x && cords1->y-j ==startcords->y) ) CanBeTakenDown++;
                }

            }



        }
    return CanBeTakenDown;
}

void board::multiplyTakedowns(cords * cord){
//FUNCTION CHECKING IF MULTIPLE TAKEDOWN ARE PREMITED
    std::vector<cords*> ViableTakedowns;


            ViableTakedowns = possibleTakdowns(new cords(cord->x,cord->y));

            for(std::vector<cords*>::iterator it2 = ViableTakedowns.begin(); it2!=ViableTakedowns.end() ;it2++ )
            {
                if(takedownPermission((pawns_board_ptr[cord->x][cord->y]),(*it2)))
                {
                    movePawn(new cords(cord->x,cord->y),(*it2));
                    this->multiplyTakedowns((*it2));
                    ViableTakedowns.clear();
                    return;
                }
            }


        return;

}
