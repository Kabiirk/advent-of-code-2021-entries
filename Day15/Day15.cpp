#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <queue> // for priority queue

typedef int ULL;

using namespace std;

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

int main() {
    string line;
    vector< vector< ULL > > cave;

    // Read File
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            vector<ULL> current_line;
            for(int i = 0; i<line.length(); i++){
                current_line.push_back( (int)(line[i] - '0') );
            }
            cave.push_back(current_line);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    // Print 2D Vector
    // for(int j = 0; j<cave.size(); j++){
    //     for(int k = 0; k<cave[j].size(); k++){
    //         cout<<cave[j][k]<<"";
    //     }
    //     cout<<"\n";
    // }

    // Part 1
    cout<<getMinPath(cave, cave.size());

    // Part 2
    return 0;
}
