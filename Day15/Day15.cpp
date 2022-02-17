#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <limits> // for numeric_limits
#include "../utils/utils.h"

using namespace std;

using CAVE = vector<vector<int>>;

CAVE readFile(string filename){
    string line;
    CAVE cave;

    // Read File
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            vector<int> current_line;
            for(int i = 0; i<line.length(); i++){
                current_line.push_back( (int)(line[i] - '0') );
            }
            cave.push_back(current_line);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return cave;
}


int leastPathCost(CAVE &cave){
    int n = cave.size(); // for readability
    // filled with max value of integer
    CAVE cost(n, vector<int>(n, numeric_limits<int>::max()));
    cost[0][0] = 0;

    deque<pair<int, int>> pending;
    pending.push_back({0, 0});

    while(!pending.empty()){
        auto p = pending.front();
        int row = p.first;
        int col = p.second;
        pending.pop_front();

        if(row>0 && cost[row][col]+cave[row-1][col]<cost[row-1][col]){
            cost[row-1][col] = cost[row][col] + cave[row-1][col];
            pending.push_back({row-1, col});
        }
        if(row+1<cost.size() && cost[row][col]+cave[row+1][col]<cost[row+1][col]){
            cost[row+1][col] = cost[row][col] + cave[row+1][col];
            pending.push_back({row+1, col});
        }
        if(col>0 && cost[row][col]+cave[row][col-1]<cost[row][col-1]){
            cost[row][col-1] = cost[row][col] + cave[row][col-1];
            pending.push_back({row, col-1});
        }
        if(col+1<cost[row].size() && cost[row][col]+cave[row][col+1]<cost[row][col+1]){
            cost[row][col+1] = cost[row][col] + cave[row][col+1];
            pending.push_back({row, col+1});
        }
    }

    return cost[cost.size()-1][cost[cost.size()-1].size()-1];
}

CAVE expandCave(CAVE &cave){
    int n = cave.size();
    CAVE result(n*5, vector<int>(n*5, 0));
    for(int i = 0; i<result.size(); i++){
        for(int j = 0; j<result[i].size(); j++){
            result[i][j] =( ( cave[i%n][j%n] + i/n + j/n - 1 ) %9 ) + 1;
        }
    }

    return result;
}

int main() {
    CAVE cave = readFile("input.txt");

    // Part 1
    cout<<leastPathCost(cave)<<endl;// 619

    CAVE expanded_cave = expandCave(cave);

    // Part 2
    cout<<leastPathCost(expanded_cave)<<endl;// 2922

    return 0;
}