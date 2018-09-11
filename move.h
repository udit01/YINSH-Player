
#ifndef MOVE_H
#define MOVE_H

#include "node.h"	// define it seperately

class move
{
	public:
		char ** poss_moves(Node **nodes,int color,int ringsOfColor, int **positionOfRingsOfColor,int total_rows,int total_cols);
		// gets a scenerio of board in arguments and find possible moves of given color for given rings
}

#endif
