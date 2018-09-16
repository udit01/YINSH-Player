/*
    board.h
    Author : udit01
*/

#ifndef BOARD_H
#define BOARD_H
#include <iostream>

using namespace std;
class Node{			//make seperate file as needed to be included at different places
    public:
        int row, col;
        /*
        Row varies from 1- 11 (ie 0 to 10 max) 
        Col varies from a - k (ie 0 to 10 max)
        */
        int color; 
        /* Color can have 0 1 or 2 corresponding to 
            no marker, player 1 marker or player 2 marker
        */
        int ring;
        /* Ring can have 0 1 or 2 corresponding to 
            no ring, player 1 ring or player 2 ring
        */ 
        bool valid;
        //(0 or 1)the node is in specified range or not
        Node* deepCopy();
        //methods for getvalid,getcolor,getring required
};

class Board
{
public:
    int boardSize;
    
	int ringsHand[2]; //no. of rings currently in hand
	int ringsDone[2]; //no. of rings currently on board's side
	// int white_pos[5][2],black_pos[5][2];	// stores the current ring positions
	
    //contaitns positions of 2 players' 5 rings' row and col's
    int ring_pos[2][5][2];
    
    Node** nodes;
    
    Board();
	Board(int boardSize);
	void markValidity();
    void printBoard();
    /*
    Nodes have the following ranges
    Col  ->   Row-range
    a 0  ->   1 - 4  (3)
    b 1  ->   0 - 6  (6)
    c 2  ->   0 - 7  (7)
    d 3  ->   0 - 8  (8)
    e 4  ->   0 - 9  (9)
    f 5  ->   1 - 9  (8)// central col
    g 6  ->   1 - 10 (9)
    h 7  ->   2 - 10 (8)
    i 8  ->   3 - 10 (7)
    j 9  ->   4 - 10 (6)
    k 10 ->   6 - 9  (3)
    */

    Board* deepCopy();
	
};

#endif
