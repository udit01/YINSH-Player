/*
    board.cpp
    Author : udit01
*/

#include"board.h"

Node* Node::deepCopy(){
    Node* n = new Node();
    
    n->row = this->row;
    n->col = this->col;
    n->color = this->color;
    n->ring = this->ring;
    n->valid = this->valid;

    return n;
}

Board* Board::deepCopy(){
    Board *b = new Board();
    b->boardSize   = this->boardSize;
    
    for(int i = 0; i < 5; i++){
        if(i < 2){
            b->ringsHand[i]  = this->ringsHand[i];
            b->ringsDone[i] = this->ringsDone[i];
        }
        b->ring_pos[0][i][0] = this->ring_pos[0][i][0];
        b->ring_pos[0][i][1] = this->ring_pos[0][i][1];
        b->ring_pos[1][i][0] = this->ring_pos[1][i][0];
        b->ring_pos[1][i][1] = this->ring_pos[1][i][1];
    }

    int range = 2*this->boardSize + 1;
    
    b->nodes = new Node*[range];

    //probably the below for loop is unreuired
    for(int i = 0; i < range; i++){
        b->nodes[i] = new Node[range];
    }

    for(int i = 0; i < range; i++){
        for(int j = 0; j < range; j++){
            b->nodes[i][j] = *(this->nodes[i][j].deepCopy());
        }
    }
    
}

Board::Board(){
    //empty constructor, just a placeholder
}

Board::Board(int boardSize){
    // rings from 0...b
    // rows and columns from 0 ... 2*b
    this->boardSize = boardSize;
    // cerr<<"came into board constructor"<<endl;
    int range = 2*boardSize + 1;
    this->nodes = new Node*[range];
    for(int i = 0; i < range; i++){
        this->nodes[i] = new Node[range];
    }
    // cerr<<"nodes of range created"<<endl;
    //marking validity of nodes
    this->markValidity(); // currently only for size 5

    this->ringsHand[0] = 5; this->ringsDone[0] = 0;
    this->ringsHand[1] = 5; this->ringsDone[1] = 0;


    // initialize to zeros although not zeros, better than random garbage
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 2; k++){
                this->ring_pos[i][j][k] = 0;
            }
        }
    }
}

void Board::markValidity(){
    //doing only for board size 5 right now 

    int range = (2*this->boardSize) + 1;
    //nodes are from 0....range-1
    int start = 0, end = 0;
    for(int i = 0; i < range; i++){
        switch(i){
            case 0 : start = 1; end = 4 ; break;
            case 1 : start = 0; end = 6 ; break;
            case 2 : start = 0; end = 7 ; break;
            case 3 : start = 0; end = 8 ; break;
            case 4 : start = 0; end = 9 ; break;
            case 5 : start = 1; end = 9 ; break;
            case 6 : start = 1; end = 10; break;
            case 7 : start = 2; end = 10; break;
            case 8 : start = 3; end = 10; break;
            case 9 : start = 4; end = 10; break;
            // case 10: start = 6; end = 9 ; break;
            default: start = 6; end = 9 ; //for i == 10
        }
        for(int j = 0; j < range; j++){
            // if( (j>=start) && (j<=end) ){
            //     this->nodes[i][j].valid = true ;
            // }else{
            //     this->nodes[i][j].valid = false;
            // }
            this->nodes[i][j].valid = ((j>=start) && (j<=end)) ? true : false;
        }
    }
}

void Board::printBoard()
{

    cerr  << "********************************************" << endl;
    cerr  << "         PRINTING BOARD START               " << endl;
    cerr  << "********************************************" << endl;

    int i,j;
    cerr<<"rings hand [0] = "<<ringsHand[0]<<endl;
    cerr<<"rings hand [1] = "<<ringsHand[1]<<endl;
    cerr<<"rings done [0] = "<<ringsDone[0]<<endl;
    cerr<<"rings done [0] = "<<ringsDone[0]<<endl;
    cerr<<"ring positions for 0 : "<<endl;
    for(i=0;i<5;i++)
        cerr<<ring_pos[0][i][0]<<" "<<ring_pos[0][i][1]<<endl;
    cerr<<"ring positions for 1 : "<<endl;
    for(i=0;i<5;i++)
        cerr<<ring_pos[1][i][0]<<" "<<ring_pos[1][i][1]<<endl;
    cerr<<"printing nodes in format \n validity color ring"<<endl;
    for(i=0;i<11;i++)
    {
        for(j=0;j<11;j++)
        {
            string str; 
            if(!nodes[i][j].valid){
                str = "   ";
            }
            else if(nodes[i][j].ring == 0){
                if(nodes[i][j].color == 0){
                    str = "_._";
                }
                else{
                    str = (nodes[i][j].color == 1) ? "_1_" : "_2_" ;
                }
            } 
            else {
                if(nodes[i][j].color == 0){
                    str = (nodes[i][j].ring == 1) ? "_r1_" : "_r2_" ;
                }
                else{
                    //both ring and marker // they will be of same color ?
                    str = (nodes[i][j].ring == 1) ? "_R1_" : "_R2_" ;
                }
            }
        
            // cerr<<"node"<<i<<" "<<j<<endl;
            // cerr<<nodes[i][j].valid<<" "<<nodes[i][j].color<<" ";
            // cerr<<nodes[i][j].ring<<endl;
            cerr << str << " ";
        }
        cerr << endl;
    }


    cerr  << "********************************************" << endl;
    cerr  << "           PRINTING BOARD END               " << endl;
    cerr  << "********************************************" << endl;

}


