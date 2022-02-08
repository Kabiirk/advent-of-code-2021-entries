#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
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

struct RequiredData {
    vector<pair<int, int>> low_points_coord;
    int part_one_answer;
};

bool checkLowpoint(vector<bool> checklist){
    bool result = true;
    for(auto item : checklist){
        result = result && item;
    }

    return result;
}

RequiredData partOne(vector<vector<int>> entries){
    int n = entries.size();
    int m = entries[0].size();
    vector<int> low_points;
    vector<pair<int, int>> low_points_coord;
    RequiredData req_data;

    for(int i = 0; i<n; i++){
        // int m = entries[i].size();
        for(int j = 0; j<m; j++){
            // Non-border entries
            if((0<i && i<n-1) && (0<j && j<m-1)){
                bool top = entries[i][j] < entries[i-1][j];
                bool left = entries[i][j] < entries[i][j-1];
                bool bottom = entries[i][j] < entries[i+1][j];
                bool right = entries[i][j] < entries[i][j+1];
                if(checkLowpoint({top, left, bottom, right})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }

            // Corners
            if(i == 0 && j == 0){
                bool bottom = entries[i][j] < entries[i+1][j];
                bool right = entries[i][j] < entries[i][j+1];
                if(checkLowpoint({bottom, right})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }
            if(i == 0 && j == m-1){
                bool left = entries[i][j] < entries[i][j-1];
                bool bottom = entries[i][j] < entries[i+1][j];
                if(checkLowpoint({left, bottom})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }
            if(i == n-1 && j == 0){
                bool top = entries[i][j] < entries[i-1][j];
                bool right = entries[i][j] < entries[i][j+1];
                if(checkLowpoint({top, right})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }
            if(i == n-1 && j == m-1){
                bool top = entries[i][j] < entries[i-1][j];
                bool left = entries[i][j] < entries[i][j-1];
                if(checkLowpoint({top, left})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }

            // Top row excluding corners
            if(i == 0 && (0<j && j<m-1)){
                bool left = entries[i][j] < entries[i][j-1];
                bool bottom = entries[i][j] < entries[i+1][j];
                bool right = entries[i][j] < entries[i][j+1];
                if(checkLowpoint({left, bottom, right})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }

            // bottom row excluding corners
            if(i == n-1 && (0<j && j<m-1)){
                bool top = entries[i][j] < entries[i-1][j];
                bool left = entries[i][j] < entries[i][j-1];
                bool right = entries[i][j] < entries[i][j+1];
                if(checkLowpoint({top, left, right})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }

            // left column excluding corners
            if((0<i && i<n-1) && j == 0){
                bool top = entries[i][j] < entries[i-1][j];
                bool bottom = entries[i][j] < entries[i+1][j];
                bool right = entries[i][j] < entries[i][j+1];
                if(checkLowpoint({top, bottom, right})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }

            // right column excluding corners
            if((0<i && i<n-1) && j == m-1){
                bool top = entries[i][j] < entries[i-1][j];
                bool left = entries[i][j] < entries[i][j-1];
                bool bottom = entries[i][j] < entries[i+1][j];
                if(checkLowpoint({top, left, bottom})){
                    low_points.push_back(entries[i][j]);
                    low_points_coord.push_back(make_pair(i,j));
                }
            }
        }
    }

    int part_one_result  = sumOfVecElements(low_points)+low_points.size();
    req_data.part_one_answer = part_one_result;
    req_data.low_points_coord = low_points_coord;
    return req_data;
}

set<pair<int, int>> compareRek(int r, int c, set<pair<int, int>> basin, int height, int width, vector<vector<int>> basin_heights){
    vector<int> dr = {1, 0, -1, 0};
    vector<int> dc = {0, 1, 0, -1};
    set<pair<int, int>> new_points;

    for(int i = 0; i<4; i++){
        int rr = r+dr[i];
        int cc = c+dc[i];
        bool is_in = basin.find(make_pair(rr, cc)) != basin.end();
        if( !is_in && (rr>=0) && (cc >= 0) && (rr < height) && (cc < width) && (basin_heights[rr][cc]<9) ){
            new_points.insert(make_pair(rr, cc));
        }
        // similar to pythonic basin.union(new_points)
        basin.insert(new_points.begin(), new_points.end());
        for(auto np : new_points){
            set<pair<int, int>> temp_set = compareRek(np.first, np.second, basin, height, width, basin_heights);
            basin.insert(temp_set.begin(), temp_set.end());
        }
    }

    return basin;
}

int partTwo(vector<vector<int>> basin_heights, vector<pair<int, int>> low_points_coord){
    vector<int> basins;
    int map_height = basin_heights.size();
    int map_width = basin_heights[0].size();
    for(auto coord : low_points_coord){
        int r = coord.first;
        int c = coord.second;
        set<pair<int, int>> basin = { make_pair(r, c) };
        int temp = compareRek(r, c, basin, map_height, map_width, basin_heights).size();
        basins.push_back( temp );
    }

    sort(basins.begin(), basins.end(), greater<int>());

    return basins[0]*basins[1]*basins[2];
}


int main(){
    vector<vector<int>> basin_heights = readFile("input.txt");

    // Alternatively just program partOne to return a 
    // vector/pair/map etc. of desired values
    // But I wanted to use struct,
    // this can alternatively be done with a class too 
    RequiredData required_data = partOne(basin_heights);

    // Part 1
    cout<< required_data.part_one_answer <<endl;// 566

    // Part 2
    cout<< partTwo(basin_heights, required_data.low_points_coord)<<endl;// 891684

    return 0;
}