#include <iostream>
#include <assert.h>
#include "game.h"
#include "utils.h"

Game::Game(){
	time=120;
}
void Game::setWeights(int argc, char **argv)
{
	if(argc<2)
    {
        weights[0]=100; //winning score
        weights[1]=1;   //worsness of opponents winning over our winning
        weights[2]=1;   //ring differnce weight
        weights[3]=0.01;    //marker difference weight
        weights[4]=0.1; //winning probablity on a side
    }
    else
    {
		ifstream readfile;
		readfile.open(argv[1]);
		if(!readfile)
		{
		weights[0]=100; //winning score
		weights[1]=1;   //worsness of opponents winning over our winning
		weights[2]=1;   //ring differnce weight
		weights[3]=0.01;    //marker difference weight
		weights[4]=0.1; //winning probablity on a side
		}
		else
		{
			int i;
			string w;
			for(i=0;i<5;i++)
			{
				getline(readfile,w);
				weights[i]=stod(w);
			}
		}
		readfile.close();
    }
}
Game::Game(int n,timing *timer,int argc, char **argv){
	this->time=time;
	// N is board size, wil go inside next line when we're ready 
	this->board = new Board(5);
	this->setWeights(argc,argv);
	this->timer=timer;
	// this->pm = new PossMove(this->b->nodes);
}

void Game::changeLine(int player, int r1, int c1, int r2, int c2, bool remove){
	
	//process current node seperately and don't include that in for loops

	//assert that unequal blocks
	assert( !( (r1 == r2) && (c1 == c2) ));

	//assert start and end points valid
	Node* n = &(this->board->nodes[r1][c1]);
	
	assert(n->valid);
	if(remove){
		//player is being checked in the loops so no need to check again 
		// assert(n->color == player);
		assert(n->ring == player); 
		n->color = 0;
		//also check if ring pos is the appropriate thing ?
	}
	n = &(this->board->nodes[r2][c2]);
	
	assert(n->valid);

	
	if(remove){
			//because we're including both of edge points
			// differnece in atleast 1 of them must be above removal threhold
			assert((abs(r2 - r1) >= 4) || (abs(c2 - c1) >= 4));
			//and check all between them are colored;
	}

	int minIdx, maxIdx;
	
	//same row , or same col jump or both changeing equally
	if(r1 == r2){
		minIdx = (c1 > c2) ? c2:c1;
		maxIdx = (c2 + c1) - minIdx;
		
		
		for(int i = minIdx+1 ; i <= maxIdx; i++){
		
			n = &(this->board->nodes[r2][i]);

			assert(n->valid); // all should be valid by default
			if(remove){
				// if any one node doesn't satisfy this then this line was not removable
				assert(n->color == player);
				n->color = 0;
			}
			else{
				n->color = (n->color == 0) ? 0 : (3 - n->color); // Flipping the colors in the path
			}
		}
		
	}else if(c1 == c2){
		minIdx = (r1 > r2) ? r2:r1;
		maxIdx = (r2 + r1) - minIdx;
		
		for(int i = minIdx+1; i <= maxIdx; i++){
		
			n = &(this->board->nodes[i][c2]);

			assert(n->valid); // all should be valid by default
			if(remove){
				assert(n->color == player);
				n->color = 0;
			}
			else{
				n->color = (n->color == 0) ? 0 : (3 - n->color); // Flipping the colors in the path
			}

		}
	}else{
		//both iterate

		assert(abs(r1-r2) == abs(c1-c2));
		int dir1 = (r2 - r1)/(abs(r2-r1));
		int dir2 = (c2 - c1)/(abs(c2-c1));
		//other complex logic here depeding on signs of r1-r2 and c2-c1
		int j = c1 ;
		j+= dir2;
		
		for(int i = r1+dir1; i != r2; i+=dir1){
			j += dir2;
			n = &(this->board->nodes[i][j]);

			assert(n->valid); // all should be valid by default
			if(remove){
				assert(n->color == player);
				n->color = 0;
			}
			else{
				n->color = (n->color == 0) ? 0 : (3 - n->color); // Flipping the colors in the path
			}

		}
	}

	if(remove){
		//change the ring position 
		n = &(this->board->nodes[r1][c1]);
		n->ring = 0;
		n = &(this->board->nodes[r2][c2]);
		n->ring = player;

		for(int k = 0 ; k < 5 ; k++ ){
			if((this->board->ring_pos[player-1][k][0] == r1 ) && (this->board->ring_pos[player-1][k][1] == c1) ){
				
				this->board->ring_pos[player-1][k][0] = r2; 
				this->board->ring_pos[player-1][k][1] = c2;

			}
		}

	}
}	

void Game::removeRing(int player, int r, int c){
	
	//Rings remaining are the rings in hand, so in the middle game they'll be zero
	// assert(this->board->ringsRem[player-1]>0);
	
	//what if >= 3 ?
	// assert(this->board->ringsDone[player-1]>3);
	Node* n = &(this->board->nodes[r][c]);
	assert(n->valid);
	assert(n->ring == player);

	//erase ring
	n->ring = 0;

	//erase ring from position base
	for(int k = 0 ; k < 5 ; k++ ){
			if((this->board->ring_pos[player-1][k][0] == r ) && (this->board->ring_pos[player-1][k][1] == c) ){
				this->board->ring_pos[player-1][k][0] = 0; 
				this->board->ring_pos[player-1][k][1] = 0;
			}
	}

	//counter inc/dec of reamaining and done rings
	// this->board->ringsRem[player-1]--;
	this->board->ringsDone[player-1]++;

}

void Game::placeRing(int player, int r, int c){
	
	//there must be something in hand to place
	assert(this->board->ringsHand[player-1] > 0);
	
	//the position where you want to place must be valid and empty
	Node* n = &(this->board->nodes[r][c]);
	assert(n->valid);
	assert(n->ring == 0);
	
	//place the ring
	n->ring = player;
	//dec remaining rings
	this->board->ringsHand[player-1]--;
	//log coordinates of the ring
	//iteraing from opposite direction may be hugely benifical in other parts, because fist ring is preffered for evey movement 
	// and if first ring is outermost then faster move generation
	for(int i = 0 ; i < 5 ; i++){
		//insert the ring at the first free position 
		if((this->board->ring_pos[player-1][i][0] == 0) && (this->board->ring_pos[player-1][i][1] == 0) ){
			this->board->ring_pos[player-1][i][0] = r;
			this->board->ring_pos[player-1][i][1] = c;
			break;
		}
	}

}

void Game::playmove(vector<Move> move, int player){ 
	/*We get a player's  move and we have to play it*/
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

	//play the move in the game
	for(std::vector<Move>::iterator it = move.begin(); it != move.end(); ++it) {
		
		type = it->moveType; row = it->row; col = it->col;
		assert(this->board->nodes[row][col].valid);

		switch(type){
			case 0: /* Placing a ring */
				this->placeRing(player, row, col);
				// this->board->nodes[row][col].ring = me;
				break;
			case 1: /* Selecting a ring(and therefore putting the marker) */
				// Put the marker on this node 
				this->board->nodes[row][col].color = player;
				//set ring start row and column
				rsr = row; rsc = col;
				break;
			case 2: /*Move ring comes after selection*/
				assert( (rsr!= 0) && (rsc!=0)); //weaker assert condition
				//assert somehow that ringstartpos was evaluated
				this->changeLine(player, rsr, rsc, row, col, false);
				break;
			case 3: /*RS may come standalone*/
			//check the rings are in order
				//set ring start row and column
				rsr = row; rsc = col;
				break;
			case 4: /*RE ring comes after selection*/
				assert( (rsr!= 0) && (rsc!=0)); //weaker assert condition
				//assert somehow that ringstartpos was evaluated
				this->changeLine(player, rsr, rsc, row, col, true);
				break;
			case 5: /*X is remove ring do after appropirate checking*/
				this->removeRing(player, row, col);
				break;
			default:
				//cerr << "Some error in move type " << type << endl;
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
	if(this->board->ringsDone[origplayer-1]==3) return weights[0];	//our winning
	if(this->board->ringsDone[2-origplayer]==3) return -1*(weights[1]*weights[0]);	//worsness of oppnonent's win
	//else
	score=(this->board->ringsDone[playerid-1]-this->board->ringsDone[2-playerid])*weights[2];//differnce in rings
	score+=weights[3]*(markers[playerid-1]-markers[2-playerid]);//marker difference;
	if(playerid==origplayer)
	return score;
	else
	return -1*(weights[1]*score);
}

double Game::minmax(int playerid,int origplayer,int alpha,int beta){
	Board* b1 = this->board->deepCopy();
	static int depth=0;
	if (depth==1)
	{
		depth=1;
		return evaluate(playerid,origplayer);
	}
	//get the next move by min max or something
	vector<vector<Move>> possMove=this->allPossibleMoves(playerid);
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
			if (local_score>=0) positivity+=weights[4];
			else positivity-=weights[4];
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
			if (local_score>=0) positivity+=weights[4];
			else positivity-=weights[4];
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
	cerr<<timer->getRemTime()<<endl;
	//if only 1 possible move then play that move, don't evaluate or anything just do it!
	vector<vector<Move>> possiblities = this->allPossibleMoves(playerid);
	if(possiblities.size() == 0){
		//cerr << "NO possible moves for player : "<< playerid <<" DID we win ? Change exit to empty in that case"<< endl;
		//don't exit instead return some sort of blank as we may have won
		vector<Move> emp;
		return emp;
		// exit(1);
	}else if(possiblities.size() == 1){
		this->playmove(possiblities[0], playerid);
		return possiblities[0];
	}
	// else
	// Do something else
	cerr<<"Inside get move possiblities greater than 1"<<endl;
	this->origBoard = this->board->deepCopy();
	//get the next move by min max or something
	
	double score=-3000.0,local_score,alpha=-4000,beta=4000;
	vector<vector<Move>> possMove=this->allPossibleMoves(playerid);
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

vector<Move> Game::placeHandRing(int player){
	// to place hand ring optimally
	// attempt to place ring at central positions and then check sourrounding 
	assert(this->board->ringsHand[player-1] > 0);

	vector<Move> seq;
	int coord[2] = {0,0};
	
	getStd(0, 0, coord);
	if(this->board->nodes[coord[0]][coord[1]].ring == 0){
		//place ring at the center if possible and return
		seq.push_back(Move(0, coord[0], coord[1]));
		return seq;
	}

	for(int hexNum = 1; hexNum <= 5; hexNum++){
		for(int pos = 0; pos < 6 * hexNum ; pos++){
			getStd(hexNum, pos, coord);
			if(this->board->nodes[coord[0]][coord[1]].ring == 0){
				//place ring at this coordinate if possible and return
				seq.push_back(Move(0, coord[0], coord[1]));
				return seq;
			}
		}
	}

	// if unable then to find such a sequence, return an empty vector
	return seq	;
}

vector<Move> Game::makeContigousMove(int player, int r1, int c1, int r2, int c2){
	vector<Move> seq;
	
	// push an RS move
	seq.push_back(Move(3, r1, c1));

	// push an RE move
	seq.push_back(Move(4, r2, c2));

	//select a ring to remove and remove it 
	//changing the order of i could improve greatly

	for(int i = 0; i < 5; i++){
		int r = this->board->ring_pos[player-1][i][0];
		int c = this->board->ring_pos[player-1][i][1];
		if((r==0)&&(c==0)){
			// an invalid ring to remove
			continue; 
		}
		else{
			seq.push_back(Move(5, r, c));
			break;
		}
	}

	return seq;
}

vector<Move> Game::checkContigousMarkers(int player){
	//to check for max possible markers

	//check row-wise , column wise and then along 3rd dim
	int startNodeRow = 0, startNodeCol = 0; //as the 0th and 10th row cant have contigous markers
	int endNodeRow = 0, endNodeCol = 0; //as the 0th and 10th row cant have contigous markers
	bool cont = false;
	int thresh = 4; //as includsive of start and end
	int save[2][2]; // 0-start, 1-end

	Node *n;
	// Checking each row 
	for(int row = 1; row <= 9 ; row++){
		cont = false; 
		startNodeRow = row; startNodeCol = 0; //as the 0th and 10th row cant have contigous markers
		endNodeRow = row; endNodeCol = 0;
		
		// row doen't change in here
		for(int col = 0; col <= 10 ; col++){
			n = &(this->board->nodes[row][col]);
			//there will be a continous stream of valid nodes
			if(n->valid){
				if(n->color == player){
					if(!cont){//first occurence
						startNodeCol = col;
					}
					endNodeCol = col; 
					cont = true;
				}
				else{//stream break
					if((endNodeCol-startNodeCol) >= thresh){
						save[0][0] = startNodeRow; save[0][1] = startNodeCol; save[1][0] = endNodeRow; save[1][1] = endNodeCol;
						//get the required move and return ? OR save this as a possibility and then decide 
						return this->makeContigousMove(player, startNodeRow, startNodeCol, endNodeRow, endNodeCol);
					}
					cont = false;
				}
			}
		}
	}


	// Checking each column 
		//as the 0th and 10th col cant have contigous markers
	for(int col = 1; col <= 9 ; col++){
		cont = false; 
		startNodeCol = col; startNodeRow = 0; 
		endNodeCol = col; endNodeRow = 0;
		
		// col doesn't change in here
		for(int row = 0; row <= 10 ; row++){
			n = &(this->board->nodes[row][col]);
			//there will be a continous stream of valid nodes
			if(n->valid){
				if(n->color == player){
					if(!cont){//first occurence
						startNodeRow = row;
					}
					endNodeRow = row; 
					cont = true;
				}
				else{//stream break
					if((endNodeRow-startNodeRow) >= thresh){
						save[0][0] = startNodeRow; save[0][1] = startNodeCol; save[1][0] = endNodeRow; save[1][1] = endNodeCol;
						//get the required move and return ? OR save this as a possibility and then decide 
						return this->makeContigousMove(player, startNodeRow, startNodeCol, endNodeRow, endNodeCol);
					}
					cont = false;
				}
			}
		}
	}

	// Checking each 3rd Dimension 
	/*
	Start form { [5][0], [4][0], ... [0][0], [0][1], .... [0][5] } 
	and increase both row and col from these to get the dimension
	The end's pos have 4 along so skip them from counting
	*/

	//left index loop
	for(int left_start = 4; left_start >= 0 ; left_start--){
		int row = left_start;
		int col = 0;

		cont = false; 
		startNodeRow = row; startNodeCol = col; //as the 0th and 10th row cant have contigous markers
		endNodeRow = row; endNodeCol = col;
		
		for(int k = 0; k <= 10 ; k++){
			if((row<11)&&(col<11)){
				n = &(this->board->nodes[row][col]);
				//there will be a continous stream of valid nodes
				if(n->valid){
					if(n->color == player){
						if(!cont){//first occurence
							startNodeRow = row; startNodeCol = col;
						}
						endNodeRow = row; endNodeRow = col; 
						cont = true;
					}
					else{//stream break
						// both diff will be same
						if((endNodeRow-startNodeRow) >= thresh){
							save[0][0] = startNodeRow; save[0][1] = startNodeCol; save[1][0] = endNodeRow; save[1][1] = endNodeCol;
							//get the required move and return ? OR save this as a possibility and then decide 
							return this->makeContigousMove(player, startNodeRow, startNodeCol, endNodeRow, endNodeCol);
						}
						cont = false;
					}
				}
			}else{
				break;
			}
			row++;	col++;
		}
	}
	//RIGHT index loop // 0 already done
	for(int right_start = 1; right_start <= 4 ; right_start++){
		int row = 0;
		int col = right_start;

		cont = false; 
		startNodeRow = row; startNodeCol = col; //as the 0th and 10th row cant have contigous markers
		endNodeRow = row; endNodeCol = col;
		
		for(int k = 0; k <= 10 ; k++){
			if((row<11)&&(col<11)){
				n = &(this->board->nodes[row][col]);
				//there will be a continous stream of valid nodes
				if(n->valid){
					if(n->color == player){
						if(!cont){//first occurence
							startNodeRow = row; startNodeCol = col;
						}
						endNodeRow = row; endNodeRow = col; 
						cont = true;
					}
					else{//stream break
						// both diff will be same
						if((endNodeRow-startNodeRow) >= thresh){
							save[0][0] = startNodeRow; save[0][1] = startNodeCol; save[1][0] = endNodeRow; save[1][1] = endNodeCol;
							//get the required move and return ? OR save this as a possibility and then decide 
							return this->makeContigousMove(player, startNodeRow, startNodeCol, endNodeRow, endNodeCol);
						}
						cont = false;
					}
				}
			}else{
				break;
			}
			row++;	col++;
		}
	}

}

vector<Move> Game::spawnRing(int player, int r1, int c1, int r2, int c2){
	vector<Move> seq;

	seq.push_back(Move(1, r1, c1));
	seq.push_back(Move(2, r2, c2));
	
	Board* board_ = this->board->deepCopy();
	
	//makes deecopy of the vector
	vector<Move> other(seq);

	while(this->board->ringsDone[player-1]<3){

		//play this move and check for contigous markers afterword
		this->playmove(other, player);
		other = this->checkContigousMarkers(player);
		
		if(other.size()>0){
			seq.insert(seq.end(), other.begin(), other.end());
		}
		else{
			break;
		}
		
	}
	// if(this->board->ringsDone[player-1] >= 3){
		
	// }
	this->board = board_;
	return seq;
	
}

vector<vector<Move>> Game::perturbRing(int player, int r, int c){

	//assert a valid node and RING ?
	Node *n = &(this->board->nodes[r][c]);
	assert(n->valid);
	assert(n->ring == player);
	assert(n->color == 0);
	// After every possiblity, you'll have to make a copy of board play the move
	// and check if RS RE , some row forming or not ?

	// 6 directions to move along, move till something comes up
	int directions[6][2] ={ {0,1}, {0,-1},
							{1,0}, {-1,0},
							{1,1}, {-1,-1} };

	int row = r, col = c;
	bool gotMarker = false;
	int lastMarkerRow, lastMarkerCol;


	vector<vector<Move>> perturbations;

	for( int k = 0; k < 6 ; k++ ){
		//Running variables
		gotMarker = false;
		row = r; col = c;
		lastMarkerRow = row, lastMarkerCol= col; // dummy marker, not actually a marker here
		//max possible displacement is 11
		for(int counter = 0; counter <= 11; counter++){

			row += directions[k][0]; col += directions[k][1];

			if((row<0)||(row>10)||(col<0)||(col>10)){
				break; 
				//as new increments mean only disaster, 
				//break off that direction loop
			}

			//Do for each valid node , generate possiblities
			n = &(this->board->nodes[row][col]);
			if(n->valid){
				if(n->ring != 0){
					// just the possibilites till now were possible, not after this ring encounter
					break;
				}
				if(n->color != 0){
					//Encountered a marker 
					if(((row-directions[k][0])==lastMarkerRow)&&((col-directions[k][1]) == lastMarkerCol)){
						// safe, as found next contigous marker
						lastMarkerRow = row; lastMarkerCol = col;
						// but we cannot move here, we can only move outside
						// therefore continue
					}
					else if((lastMarkerRow == r)&&(lastMarkerCol == c)){
						// this is the first true marker encountered after some gap,
						lastMarkerRow = row; lastMarkerCol = col;
						// go to just one more unit(if possible) to make possiblites then give up
						// 
					}
					else{
						//some other marker(discontigous) was encounterd and this is another
						break;///should have broken at that previous time
					}
				}else{
					//marker not found then check the status of last marker thingy and make it into a possiblility
					// This will spawn ring, check for contigous rings recursively etc
					perturbations.push_back(this->spawnRing(player, r, c,row, col));
					
					if((lastMarkerRow == r)&&(lastMarkerCol == c)){
						// continue, keep spawning,  do nothing, 
					}
					else if(((row-directions[k][0])==lastMarkerRow)&&((col-directions[k][1]) == lastMarkerCol)){
						// last point was a marker, therefore end spawning here
						break;
					}
					
				}
				
			}

		}
	}

	return perturbations;
}

vector<vector<Move>> Game::allPossibleMoves(int player){

	vector<vector<Move>> possibilities;

	vector<Move> ringsPlacingSeq;

	if(this->board->ringsHand[player-1] > 0){
		ringsPlacingSeq = this->placeHandRing(player);
	}

	if(!ringsPlacingSeq.empty()){
		possibilities.push_back(ringsPlacingSeq);
		return possibilities;
	}

	// Otherwise it's empty and move on to the next step
	if(this->board->ringsDone[player-1] >= 3){
		//return the empty vector
		return possibilities;
	}


	// call if all 5 rings placed from hand to board and Done rings is still < 3

	//will return the 1st max sequence found, otherwise NULL
	vector<Move> ringRemovalSeq = this->checkContigousMarkers(player);
	
	//returns 'a' contigous sequence if exists

	//somehow check if it's a valid and not null case
	if (!ringRemovalSeq.empty()){
		//if not empty then make
		Board* boardSave = this->board->deepCopy();
		
		//this modified this.board
		this->playmove(ringRemovalSeq, player);

		vector<vector<Move>> deeperPoss = this->allPossibleMoves(player);

		//prepend ringRemovalSeq to each vector to make and the return the possibilites vector
		for(vector<vector<Move>>::iterator it = deeperPoss.begin() ; it != deeperPoss.end() ; it++ ){
			//theis deepcopies the ringRemovalSeq
			vector<Move> temp(ringRemovalSeq); 
			//this inserts the deepPossiblites vector after (copy of) ringRemovalSeq vector and returns the final vector of vectors 
			temp.insert(temp.end(), it->begin(), it->end());
			possibilities.push_back(temp);
		}

		//now return the board to original state
		this->board = boardSave;
		//and return the possiblites ? without checking other normal moves because that won't be required
		return possibilities;
	}

	// if multiple contigous markers, then call possible moves again after removing the first set,
	// as it could or couldn't disturb the 2nd config
	

	//if upper is NULL then do this --- for each of the ring, check status of possible moves 
	// vector<vector<Move>> ringMoves;

	// //cerr << "REACHED ring moves stage, for now returning NULL if no other move: " << endl;
	
	//UNCOMMENT FOLLOWING TO INCLUDING RING MOVE POSSIBILITIES
	
	for(int ringNumber = 0; ringNumber < 5; ringNumber++){
		int r = this->board->ring_pos[player-1][ringNumber][0];
		int c = this->board->ring_pos[player-1][ringNumber][1];
		if((r==0)&&(c==0)){
			continue; //as this index ring is not on board
		}

		vector<vector<Move>> temp = this->perturbRing(player, r, c);
		// call a function for each ring, returning a vector of vector of moves  possible and append them to the possibilites set 
		possibilities.insert(possibilities.end(), temp.begin(), temp.end());
	}

	return possibilities;
}
