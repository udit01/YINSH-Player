#include <iostream>
#include <assert.h>
#include "game.h"
#include "PossibleMove.h"

Game::Game(){
	time=150;
	initPossibleMoves();
}

Game::Game(int id,int n,int time){
	this->time=time;
	this->board = new Board(5);
	// this->pm = new PossMove(this->b->nodes);
}

void Game::changeLine(int player, int r1, int c1, int r2, int c2, bool remove){
	
	//assert that unequal blocks
	assert( !( (r1 == r2) && (c1 == c2) ));

	//assert start and end points valid
	Node n = this->board->nodes[r1][c1];
	
	assert(n.valid);
	if(remove){
		//color is being checked in the loops so no need to check again 
		// assert(n.color == player);
		assert(n.ring == player); 
		//also check if ring pos is the appropriate thing ?
	}
	n = this->board->nodes[r2][c2];
	
	assert(n.valid);

	
	if(remove){
			//because we're including both of edge points
			// differnece in atleast 1 of them must be above removal threhold
			assert((abs(r2 - r1) >= 4) || (abs(c2 - c1) >= 4));
	}

	int minIdx, maxIdx;
	
	
	//same row , or same col jump or both changeing equally
	if(r1 == r2){
		minIdx = (c1 > c2) ? c2:c1;
		maxIdx = (c2 + c1) - minIdx;
		
		
		for(int i = minIdx; i <= maxIdx; i++){
		
			n = this->board->nodes[r2][i];

			assert(n.valid); // all should be valid by default
			if(remove){
				assert(n.color == player);
				n.color = 0;
			}
			else{
				n.color = (n.color == 0) ? 0 : (3 - n.color); // Flipping the colors in the path
			}
		}
		
	}else if(c1 == c2){
		minIdx = (r1 > r2) ? r2:r1;
		maxIdx = (r2 + r1) - minIdx;
		
		for(int i = minIdx; i <= maxIdx; i++){
		
			n = this->board->nodes[i][c2];

			assert(n.valid); // all should be valid by default
			if(remove){
				assert(n.color == player);
				n.color = 0;
			}
			else{
				n.color = (n.color == 0) ? 0 : (3 - n.color); // Flipping the colors in the path
			}

		}
	}else{
		//both iterate

		assert(abs(r1-r2) == abs(c1-c2));
		int dir1 = (r2 - r1)/(abs(r2-r1));
		int dir2 = (c2 - c1)/(abs(c2-c1));
		//other complex logic here depeding on signs of r1-r2 and c2-c1
		int j = c1 ;
		for(int i = c1; i != r2; i+=dir1){
			j += dir2;
			n = this->board->nodes[i][r2];

			assert(n.valid); // all should be valid by default
			if(remove){
				assert(n.color == player);
				n.color = 0;
			}
			else{
				n.color = (n.color == 0) ? 0 : (3 - n.color); // Flipping the colors in the path
			}

		}
	}

	if(remove){
		//change the ring position 
		n = this->board->nodes[r1][c1];
		n.ring = 0;
		n = this->board->nodes[r2][c2];
		n.ring = player;

		for(int k = 0 ; k < 5 ; k++ ){
			if((this->board->ring_pos[player-1][k][0] == r1 ) && (this->board->ring_pos[player-1][k][1] == c1) ){
				
				this->board->ring_pos[player-1][k][0] = r2; 
				this->board->ring_pos[player-1][k][1] = c2;

			}
		}

	}
}	

void Game::removeRing(int player, int r, int c){
	assert(this->board->ringsRem[player-1]>0);
	//what if >= 3 ?
	// assert(this->board->ringsDone[player-1]>3);
	Node n = this->board->nodes[r][c];
	assert(n.valid);
	assert(n.ring == player);

	//erase ring
	n.ring = 0;

	//erase ring from position base
	for(int k = 0 ; k < 5 ; k++ ){
			if((this->board->ring_pos[player-1][k][0] == r ) && (this->board->ring_pos[player-1][k][1] == c) ){
				this->board->ring_pos[player-1][k][0] = 0; 
				this->board->ring_pos[player-1][k][1] = 0;
			}
	}

	//counter inc/dec of reamaining and done rings
	this->board->ringsRem[player-1]--;
	this->board->ringsDone[player-1]++;

}

void Game::playmove(vector<Move> move, int player){ 
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
		type = it->moveType; row = it->row; col = it->col;

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
				this->changeLine(me, rsr, rsc, row, col, false);
				break;
			case 3: /*RS may come standalone*/
			//check the rings are in order
				//set ring start row and column
				rsr = row; rsc = col;
				break;
			case 4: /*RE ring comes after selection*/
				assert( (rsr!= 0) && (rsc!=0)); //weaker assert condition
				//assert somehow that ringstartpos was evaluated
				this->changeLine(me, rsr, rsc, row, col, true);
				break;
			case 5: /*X is remove ring do after appropirate checking*/
				this->removeRing(me, row, col);
				break;
			default:
				cerr << "Some error in move type " << type << endl;
				exit(1);
		}

	/* std::cout << *it; ... */
	}
	
}

double Game::evaluate(int playerid,int origplayer){
	int i,j;
	double score;
	int markers[2]={0,0};
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			if(this->board->nodes[i][j].valid)
			{
				if(this->board->nodes[i][j].color==playerid) markers[playerid-1]++;
				else if(this->board->nodes[i][j].color==(3-playerid)) markers[2-playerid]++;
			}
		}
	}
	if(this->board->ringsRem[origplayer-1]==2) return Weight[0];	//our winning
	if(this->board->ringsRem[2-origplayer]==2) return -1*(Weight[1]*Weight[0]);	//worsness of oppnonent's win
	//else
	score=this->board->ringsRem[2-playerid]-this->board->ringsRem[playerid-1];//differnce in rings
	score+=0.1*(markers[playerid-1]-markers[2-playerid]);//marker difference;
	return score;
}

double Game::minmax(int playerid,int origplayer,int alpha,int beta){
	Board* b1 = this->board->deepCopy();
	static int depth=0;
	if (depth==6)
	{
		depth=1;
		return evaluate(playerid,origplayer);
	}
	//get the next move by min max or something
	poss_moves(playerid);
	vector<vector<Move>> possMove;
	possMove=possibleMoves;
	double score,local_score;
	double positivity=0.0;
	if(possMove.empty())
	{
		depth=1;
		return evaluate(playerid,origplayer);
	}
	for(auto i=possMove.begin();i!=possMove.end();i++)
	{
		playmove(*i,playerid);
		depth++;
		if(playerid==origplayer)
		{
			score=-4500;
			local_score=minmax(3-playerid,origplayer,alpha,beta);
			if (local_score>=0) positivity+=0.1;
			else positivity-=0.1;
			if(local_score>score)
			{
				score=local_score;
			}
			if(alpha<score)
			{
				alpha=score;
			}
			if(beta<=alpha)
			{
				this->board = b1->deepCopy();
				depth--;
				return score+positivity;
			}
		}
		else
		{
			score=4500;
			local_score=minmax(3-playerid,origplayer,alpha,beta);
			if (local_score>=0) positivity+=0.1;
			else positivity-=0.1;
			if(local_score<score)
			{
				score=local_score;
			}
			if(score<beta)	beta=score;
			if(beta<=alpha)
			{
				this->board = b1->deepCopy();
				depth--;
				return score+positivity;
			}
		}
		this->board = b1->deepCopy();
	}
	return score+positivity;
	
}

vector<Move> Game::getMove(int playerid){
	this->origBoard = this->board->deepCopy();
	//get the next move by min max or something
	
	double score=-3000.0,local_score,alpha=-4000,beta=4000;
	poss_moves(playerid);
	vector<vector<Move>> possMove;
	possMove=possibleMoves;
	auto best_move=possMove.begin();
	for(auto i=possMove.begin();i!=possMove.end();i++)
	{
		playmove(*i,playerid);
		local_score=minmax(3-playerid,playerid,alpha,beta);
		if(local_score>score)
		{
			score=local_score;
			best_move=i;
		}
		this->board = this->origBoard->deepCopy();
	}
	
	return (*best_move);
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

Node Game::getNode(int row,int coloumn){
	if((row<11)&&(coloumn<11)){
		Node n = this->board->nodes[row][coloumn];
		if (n.valid){
			return n;
		}
	}
	
	cerr << "Trying to get an Invalid or out of range Node" << endl;
	exit(1);
}

void Game::setNode(int row,int coloumn,Node node){
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

pair< pair<int,int>, pair<int,int>> Game::removableMarkers(int color,int &marks,int pos[121][2]){
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

int Game::poss_moves(int color){
	if(this->flag)
	{
		cerr<<"nodes not set for possiblemoves"<<endl;
		exit(1);
	}
	//else
	possibleMoves.clear();
	int i,j;
	vector<Move> poss_move;		//single possible move
	// int whiteRings=0,blackRings=0,whiteringPos[5][2],blackringPos[5][2];		//considering white as player1 black as player2
	int whiteMarks=0,blackMarks=0,whiteMarkPos[121][2],blackMarkPos[121][2];	//no issues of this outside this class
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			if(this->board->nodes[i][j].valid==0)
				continue;
			//else
				
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
				
			}
			
	}
	
	//is it possible that we need to remove markers before move
	pair < pair<int,int> , pair<int,int> > remove;
	
	switch(color){
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
