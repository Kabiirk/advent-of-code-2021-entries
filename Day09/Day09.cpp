#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "../utils/utils.h"

using namespace std;

vector<vector<int>> readFile(string filename){
    vector<vector<int>> basing_heights;
    string line;
    ifstream myfile (filename);

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            vector<int> current_row;
            int n = line.length();
            for(int i = 0; i<n; i++){
                current_row.push_back(line[i]-'0');
            }

            basing_heights.push_back(current_row);
        }
    }
    else cout << "Unable to open file";

    return basing_heights;
}

int main() {
    vector<vector<int>> basin_heights = readFile("input.txt");

    return 0;
}