#ifndef BOARD_H
#define BOARD_H

class Node{
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
};

class Board
{
private:

public:
	Board();
    /*
    Nodes have the following ranges
    Col  ->   Row-range
    a 0  ->   0 - 3 
    b 1  ->   0 - 6 
    c 2  ->   0 - 7 
    d 3  ->   0 - 8 
    e 4  ->   0 - 9 
    f 5  ->   0 - 8  // central col
    g 6  ->   0 - 9 
    h 7  ->   0 - 8 
    i 8  ->   0 - 7 
    j 9  ->   0 - 6 
    k 10 ->   0 - 3 
    */
   
    
	
};

#endif
