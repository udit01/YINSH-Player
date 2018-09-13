#include "game.h"

Game::Game()
{
	player_id=1;
	no_of_rings=5;
	time=150;
}

Game::Game(int id,int n,int time)
{
	this->player_id=id;
	this->no_of_rings=n;
	this->time=time;
}
	
void Game::playmove(vector<Move> move)
{ 
	//play the move in the game
	
	//opp_move=board.convert(opp_move
	// string my_move;
		//our code
	// return my_move;
}

vector<Move> Game::getMove(){
	vector<Move> move;
	return move;
}