#include<PossibleMove.h>

void PossMove::init()
{
	flag=1;
	totalMoves=0;
	currmove=0;
}

PossMove::PossMove()
{
	init();
}

possMove::PossMove(Node **curr_nodes)
{
	init();
	int i,j;
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
			nodes[i][j]=curr_nodes[i][j];
	}
	flag=0;
}

Node possMove:: getNode(int row,int coloumn)
{
	if((row<11)&&(coloumn<11))
		return nodes[row][coloumn];
	//else
	cerr<<"getting node out of range"<<endl;
	exit(1);
}

void possMove:: setNode(int row,int coloumn,Node node)
{
	if((row<11)&&(coloumn<11))
		nodes[row][coloumn]=node;
	//else
	cerr<<"setting node out of range"<<endl;
	exit(1);
}
