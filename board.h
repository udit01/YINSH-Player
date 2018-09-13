/*
    board.h
    Author : udit01
*/

#ifndef BOARD_H
#define BOARD_H

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
	int p1ringsRem, p2ringsRem; //no. of rings currently remaining
    int p1ringsDone, p2ringsDone;// no. of rings completed
	int white_pos[5][2],black_pos[5][2];	// stores the current ring positions
    Node** nodes;
    
    Board();
	Board(int boardSize);
	void markValidity();
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
