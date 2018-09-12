/*
    utils.h
    Author : udit01
*/
#ifndef UTILS_H
#define UTILS_H

#include<vector.h>
#include"board.h"


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

        static vector<Move> convertToStd(String s);

       /*Converts a Move vector to Standard string with \n included */
        static string convertToHexagonal( vector<Move> moves);

};


#endif
