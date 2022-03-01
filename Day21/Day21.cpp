#include <iostream>
#include <fstream>
#include <regex>
#include "../utils/utils.h"

using namespace std;

pair<int, int> readFile(string filename){
    ifstream myfile (filename);
    int player_1=0, player_2=0;

    if (myfile.is_open())
    {
        string line;
        while ( getline(myfile, line) )
        {
            // Player 1 starting position: 4
            const regex r("Player (-?\\d*) starting position: (-?\\d*)");  
            smatch result;

            // can't add numbers to a pair iteratively
            // result = ["Player 1 starting position: 4", "1", "4"]
            if (regex_search(line, result, r)) {
                if(result[1]=='1'){
                    player_1 = stoi(result[2]);
                }
                else{
                    player_2 = stoi(result[2]);
                }
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return make_pair(player_1, player_2);
}

int main() {
    pair<int, int> positions = readFile("input.txt");
    printPair(positions);

    return 0;
}