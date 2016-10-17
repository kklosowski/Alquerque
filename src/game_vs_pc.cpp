#include "game_vs_pc.h"

game_vs_pc::game_vs_pc(int lv, bool load): level(lv), load(load)
{
        board_ptr =  new board;
        if(load) readFromFile();
        else board_ptr->createPawns();
        board_ptr->draw();


        while(true){
        this->playerMove();
        if(this->winCondition())
        {
            remove( "save.txt" );
            break;
        }
        Sleep(500);
        switch(level){
        case 0:
            this->computerMoveEasy();
            break;
        case 1:
            this->computerMoveNormal();
            break;
        case 2:
            this->computerMoveHard();
            break;
        }
        if(this->winCondition())
        {
            remove( "save.txt" );
            break;
        }

        this->saveToFile();
        }

    }

game_vs_pc::~game_vs_pc()
{
    //dtor
}


void game_vs_pc::saveToFile(){

    std::ofstream fileOut;
    fileOut.open("save.txt");
    std::string tmp;

    fileOut << "1 " << this->level << std::endl;

    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(this->board_ptr->pawns_board_ptr[j][i]!=NULL)
            {tmp+=static_cast<int>(this->board_ptr->pawns_board_ptr[j][i]->x+65);
            tmp+=static_cast<int>(this->board_ptr->pawns_board_ptr[j][i]->y+48);
            tmp+=this->board_ptr->pawns_board_ptr[j][i]->sign;
            fileOut << tmp << " ";
            tmp.clear();
            }
            else fileOut << " x  ";
        }
        fileOut << std::endl;
    }

    fileOut.close();
}

void game_vs_pc::readFromFile(){

    std::ifstream fileIn;
    fileIn.open("save.txt");
    std::string tmp;
    getline(fileIn,tmp);
    tmp.clear();
        for(int i=0; i<5;i++){
            for(int j=0; j<5 && !fileIn.eof(); j++){
            fileIn >> tmp;
            if (tmp=="x") this->board_ptr->pawns_board_ptr[j][i] = NULL;
            else this->board_ptr->pawns_board_ptr[j][i] = new pawns(new cords(tmp), tmp[2]);
            tmp.clear();
        }
    }
    fileIn.close();
}

void game_vs_pc::playerMove(){

    std::string string_start_cords,string_destination_cords;

    while(true){

    this->saveToFile();

    board_ptr->setCursor(0,15);
    std::cout << "\t \t \t \t";
    board_ptr->setCursor(0,16);
    std::cout << "\t \t \t \t";
    board_ptr->setCursor(0,17);
    std::cout << "\t \t \t \t";
    board_ptr->setCursor(0,15);
    std::cout << "Choose a pawn:";

    std::cin >> string_start_cords;
    cords * start_cords = new cords(string_start_cords);
    if(!board_ptr->cordInBoard(start_cords->x, start_cords->y))continue;

     if(board_ptr->isFree(start_cords))
        {
            board_ptr->setCursor(20, 10);
            std::cout << "Pawn doesn't exist \t \t";
            continue;
        }

    if(board_ptr->pawns_board_ptr[start_cords->x][start_cords->y]->sign != 'o')
    {
        board_ptr->setCursor(20, 10);
        std::cout << "It's not your pawn' \t \t";
        continue;
    }



    std::vector<cords*> ViableMoves;
    ViableMoves = board_ptr->checkViableMoves(start_cords);


 if(ViableMoves.empty())
    {
        board_ptr->setCursor(20, 10);
        std::cout << "This pawn can't move' \t \t";
        continue;
    }

    std::cout << "Pick a field:";
    std::cin >> string_destination_cords;
    cords * destination_cords = new cords(string_destination_cords);
    if(!board_ptr->cordInBoard(destination_cords->x, destination_cords->y))continue;



    if(!board_ptr->isFree(destination_cords))
    {
        board_ptr->setCursor(20, 10);
        std::cout << "This field is occupied \t \t";
        continue;
    }


    bool tmp = 0;
    for(std::vector<cords*>::iterator it = ViableMoves.begin(); it!=ViableMoves.end()  ;it++ )
                {
                    if((*it)->x == destination_cords->x && (*it)->y == destination_cords->y)
                    {
                            tmp=true;
                            break;
                    }
                }

        if(tmp)
        {
            board_ptr->movePawn(start_cords,destination_cords);
            std::vector<cords*> tmp = board_ptr->possibleTakdowns(destination_cords);
            if(abs(start_cords->y - destination_cords->y)==2 || abs(start_cords->x - destination_cords->x) == 2)
            if(!tmp.empty()) continue;
            return;
        }
        else
        {
            board_ptr->setCursor(20, 10);
            std::cout << "This move is illegal";
        }


    }

}

void game_vs_pc::computerMoveEasy(){
 //LEVEL EASY: COMPUTER MOVES ARE RANDOM

  std::vector<pawns*> PawnsVec;
    for(int i=0; i<5;i++)
    {
        for(int j=0; j<5; j++)
        {
            if(board_ptr->pawns_board_ptr[i][j]!=NULL)
            {
                if(board_ptr->pawns_board_ptr[i][j]->sign=='*')
                PawnsVec.push_back(board_ptr->pawns_board_ptr[i][j]);
            }
        }
    }

    std::vector<cords*> ViableMoves;
    std::vector<cords*> ViableTakedowns;

        for(std::vector<pawns*>::iterator it = PawnsVec.begin(); it!=PawnsVec.end() ;it++ )
        {

        ViableTakedowns = board_ptr->possibleTakdowns(new cords((*it)->x,(*it)->y));

            for(std::vector<cords*>::iterator it2 = ViableTakedowns.begin(); it2!=ViableTakedowns.end() ;it2++ )
            {
                if(board_ptr->takedownPermission((*it),(*it2)))
                {
                    board_ptr->movePawn(new cords((*it)->x,(*it)->y),(*it2));
                    board_ptr->multiplyTakedowns((*it2));
                    ViableTakedowns.clear();
                    return;
                }
            }
        }


    cords * cordBestMove;
    int intBestMove = 0, tmp;
    pawns * pawnToMove;
    for(std::vector<pawns*>::iterator it = PawnsVec.begin(); it!=PawnsVec.end(); it++ )
    {
        ViableMoves = board_ptr->checkViableMoves(new cords((*it)->x,(*it)->y));

        if(ViableMoves.empty()) continue;
        else
        {
            for(std::vector<cords*>::iterator it2 = ViableMoves.begin(); it2!=ViableMoves.end(); it2++ )
            {
                tmp = board_ptr->canBeTakenDown((*it2), new cords((*it)->x,(*it)->y));
                
                 if(tmp > intBestMove)
                {
                    intBestMove = tmp;
                    cordBestMove = (*it2);
                    pawnToMove = (*it);
                }

            }
        }
    }
    board_ptr->movePawn(new cords(pawnToMove->x, pawnToMove->y), cordBestMove);
    }

void game_vs_pc::computerMoveNormal(){
//LEVEL NORMAL: COMPUTER SEARCHES ONE LEVEL OF THE GAME TREE AND MAKES THE BEST MOVE

    std::vector<pawns*> PawnsVec;
    for(int i=0; i<5;i++)
    {
        for(int j=0; j<5; j++)
        {
            if(board_ptr->pawns_board_ptr[i][j]!=NULL)
            {
                if(board_ptr->pawns_board_ptr[i][j]->sign=='*')
                PawnsVec.push_back(board_ptr->pawns_board_ptr[i][j]);
            }
        }
    }

    std::vector<cords*> ViableMoves;
    std::vector<cords*> ViableTakedowns;

        for(std::vector<pawns*>::iterator it = PawnsVec.begin(); it!=PawnsVec.end() ;it++ )
        {

        ViableTakedowns = board_ptr->possibleTakdowns(new cords((*it)->x,(*it)->y));

            for(std::vector<cords*>::iterator it2 = ViableTakedowns.begin(); it2!=ViableTakedowns.end() ;it2++ )
            {
                if(board_ptr->takedownPermission((*it),(*it2)))
                {
                    board_ptr->movePawn(new cords((*it)->x,(*it)->y),(*it2));
                    board_ptr->multiplyTakedowns((*it2));
                    ViableTakedowns.clear();
                    return;
                }
            }
        }

    while(true)
    {
        int r = rand()%PawnsVec.size();

        pawns * pawn = PawnsVec[r];
        ViableMoves = board_ptr->checkViableMoves(new cords(pawn->x,pawn->y));

        if(ViableMoves.empty()) continue;
        else
        {
         r = rand()%ViableMoves.size();

        board_ptr->movePawn(new cords(pawn->x, pawn->y), ViableMoves[r]);
        break;
        }
    }

}

void game_vs_pc::computerMoveHard(){
//LEVEL HARD: COMPUTER SEARCHES TWO LEVELS OF THE GAME TREE AND MAKES THE BEST MOVE POSSIBLE, IT ALSO CHECKS FOR THREAT LEVELS OF CHECKED MOVES



  std::vector<pawns*> PawnsVec;
    for(int i=0; i<5;i++)
    {
        for(int j=0; j<5; j++)
        {
            if(board_ptr->pawns_board_ptr[i][j]!=NULL)
            {
                if(board_ptr->pawns_board_ptr[i][j]->sign=='*')
                PawnsVec.push_back(board_ptr->pawns_board_ptr[i][j]);
            }
        }
    }

    std::vector<cords*> ViableMoves;
    std::vector<cords*> ViableTakedowns;

        for(std::vector<pawns*>::iterator it = PawnsVec.begin(); it!=PawnsVec.end() ;it++ )
        {

        ViableTakedowns = board_ptr->possibleTakdowns(new cords((*it)->x,(*it)->y));

            for(std::vector<cords*>::iterator it2 = ViableTakedowns.begin(); it2!=ViableTakedowns.end() ;it2++ )
            {
                if(board_ptr->takedownPermission((*it),(*it2)))
                {
                    board_ptr->movePawn(new cords((*it)->x,(*it)->y),(*it2));
                    board_ptr->multiplyTakedowns((*it2));
                    ViableTakedowns.clear();
                    return;
                }
            }
        }


    cords * cordBestMove;
    int intBestMove = 5, tmp;
    pawns * pawnToMove;
    for(std::vector<pawns*>::iterator it = PawnsVec.begin(); it!=PawnsVec.end(); it++ )
    {
        ViableMoves = board_ptr->checkViableMoves(new cords((*it)->x,(*it)->y));

        if(ViableMoves.empty()) continue;
        else
        {
            for(std::vector<cords*>::iterator it2 = ViableMoves.begin(); it2!=ViableMoves.end(); it2++ )
            {

                tmp = board_ptr->canBeTakenDown((*it2), new cords((*it)->x,(*it)->y));

                if(tmp < intBestMove)
                {
                    intBestMove = tmp;
                    cordBestMove = (*it2);
                    pawnToMove = (*it);
                }

            }
        }
    }
    board_ptr->movePawn(new cords(pawnToMove->x, pawnToMove->y), cordBestMove);
}

bool game_vs_pc::winCondition(){

 if(!board_ptr->pawnsLeft('*'))
        {
            system("cls");
            board_ptr->setCursor(15, 7);
            std::cout << "White has won (o)";
            system("pause");
            return true;
        }
        if(!board_ptr->pawnsLeft('o'))
        {
            system("cls");
            board_ptr->setCursor(15, 7);
            std::cout << "Black has won (*)";
            system("pause");
            return true;
        }

}













