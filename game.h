#ifndef GAME_H
#define GAME_H
class Game
{
private:
	int player_id,no_of_rings,time;
public:
			// write the names of data members to be used and member functions required along with why/what to do in it
	Game();
	Game(int id,int n,int time);
	string playmove(string opp_move);
};

#endif
