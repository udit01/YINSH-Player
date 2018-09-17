#include<iostream>
#include<string>

#include "utils.h"
#include "game.h"
#include "timing.h"

using namespace std;

int main( int argc, char **argv){


    int player, n, time;
    double weights[5];
    //Firstly , server_string is forwarded to process
    //server string has : <player_id> <num_rings> <time> 
    
    cin >> player;
    cin >> n;
    cin >> time;
    string temp;
    getline(cin, temp);

    timing *timer=new timing(time);
	Game* game= new Game(n,timer,argc,argv); //creates an object of game class
    string opp_move,my_move;
    
    if (player == 1){
        my_move = convertToHexagonal(game->getMove(1));
        cout << my_move;        
    }

    while(true){
        
        // This will wait till a move from opponent
        // cin >> move;
        timer->stop();
        getline(cin, opp_move);
	    timer->resume();
        // cerr << "Inside CPP file : Opponent tried to play : " <<  opp_move  << "  : Calling play MOVE"<< endl ;



        game->playmove(convertToStd(opp_move), 3 - player);// a call to a fuction of Game

        // cerr << "Inside CPP file : PLAY move finished : Printing board" << endl ;

        // game->board->printBoard();

        // cerr << "Inside CPP file : Getting MY MOVE " << endl ;

        my_move = convertToHexagonal(game->getMove(player));
        
        // cerr << "Inside CPP file : I tried to play : " <<  my_move  << "  : COUTING "<< endl ;
        cout << my_move;  




    }
    return 0;
}
