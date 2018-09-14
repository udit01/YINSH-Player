#include <iostream>
#include <assert.h>
#include "game.h"
#include "PossibleMove.h"

Game::Game()
{
	player_id=1;
	no_of_rings=5;
	time=150;
	initPossibleMoves();
}

Game::Game(int id,int n,int time)
{
	this->player_id=id;
	this->no_of_rings=n;
	this->time=time;
	this->board = new Board(5);
	// this->pm = new PossMove(this->b->nodes);

}
	
void Game::playmove(vector<Move> move, int player)
{ 
	/*We get a player's  move and we have to play it*/
	int me = player;
	int opp = 3 - me;
	int type = 0, row = 0, col = 0;
	//ring start row and column
	int rsr = 0, rsc = 0;


	/*
	Types of sequences in the game : 
	-> Place
	-> Select ring(marker put), then move
	-> Remove a row start (marker put), then move (in general started by move seq)
	When is it started from non move ?
		S 1 2 M 2 4 RS 1 2 RE 4 16 X 3 4


	*/

	Node n;

	//play the move in the game
	for(std::vector<Move>::iterator it = move.begin(); it != move.end(); ++it) {
		type = (*it).moveType; row = (*it).row; col = (*it).col;

		assert(this->board->nodes[row][col].valid);

		switch(type){
			case 0: /* Placing a ring */
				this->board->nodes[row][col].ring = me;
				break;
			case 1: /* Selecting a ring(and therefore putting the marker) */
				// Put the marker on this node 
				this->board->nodes[row][col].color = me;
				//set ring start row and column
				rsr = row; rsc = col;
				break;
			case 2: /*Move ring comes after selection*/
				assert( (rsr!= 0) && (rsc!=0)); //weaker assert condition
				//assert somehow that ringstartpos was evaluated
				for(int i = rsr; i <= row; i++){
					
					//wrong logic for j 
					int j = rsc + (i-rsr);
					n = this->board->nodes[i][j];

					//all should be valid by default
					if(n.valid && (n.color!=0)){
						n.color = 3 - n.color; // Flipping the colors in the path
					}
				}

		}

	/* std::cout << *it; ... */
	}
	
}

vector<Move> Game::getMove(){
	this->origBoard = this->board->deepCopy();

	vector<Move> move;
	//get the next move by min max or something


	return move;
}

/*
From the PossibleMoves class
*/

void Game::initPossibleMoves(){
	this->flag = 1;
	this->totalMoves = 0;
	this->currMove = 0;
}
/*
Instead of nodes copy , we'll work on a board's copy
because we need the number of rings and other things preserverd
*/
//get set is unrequired 

Node Game::getNode(int row,int coloumn)
{
	if((row<11)&&(coloumn<11)){
		Node n = this->board->nodes[row][coloumn];
		if (n.valid){
			return n;
		}
	}
	
	cerr << "Trying to get an Invalid or out of range Node" << endl;
	exit(1);
}

void Game::setNode(int row,int coloumn,Node node)
{
	if((row<11)&&(coloumn<11))
	{
		this->totalMoves = 0;
		this->currMove = 0;
		this->possibleMoves.clear();			
		this->board->nodes[row][coloumn] = node;
		return;
	}
	//else					
	cerr << "Trying to set an out of bounds node" << endl;
	exit(1);
}


pair< pair<int,int>, pair<int,int>> Game::removableMarkers(int color,int &marks,int pos[121][2])
{
	int i,j,k;
	for(i=0;i<marks;i++)
	{
		if(this->board->nodes[pos[i][0]][pos[i][1]].color != color)
		{
			cerr<<"some error in marker colouring or finding markers"<<endl;
			exit(1);
		}
		// code to find removable markers is under process	//need to be generic removal has been fixed
		for(j=1;(this->board->nodes[(pos[i][0])-j][pos[i][1]].valid)&&(this->board->nodes[(pos[i][0])-j][pos[i][1]].color==color);j++);
		for(k=1;(this->board->nodes[(pos[i][0])+k][pos[i][1]].valid)&&(this->board->nodes[(pos[i][0])+k][pos[i][1]].color==color);k++);
		if(j+k-1 >= 5) return make_pair(make_pair(((pos[i][0])-j+1),pos[i][1]),make_pair(((pos[i][0])-j+5),pos[i][1]));
		//else
		for(j=1; (this->board->nodes[pos[i][0]][pos[i][1]-j].valid) && this->board->nodes[pos[i][0]][(pos[i][1])-j].color==color;j++);
		for(k=1; (this->board->nodes[pos[i][0]][pos[i][1]+k].valid) && this->board->nodes[pos[i][0]][(pos[i][1])+k].color==color;k++);
		if(j+k-1 >= 5) return make_pair(make_pair(pos[i][0],((pos[i][1])-j+1)),make_pair(pos[i][0],((pos[i][1])-j+1)));
		//else
		for(j=1; (this->board->nodes[pos[i][0]-j][pos[i][1]-j].valid) && this->board->nodes[(pos[i][0])-j][(pos[i][1])-j].color==color;j++);
		for(k=1; (this->board->nodes[pos[i][0]+k][pos[i][1]+k].valid) && this->board->nodes[(pos[i][0])+k][(pos[i][1])+k].color==color;k++);
		if(j+k-1 >= 5) return make_pair(make_pair(((pos[i][0])-j+1),((pos[i][1])-j+1)),make_pair(((pos[i][0])-j+5),((pos[i][1])-j+1)));
		//else
		return make_pair(make_pair(-1,0),make_pair(0,0));
	}
}


int Game::poss_moves(int color)
{
	if(this->flag)
	{
		cerr<<"nodes not set for possiblemoves"<<endl;
		exit(1);
	}
	//else
	int i,j;
	vector<Move> poss_move;		//single possible move
	int whiteRings=0,blackRings=0,whiteringPos[5][2],blackringPos[5][2];		//considering white as player1 black as player2
	int whiteMarks=0,blackMarks=0,whiteMarkPos[121][2],blackMarkPos[121][2];	//no issues of this outside this class
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			if(this->board->nodes[i][j].valid==0)
				continue;
			//else
			switch(this->board->nodes[i][j].ring)
			{
				case 1 :
					whiteringPos[whiteRings][0]=i;
					whiteringPos[whiteRings][1]=j;
					whiteRings++;
					break;
				case 2 :
					blackringPos[blackRings][0]=i;
					blackringPos[blackRings][1]=j;
					blackRings++;
					break;
				case 0 :
				//rings and markers can't be true together hence here is possiblity of marker
					switch(this->board->nodes[i][j].color)
					{
						case 1 :
							whiteMarkPos[whiteMarks][0]=i;
							whiteMarkPos[whiteMarks][1]=j;
							whiteMarks++;
							break;
						case 2 :
							blackMarkPos[blackMarks][0]=i;
							blackMarkPos[blackMarks][1]=j;
							blackMarks++;
							break;
						default :
							cerr<<"markers not properly assigned to this->board->nodes"<<endl;
							exit(1);
					}
					break;
				default :
					cerr<<"rings not properly assigned to this->board->nodes"<<endl;
					exit(1);
			}
			
		}
	}
	//is it possible that we need to remove markers before move
	pair < pair<int,int> , pair<int,int> > remove;
	switch (color)
	{
		case 1 :
			remove=removableMarkers(1,whiteMarks,whiteMarkPos);
			break;
		case 2 :
			remove=removableMarkers(2,blackMarks,blackMarkPos);
			break;
		default :
			cerr<<"wrong color passed to poss_moves()"<<endl;
			exit(1);
	}
	if(remove.first.first != -1)
	{
		poss_move.push_back(Move(3,remove.first.first,remove.first.second));
		poss_move.push_back(Move(4,remove.second.first,remove.second.second));
		switch (color)
		{
			case 1 :
				poss_move.push_back(Move(5,whiteringPos[whiteRings-1][0],whiteringPos[whiteRings-1][1]));//need to make it for all rings, right now removing only last one
				whiteRings--;
				break;
			case 2 :
			poss_move.push_back(Move(5,blackringPos[blackRings-1][0],blackringPos[blackRings-1][1]));//need to make it for all rings, right now removing only last one
				blackRings--;
				break;
		}
		//ring movements need to be added to each move
		totalMoves=1;	//need to be considered while all rings possible to remove
		possibleMoves.push_back(poss_move);
		return totalMoves;
	}
	//else
	//other moves - movement of rings
	if(color==1)
	{
		for(i=0;i<whiteRings;i++)
		{
			int ringposi=whiteringPos[whiteRings][0];
			int ringposj=whiteringPos[whiteRings][1];
			int x;
			
		}
	}
}
