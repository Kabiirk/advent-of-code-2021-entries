#include <iostream>
#include <fstream>
#include <string>
#include <vector> 

using namespace std;

int main() {
    string line;
    vector<int> depths;

    // Read File
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            depths.push_back(stoi(line));
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    int n = depths.size();
    int depth_increase = 0;

    // Part 1
    for(int i = 1; i<n; i++){
        if( depths[i] > depths[i-1] ){
            depth_increase += 1;
        }
    }
    cout << depth_increase << endl; // 1502

    // Part 2
    // current window - previous window = (x3 + x2 + x1) - (x2 + x1 + x0) = x3 - x0
    int window_increase = 0;
    for(int j = 3; j<n; j++){
        if(depths[j] > depths[j-3]){
            window_increase += 1;
        }
    }
    cout << window_increase <<endl; // 1538

    return 0;
}
