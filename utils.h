/*
    utils.h
    Author : udit01
*/
#ifndef UTILS_H
#define UTILS_H

#include<board.h>
#include<vector.h>

class Move{
    public:
        /* Mapped to integer in the following order
        P - Place a ring 
        S - Select a ring
        M - Move a ring
        RS - Remove a row Start
        RE - Remove a row End
        X - Remove a ring
        */
        int moveType: 

        Node* start, end;
        /*MoveType move from start to end
        */

       /*Converts the move from hexagonal to standard coordinates*/
        static vector<Move> convertToStd(String s);

       /*Converts a Move vector to Standard string */
        static string convertToHexagonal( vector<Move> moves);

};


#endif
