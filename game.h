#ifndef GAME_H
#define GAME_H

#include"utils.h"
#include"board.h"
#include"PossibleMove.h"

class Game
{
public:
	// int player_id,no_of_rings,time;
	int time;
	Board* board; 
	Board* origBoard;
	// write the names of data members to be used and member functions required along with why/what to do in it
	Game();
	Game(int id,int n,int time);
	void playmove(vector<Move>, int player);
	void changeLine(int player, int r1, int c1, int r2, int c2, bool remove);
	void removeRing(int player, int r, int c);
	vector<Move> getMove(int playerid);

	// Possible Moves adaptives: Will make a board copy 
	vector<vector<Move>> possibleMoves;
	int totalMoves, currMove;
	int flag;
	
	//checks if a row of markers exist if not then .first.first=-1
	pair<pair<int,int>, pair<int,int>> removableMarkers(int color,int &marks,int pos[121][2]);
	double evaluate(int playerid,int origplayer);
	void initPossibleMoves();
	Node getNode(int row, int col);
	double minmax(int playerid,int origplayer,int alpha,int beta);
	void setNode(int row,int coloumn,Node node);	//sets particular configuration at specified row coloumn node and moves to null
	int poss_moves(int color);
	//find possible moves of given color and return no. of moves found
	//we have three kinds of move - [i][j++],[++][j],[++][++]
		
};

#endif
