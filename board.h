#ifndef BOARD_H
#define BOARD_H

class Node{
    public:
        int row, col;
        /*
        Row varies from 0 - 9 
        Col varies from a - k ( ie 0 to 9)
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
			// write the names of data members to be used and member functions required along with why/what to do in it
	Board();
	
};

#endif
