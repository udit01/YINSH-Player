#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "utils.h"


using namespace std;

vector<string> moveCodes = {"P", "S", "M", "RS", "RE", "X"};
int flag = 0;

//change according to size of board
pair<int, int> mapping[6][36];
pair<int, int> reverseMapping[11][11];


Move::Move(int mt, int r, int c){
    this->moveType = mt; 
    this->row = r;
    this->col = c;
}

void formMap( int boardSize  ) {
    /*
    Docs Keeping in mind boardsize = 5
    Rows and Columns from 0...b....2*b 
    Hexagons number (h) from 0 ... b 
    and pos from 0 .... 6*h - 1 
    */
    int central = boardSize; // central square 
    int minlimit = 0, maxlimit = 0;
    int itr1 = 0, itr2 = 0;
    int limitcounter = 0;

    // tc.insert( make_pair(0, 0), make_pair(central, central) );
    
    mapping[0][0] = make_pair(central, central);
    reverseMapping[central][central] = make_pair(0, 0);

    for(int hexNum = 1 ; hexNum <= boardSize; hexNum++ ){
        
        //these must be repeated (hexNum+1) times
        minlimit = central - hexNum;
        maxlimit = central + hexNum;
        
        itr1 = central;
        itr2 = maxlimit;
        limitcounter = hexNum + 1 ;

        int counter1 = limitcounter;
        int counter2 = limitcounter;
        int dir1 = +1; 
        int dir2 = -1;

        for(int pos = 0 ; pos < 6 * hexNum; pos++){
        
            mapping[hexNum][pos] = make_pair(itr1, itr2);
            reverseMapping[itr1][itr2] = make_pair(hexNum, pos);

            if(itr1 == minlimit){
                counter1--;
                if(counter1 == 0){
                    dir1 = +1; counter1 = limitcounter; itr1 += dir1;
                }
            }else if(itr1 == maxlimit){
                counter1--;
                if(counter1 == 0){
                    dir1 = -1; counter1 = limitcounter; itr1 += dir1;
                }
            }else{
                itr1 += dir1;
            }

            if(itr2 == minlimit){
                counter2--;
                if(counter2 == 0){
                    dir2 = +1; counter2 = limitcounter; itr2 += dir2;
                }
            }else if(itr2 == maxlimit){
                counter2--;
                if(counter2 == 0){
                    dir2 = -1; counter2 = limitcounter; itr2 += dir2;
                }
            }else{
                itr2 += dir2;
            }

        }
    }
} 

/*
Returns Move in the transformed standard coordinates

Do casewise in case of moves with start and end both

*/
// Move transformCoord( int moveType, int hexNum, int pos ){
    
//     Move* start = new Move()

// }

//INIT mapping once
constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}


vector<Move> convertToStd(string move){

    if(flag == 0){
        formMap(5); flag = 1;
    }

    stringstream moveStream(move);
    string token;
    char delim = ' ';
    
    int number = 0;
    int counter = 0;
    int moveNumber = 0;
    int hexNum = 0;
    int position = 0;

    vector<Move> moveVector;

    while (getline(moveStream, token, delim)) {
        
        switch (str2int(token.c_str())){

            case str2int("P") : moveNumber = 0; counter = (counter + 1) % 3; break;
            case str2int("S") : moveNumber = 1; counter = (counter + 1) % 3; break;
            case str2int("M") : moveNumber = 2; counter = (counter + 1) % 3; break;
            case str2int("RS"): moveNumber = 3; counter = (counter + 1) % 3; break;
            case str2int("RE"): moveNumber = 4; counter = (counter + 1) % 3; break;
            case str2int("X") : moveNumber = 5; counter = (counter + 1) % 3; break;
            //otherwise it's a number
            default : 
                number = stoi(token);
                if(counter % 3 == 1 ){ 
                    // it's the hexagon number or the first number after movetype
                    hexNum = number;

                }else if(counter % 3 == 2){
                    // it's position number , 2nd after the move type
                    position = number;
                    pair<int, int> p = mapping[hexNum][position];
                    moveVector.push_back(Move(moveNumber, p.first, p.second));
                }
                else{
                    //some error in parsing
                    cerr << "Some error in parsing " << token << " : from : " << moveStream.str() ;
                }

                counter = (counter + 1) % 3;

        }
    }

    return moveVector;

}

string convertToHexagonal( vector<Move> moves){
    if(flag == 0){
        formMap(5); flag = 1;
    }

    stringstream cmoves;
    string type;
    pair<int, int> p;
    vector<Move>::iterator itr ;

    for(itr = moves.begin(); itr != moves.end(); itr++){
        switch(itr->moveType){
            case 0 : type = "P" ; break;
            case 1 : type = "S" ; break;
            case 2 : type = "M" ; break;
            case 3 : type = "RS"; break;
            case 4 : type = "RE"; break;
            // case 5 : type = "P" ; break;
            default: type = "X" ;
        }
        p = reverseMapping[itr->row][itr->col];
        cmoves << type << " " << p.first << " " << p.second << " " ;
        // I am adding a trailing space above, test that it doesn't affect 
    }

    cmoves << "\n";
    return cmoves.str();
}