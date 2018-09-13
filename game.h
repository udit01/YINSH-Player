#ifndef GAME_H
#define GAME_H

#include"utils.h"
#include"board.h"
#include"PossibleMove.h"

class Game
{
public:
	int player_id,no_of_rings,time;
	Board* b;
	PossMove* pm;
	// write the names of data members to be used and member functions required along with why/what to do in it
	Game();
	Game(int id,int n,int time);
	void playmove(vector<Move>);
	vector<Move> getMove();
};

#endif
