#include "game.h"

Game::Game()
{
	player_id=1;
	no_of_rings=5;
	time=150;
}

Game::Game(int id,int n,int time)
{
	player_id=id;
	no_of_rings=n;
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

// take the input from your player file and make it available here

//node class - row coloumn colour ring --2darray

//board class - read move and convert it to opposite format
