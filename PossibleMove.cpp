#include<move.h>

void Move::init()
{
	int i;
	flag=0;
	Max_moves=10;
	Max_length_move=30;	//using long complete notation
	moves=(char **)malloc(Max_moves*sizeof(singlemove));
	for(i=0;i<Max_moves;i++)
		moves[i]=NULL;		//set all singlemove pointers to null;
	totalMoves=0;
	currmove=0;
}

Move::Move()
{
	init();
}
