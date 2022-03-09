#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "../utils/utils.h"

using namespace std;

using GRID = vector<string>;

GRID readFile(string filename){
    string line;
    ifstream myfile (filename);
    GRID grid;

    if (myfile.is_open())
    {
        while ( getline(myfile, line) ){
            grid.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return grid;
}

pair<GRID, int> moveOnGrid(GRID &grid){
    pair<GRID, int> result(grid, 0);
    int maxy = grid.size();
    int maxx = grid[0].size();

    for(int i=0; i<maxy; i++){
        for(int j=0; j<maxx; j++){
            int src = (j+grid[i].size()-1)%grid[i].size();
            if(grid[i][j]=='.' && grid[i][src]=='>'){
                result.first[i][j] = '>';
                result.first[i][src] = '.';
                result.second++;
            }
        }
    }

    for(int i=0; i<maxy; i++){
        for(int j=0; j<maxx; j++){
            int src = (i+grid.size()-1)%grid.size();
            if(result.first[i][j]=='.' && grid[i][j]!='v' && grid[src][j]=='v'){
                result.first[i][j] = 'v';
                result.first[src][j] = '.';
                result.second++;
            }
        }
    }

    return result;
}

int solve(GRID &grid){
    int moves = 1;
    while (true){
        auto next_cnt = moveOnGrid(grid);
        if(next_cnt.second==0){
            break;
        }
        moves++;
        grid = move(next_cnt.first);
    }

    return moves;
}

int main() {
    GRID grid = readFile("input.txt");

    // Part 1
    cout<<solve(grid)<<endl;// 520

    return 0;
}

/*
     *
    /.\
   /..'\
   /'.'\
  /.''.'\
  /.'.'.\
 /'.''.'.\
 ^^^[_]^^^
  __  __                             _____  _            _       _                            _  _ 
 |  \/  |                           / ____|| |          (_)     | |                          | || |
 | \  / |  ___  _ __  _ __  _   _  | |     | |__   _ __  _  ___ | |_  _ __ ___    __ _  ___  | || |
 | |\/| | / _ \| '__|| '__|| | | | | |     | '_ \ | '__|| |/ __|| __|| '_ ` _ \  / _` |/ __| | || |
 | |  | ||  __/| |   | |   | |_| | | |____ | | | || |   | |\__ \| |_ | | | | | || (_| |\__ \ |_||_|
 |_|  |_| \___||_|   |_|    \__, |  \_____||_| |_||_|   |_||___/ \__||_| |_| |_| \__,_||___/ (_)(_)
                             __/ |                                                                 
                            |___/       
*/
