
#ifndef MOVE_H
#define MOVE_H

#include "node.h"

class move
{
	public:
		string * poss_moves(Node **nodes,int color,int ringsOfColor, int **positionOfRingsOfColor);
		// gets a scenerio of board in arguments and find possible moves of given color for given rings
}

#endif
