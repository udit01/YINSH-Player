/*
    utils.h
    Author : udit01
*/
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "board.h"

using namespace std;

/*Can also put the moves in an array, then no need to iterate over vector every time*/
class Move{
    public:
        /* Mapped to integer in the following order
        P - Place a ring        0
        S - Select a ring       1
        M - Move a ring         2
        RS - Remove a row Start 3
        RE - Remove a row End   4
        X - Remove a ring       5
        */
        int moveType; 

        int  row, col;
        /*MoveType move from start to end
        */

       /*Converts the move from hexagonal to standard coordinates*/
        Move(int mt, int r, int c);

        // static vector<Move> convertToStd(string s);

       /*Converts a Move vector to Standard string with \n included */
        // static string convertToHexagonal( vector<Move> moves);

};


vector<Move> convertToStd(string s);
string convertToHexagonal( vector<Move> moves);
void getStd(int hexNum, int pos, int coord[2] );
void getHex(int row, int col, int coord[2] );

#endif
