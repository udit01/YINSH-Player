#include<utils.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

void split(const std::string& str, Container& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}

static vector<Move> Move::convertToStd(string move){
    vector<string> splices;
    split(move, splices);

}

static string Move::convertToHexagonal( vector<Move> moves){

}