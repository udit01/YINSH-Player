
#ifndef MOVE_H
#define MOVE_H

#include "node.h"	// define it seperately

class move
{
		Node nodes[11][11];		//scenerio for moves
		char ** moves;			//strings of moves
		int totalMoves,currmove;
		int flag;
	public:
		move();	//sets pointers to null
		move(Node **curr_nodes);	//set pointers to null and sets nodes
		int poss_moves(int color);
		//find possible moves of given color and return no. of moves found
}

#endif
