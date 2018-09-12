
#ifndef POSSIBLEMOVE_H
#define POSSIBLEMOVE_H

#include "node.h"	// define it seperately
#include "utils.h"
class PossMove
{
		Node nodes[11][11];		//scenerio for moves
		vector< vector<Move> > possiblemoves;
		int totalMoves,currmove;
		int flag;	//nodes set or not
		void init();	// called by constructors and some functions
	public:
		Move();	//sets pointers to null
		Move(Node **curr_nodes);	//set pointers to null and sets nodes
		~Move();	//frees all memory allocated If any
		Node node getNode(int row,int coloumn);
		void setNode(int row,int coloumn,Node node);	//sets particular configuration at specified row coloumn node and moves to null
		int poss_moves(int color);
		//find possible moves of given color and return no. of moves found
		vector<Move> getNextMove();	//returns next move in array
}

#endif