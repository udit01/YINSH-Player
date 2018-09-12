
#ifndef MOVE_H
#define MOVE_H

#include "node.h"	// define it seperately

class move
{
		Node nodes[11][11];		//scenerio for moves
		char ** moves;			//strings of moves
		int Max_moves;	//to get dynamic array of pointers to moves
		int totalMoves,currmove;
		int flag;	//nodes set or not
		void init();	// called by constructors
	public:
		move();	//sets pointers to null
		move(Node **curr_nodes);	//set pointers to null and sets nodes
		node node getNode(int row,int coloumn);
		void setNode(int row,int coloumn,Node node);	//sets particular configuration at specified row coloumn node
		int poss_moves(int color);
		//find possible moves of given color and return no. of moves found
		string getNextMove();	//returns next move in array
}

#endif
