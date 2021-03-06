#ifndef GAME_H
#define GAME_H
#include<fstream>
#include"utils.h"
#include"board.h"
#include"timing.h"

class Game
{
public:
	// int player_id,no_of_rings,time;
	int time;
	timing *timer;
	double weights[5];
	Board* board; 
	Board* origBoard;
	// write the names of data members to be used and member functions required along with why/what to do in it
	Game();
	Game(int n,timing *timer,int argc, char **argv);
	void setWeights(int argc, char **argv);
	void playmove(vector<Move>, int player);
	void changeLine(int player, int r1, int c1, int r2, int c2, bool remove);
	void removeRing(int player, int r, int c);
	void placeRing(int player, int r, int c);
	//return the most optimal move for specified player
	vector<Move> getMove(int playerid);
	//checkes for >=5 contigually placed markers 
	//will return the 1st max sequence found, otherwise NULL
	vector<Move> checkContigousMarkers(int player);
	//makes in a move format the start and end nodes
	vector<Move> makeContigousMove(int player, int r1, int c1, int r2, int c2);
	//places the hand ring optimally for the given player
	vector<Move> placeHandRing(int player);
	//get possiblilites of move by perturbing specific ring
	vector<vector<Move>> perturbRing(int player, int r, int c);
	//creates a possiblity of a ring here and checks if contigous rings is possible
	vector<Move> spawnRing(int player, int r1, int c1, int r2, int c2);
	//checks if a row of markers exist if not then .first.first=-1
	// pair<pair<int,int>, pair<int,int>> removableMarkers(int color,int &marks,int pos[121][2]);
	double evaluate(int playerid,int origplayer);
	// void initPossibleMoves();
	double minmax(int playerid,int origplayer,int alpha,int beta);
	vector<vector<Move>> allPossibleMoves(int player);
	//find possible moves of given color and return no. of moves found
	//we have three kinds of move - [i][j++],[++][j],[++][++]
		
};

#endif
