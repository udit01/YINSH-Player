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

pair < pair<int,int> , pair<int,int> > possMove::removableMarkers(int color,int marks,int pos[121][2])
{
	int i;
	for(i=0;i<marks;i++)
	{
		if(node[pos[i][0]][pos[i][1]].getcolor != color)
		{
			cerr<<"some error in marker colouring or finding markers"<<endl;
			exit(1);
		}
		// code to find removable markers is under process
	}
}

int possMove::poss_moves(int color)
{
	if(flag)
	{
		cerr<<"nodes not set for possiblemoves"<<endl;
		exit(1);
	}
	//else
	int i,j;
	int whiteRings=0,blackRings=0,whiteringPos[5][2],blackringpos[5][2];		//considering white as player1 black as player2
	int whiteMarks=0,blackMarks=0,whiteMarkPos[121][2],blackMarkPos[121][2];	//no issues of this outside this class
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			if(nodes[i][j].getvalid()==0)
				continue;
			//else
			switch(nodes[i][j].getring())
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
					switch(nodes[i][j].getcolor())
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
							cerr<<"markers not properly assigned to nodes"<<endl;
							exit(1);
					}
				default :
					cerr<<"rings not properly assigned to nodes"<<endl;
					exit(1);
			}
			
		}
	}
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
	
}



















