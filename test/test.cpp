#include <iostream>

using namespace std;

pair<int, int> mapping[6][36];
pair<int, int> reverseMapping[11][11];


void formMap( int boardSize  ) {
    /*
    Docs Keeping in mind boardsize = 5
    Rows and Columns from 0...b....2*b 
    Hexagons number (h) from 0 ... b 
    and pos from 0 .... 6*h - 1 
    */
    int central = boardSize; // central square 
    int minlimit = 0, maxlimit = 0;
    int itr1 = 0, itr2 = 0;
    int limitcounter = 0;

    // tc.insert( make_pair(0, 0), make_pair(central, central) );
    
    mapping[0][0] = make_pair(central, central);
    reverseMapping[central][central] = make_pair(0, 0);

    for(int hexNum = 1 ; hexNum <= boardSize; hexNum++ ){
        
        //these must be repeated (hexNum+1) times
        minlimit = central - hexNum;
        maxlimit = central + hexNum;
        
        itr1 = central;
        itr2 = maxlimit;
        limitcounter = hexNum + 1 ;

        int counter1 = limitcounter;
        int counter2 = limitcounter;
        int dir1 = +1; 
        int dir2 = -1;

        for(int pos = 0 ; pos < 6 * hexNum; pos++){
        
            mapping[hexNum][pos] = make_pair(itr1, itr2);
            reverseMapping[itr1][itr2] = make_pair(hexNum, pos);

            if(itr1 == minlimit){
                counter1--;
                if(counter1 == 0){
                    dir1 = +1; counter1 = limitcounter; itr1 += dir1;
                }
            }else if(itr1 == maxlimit){
                counter1--;
                if(counter1 == 0){
                    dir1 = -1; counter1 = limitcounter; itr1 += dir1;
                }
            }else{
                itr1 += dir1;
            }

            if(itr2 == minlimit){
                counter2--;
                if(counter2 == 0){
                    dir2 = +1; counter2 = limitcounter; itr2 += dir2;
                }
            }else if(itr2 == maxlimit){
                counter2--;
                if(counter2 == 0){
                    dir2 = -1; counter2 = limitcounter; itr2 += dir2;
                }
            }else{
                itr2 += dir2;
            }

        }
    }
} 

int main(int argc, char** argv){

    int boardSize = 5;

    formMap(boardSize);

    pair<int, int> p = mapping[0][0];

    cout << " ( 0, 0 ) -> ( " << p.first << ", "<< p.second << " ) " << endl;

    for(int hexNum = 1 ; hexNum <= boardSize; hexNum++ ){

        cout << " ----------------------- " << endl;

        for(int pos = 0 ; pos < 6 * hexNum; pos++){
            pair<int, int> p = mapping[hexNum][pos] ;
            cout << " ( "<< hexNum << ", " << pos << " ) -> ( " << p.first << ", "<< p.second << " ) " << endl;

        }
    }


    return 0;
}