#include<fstream>
#include<iostream>

using namespace std;

int main( int argc, char **argv)
{
    if(argc<4)
    {
        cout<<"run in following format/n ./file loser.txt winner.txt resulting.txt"<<endl;
        exit(0);
    }
    //else
    ifstream loser(argv[1]);
    ifstream winner(argv[2]);
    ofstream result(argv[3]);
    string l,w;
    int i;
    double lw,ww,rw,diff;
    for(i=0;i<5;i++)
    {
        getline(loser,l);
        lw=stod(l);
        getline(winner,w);
        ww=stod(w);
        diff=ww-lw;
        rw=lw+(diff/10);
        result<<rw;
        result<<rw;
        result<<endl;
    }
    result.close();
    loser.close();
    winner.close();
}