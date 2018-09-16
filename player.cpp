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
    // string server_string;
    // cin >> server_string;
    // getline(cin, server_string);
    // cout << server_string;
    cin >> player;
    cin >> n;
    cin >> time;
    // cerr<<"inputs taken well"<<endl;
    // cout << "P 5 7"<< endl;
    timing *timer=new timing(time);
    // cerr<<"timer object created"<<endl;
	Game* game= new Game(n,timer,argc,argv); //creates an object of game class
    // cerr<<"game object created"<<endl;
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
        cerr<<opp_move<<endl;
	    timer->resume();

        cerr << "Inside CPP file : Opponent played : " <<  opp_move << endl ;


        game->playmove(convertToStd(opp_move), 3 - player);// a call to a fuction of Game

        game->board->printBoard();
        my_move = convertToHexagonal(game->getMove(player));
        
        cout << my_move;  


    }
    return 0;
}
