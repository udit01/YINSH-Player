
#ifndef MOVE_H
#define MOVE_H

#include "node.h"	// define it seperately

class move
{
		Node nodes[11][11];		//scenerio for moves
		char ** moves;			//strings of moves
		int totalMoves,currmove;
	public:
		char ** poss_moves(int color);
		//find possible moves of given color
}

#endif
