/*
    board.cpp
    Author : udit01
*/

#include"board.h"

void Board::markValidity(){
    //doing only for board size 5 right now 

    int range = 2*this->boardSize + 1;
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
            if( (j>=start) && (j<=end) ){
                this->nodes[i][j].valid = true ;
            }else{
                this->nodes[i][j].valid = false;
            }
        }
    }
}

Board::Board(int boardSize){
    // rings from 0...b
    // rows and columns from 0 ... 2*b
    this->boardSize = boardSize;

    int range = 2*boardSize + 1;
    this->nodes = new Node*[range];
    for(int i = 0; i < range; i++){
        this->nodes[i] = new Node[range];
    }
    
    //marking validity of nodes
    this->markValidity(); // currently only for size 5

    this->p1ringsRem = 5; this->p1ringsDone = 0;
    this->p2ringsRem = 5; this->p2ringsDone = 0;
    
    // initialize to zeros although not zeros, better than random garbage
    for(int i = 0; i < 5; i++){
        this->white_pos[i][0] = 0;
        this->white_pos[i][1] = 0;
        this->black_pos[i][0] = 0;
        this->black_pos[i][1] = 0;
    }
}


