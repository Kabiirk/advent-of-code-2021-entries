#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <queue> // for priority queue
#include <deque>
#include "../utils/utils.h"

using namespace std;

using CAVE = vector<vector<int>>;
// using size_t = int;
/*
ULL getMinPath(vector<vector<ULL>>&arr,ULL n){
    //decalre a array for storing minimum cost up to that cell and initialize with INT_MAX
    vector<vector<ULL>>dp(n,vector<ULL>(n,1000));
    //declare a visibility array to track setteled cells and initialize it with all false values
    vector<vector<bool>>vis(n,vector<bool>(n,false));
    typedef pair<ULL,pair<ULL,ULL>> p;
    //initialize dp[0][0] to the first cell of the input array
    dp[0][0]=arr[0][0];
    //declare a mean heap 
    priority_queue<p,vector<p>,greater<p>>pq;
    ULL i,j,val;
    //push the first cell to the heap
    pq.push(make_pair(dp[0][0],make_pair(0,0)));
    
    //start extracting from heap until the heap becomes empty
    while(!pq.empty()){
        auto temp=pq.top();
        pq.pop();
        i=temp.second.first,j=temp.second.second;
        val=temp.first;
        dp[i][j]=val;
        vis[i][j]=true;
        //if the current cell is the bottom right then immediately return the value
        if(i==n-1 && j==n-1)
            return val;
    
        //go to to left,right,bottom and up and push to the heap if criteria matched
        if(i-1>=0 && !vis[i-1][j] && dp[i][j]+arr[i-1][j]<dp[i-1][j]){
            dp[i-1][j]=dp[i][j]+arr[i-1][j];
            pq.push(make_pair(dp[i][j]+arr[i-1][j],make_pair(i-1,j)));
        }
        if(j-1>=0 && !vis[i][j-1] && dp[i][j]+arr[i][j-1]<dp[i][j-1]){
            dp[i][j-1]=dp[i][j]+arr[i][j-1];
            pq.push(make_pair(dp[i][j-1],make_pair(i,j-1)));
        }
        if(j+1<n && !vis[i][j+1] && dp[i][j]+arr[i][j+1]<dp[i][j+1]){
            dp[i][j+1]=dp[i][j]+arr[i][j+1];
            pq.push(make_pair(dp[i][j+1],make_pair(i,j+1)));
        }
        if(i+1<n && !vis[i+1][j] && dp[i][j]+arr[i+1][j]<dp[i+1][j]){
            dp[i+1][j]=dp[i][j]+arr[i+1][j];
            pq.push(make_pair(dp[i+1][j],make_pair(i+1,j)));
        }
            
        //start popping the top elements if already settled
        if(!pq.empty()){
            temp=pq.top();
            i=temp.second.first,j=temp.second.second;
            while(!pq.empty() && vis[i][j]){
                pq.pop();
                if(!pq.empty()){
                temp=pq.top();
                i=temp.second.first,j=temp.second.second;}
            }
            
        }
    }
    return dp[n-1][n-1];
}
*/

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

struct Point {
    int row;
    int col;
    int cost;
};

int leastPathCost(CAVE &cave){
    int n = cave.size(); // for readability
    // filled with max value for integer
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
    //print2DVec(cave);

    // Part 1
    // cout<<getMinPath(cave, cave.size());
    cout<<leastPathCost(cave)<<endl;// 619

    CAVE expanded_cave = expandCave(cave);

    // Part 2// 2922
    return 0;
}
