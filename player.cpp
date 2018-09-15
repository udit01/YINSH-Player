#include<iostream>
#include<string>
#include<fstream>
#include "utils.h"
#include "game.h"

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
    cin >> player;
    cin >> n;
    cin >> time;

    // cout << "P 5 7"<< endl;

	Game* game= new Game(player,n,time,weights); //creates an object of game class
    
    string opp_move,my_move;
    
    if (player == 1){
        my_move = convertToHexagonal(game->getMove(1));
        cout << my_move;        
    }

    while(true){
        
        // This will wait till a move from opponent
        // cin >> move;
        getline(cin, opp_move);
	    
        game->playmove(convertToStd(opp_move), 3 - player);// a call to a fuction of Game

        my_move = convertToHexagonal(game->getMove(player));
        
        cout << my_move;  

        // why is blank output coming twice ?
        //decompose move according to game.cpp and play move
        cerr << "Opponent played : " <<  opp_move << endl;
        // cout << move << endl;
    }
    return 0;
}
