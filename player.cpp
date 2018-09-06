#include<iostream>
#include<string>

using namespace std;

int main( int argc, char **argv){


    int player, n, time;

    //Firstly , server_string is forwarded to process
    //server string has : <player_id> <num_rings> <time> 
    // string server_string;
    // cin >> server_string;
    // getline(cin, server_string);
    // cout << server_string;
    cin >> player;
    cin >> n;
    cin >> time;
    cout << "P 5 7"<< endl;

    string move;

    while(true){
        
        // This will wait till a move from opponent
        // cin >> move;
        getline(cin, move);

        // why is blank output coming twice ?
        //decompose move according to game.cpp and play move
        cerr << "Opponent played : " <<  move << endl;
        // cout << move << endl;

        // cout << "P 4 7"<< endl;



    }
    return 0;
}