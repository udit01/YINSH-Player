
#ifndef POSSIBLEMOVE_H
#define POSSIBLEMOVE_H

#include "board.h"	// define it seperately
#include "utils.h"
#include <vector>
#include <utility>

class PossMove
{
		Node nodes[11][11];		//scenerio for moves
		vector< vector<Move> > possiblemoves;
		int totalMoves,currmove;
		int flag;	//nodes set or not
		void init();	// called by constructors and some functions
		pair < pair<int,int> , pair<int,int> > removableMarkers(int color,int &marks,int pos[121][2]);
		//checks if a row of markers exist if not then .first.first=-1
	public:
		PossMove();	//sets pointers to null
		PossMove(Node **curr_nodes);	//set pointers to null and sets nodes
		Node getNode(int row,int coloumn);
		void setNode(int row,int coloumn,Node node);	//sets particular configuration at specified row coloumn node and moves to null
		int poss_moves(int color);
		//find possible moves of given color and return no. of moves found
		//we have three kinds of move - [i][j++],[++][j],[++][++]
		vector<Move> getNextMove();	//returns next move in array
}

#endif
