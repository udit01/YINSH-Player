
#ifndef MOVE_H
#define MOVE_H

#include "node.h"	// define it seperately

class Move
{
		Node nodes[11][11];		//scenerio for moves
		char * singlemove;		//single possible next move
		char ** moves;			//array of moves
		int Max_moves,Max_length_move;	//to get dynamic array of pointers to moves
		int totalMoves,currmove;
		int flag;	//nodes set or not
		void init();	// called by constructors and some functions
	public:
		move();	//sets pointers to null
		move(Node **curr_nodes);	//set pointers to null and sets nodes
		~move();	//frees all memory allocated
		Node node getNode(int row,int coloumn);
		void setNode(int row,int coloumn,Node node);	//sets particular configuration at specified row coloumn node and moves to null
		int poss_moves(int color);
		//find possible moves of given color and return no. of moves found
		string getNextMove();	//returns next move in array
}

#endif
