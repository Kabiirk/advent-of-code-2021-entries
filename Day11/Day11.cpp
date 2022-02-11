#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm> // for copy()
#include "../utils/utils.h"

using namespace std;

typedef map<pair<int, int>, int> GRID;
typedef pair<int, int> COORDINATES;


GRID readFile(string filename){
    /*
    Desired Grid Map:
    {
        (0, 0): 7, (0, 1): 6, (0, 2): 1, (0, 3): 2, (0, 4): 6, (0, 5): 4, (0, 6): 8, (0, 7): 2, (0, 8): 1, (0, 9): 7,
        (1, 0): 7, (1, 1): 6, (1, 2): 1, (1, 3): 7, (1, 4): 2, (1, 5): 3, (1, 6): 7, (1, 7): 6, (1, 8): 7, (1, 9): 2,
        (2, 0): 2, (2, 1): 8, (2, 2): 5, (2, 3): 3, (2, 4): 8, (2, 5): 7, (2, 6): 1, (2, 7): 8, (2, 8): 3, (2, 9): 6,
        (3, 0): 7, (3, 1): 2, (3, 2): 1, (3, 3): 4, (3, 4): 3, (3, 5): 6, (3, 6): 7, (3, 7): 1, (3, 8): 3, (3, 9): 5,
        (4, 0): 1, (4, 1): 5, (4, 2): 3, (4, 3): 3, (4, 4): 3, (4, 5): 6, (4, 6): 5, (4, 7): 6, (4, 8): 1, (4, 9): 4,
        (5, 0): 6, (5, 1): 2, (5, 2): 5, (5, 3): 8, (5, 4): 1, (5, 5): 7, (5, 6): 2, (5, 7): 8, (5, 8): 6, (5, 9): 2,
        (6, 0): 5, (6, 1): 3, (6, 2): 7, (6, 3): 7, (6, 4): 6, (6, 5): 7, (6, 6): 5, (6, 7): 5, (6, 8): 8, (6, 9): 3,
        (7, 0): 5, (7, 1): 6, (7, 2): 1, (7, 3): 3, (7, 4): 2, (7, 5): 6, (7, 6): 8, (7, 7): 2, (7, 8): 7, (7, 9): 8,
        (8, 0): 8, (8, 1): 3, (8, 2): 8, (8, 3): 1, (8, 4): 1, (8, 5): 3, (8, 6): 4, (8, 7): 4, (8, 8): 6, (8, 9): 5,
        (9, 0): 3, (9, 1): 4, (9, 2): 4, (9, 3): 5, (9, 4): 4, (9, 5): 2, (9, 6): 8, (9, 7): 7, (9, 8): 3, (9, 9): 3
    }
    */
    string line;
    ifstream myfile (filename);
    GRID grid;

    int m = 0;
    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            int n = 0;
            for(auto val : line){
                pair<int, int> temp_coord(m,n);
                grid.insert( pair<pair<int, int>, int>(temp_coord, val-'0') );
                n++;
            }
            m++;
        }
    }
    else cout << "Unable to open file";

    return grid;
}

// Helper function specifically for this problem
void printGrid(map<COORDINATES, int> grid, bool pretty=false){
    for (map<COORDINATES, int>::const_iterator itr = grid.begin(); itr != grid.end(); ++itr) {
        if(pretty){
            cout << "(" <<itr->first.first<<","<<itr->first.second<<")" << ":" << itr->second<<" ";
        }
        else{
            cout<< itr->second<<" ";
        }
    }
    cout<<endl;
}

void printSet(set<COORDINATES> s){
    cout<<"{ ";
    for(auto it : s){
        cout<<"("<<it.first<<","<<it.second<<")";
    }
    cout<<"}"<<endl;
}

void inc_neighbours(map<COORDINATES, int> &grid, int m, int n){
    vector<pair<int, int>> neighbours_incs = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
    for(auto neighbour : neighbours_incs){
        COORDINATES temp_pair(m+neighbour.first, n+neighbour.second);
        if( grid.find(temp_pair) != grid.end() ){
            grid[temp_pair] += 1;
        }
    }
}

void flash(GRID& grid, set<COORDINATES>& already_flashed){
    while(true){
        set<COORDINATES> flashed_now;
        for(map<COORDINATES, int>::const_iterator item = grid.begin(); item != grid.end(); ++item){
            COORDINATES current_coords = item->first;// (m,n)
            int v = item->second;// integer
            bool a = v>9;
            bool b = already_flashed.find(current_coords) != already_flashed.end();
            if( a && !b ){
                flashed_now.insert(current_coords);
                inc_neighbours(grid, current_coords.first, current_coords.second);
            }
        }
        if(flashed_now.empty()){
            break;
        }
        already_flashed.insert(flashed_now.begin(), flashed_now.end());
    }
}

void incrementGridValues(GRID& grid){
    // Increment by iterator for loop not working
    // for some reason
    // TODO : Remove hard-coding of limits
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            grid[make_pair(i, j)]++;
        }
    }
}

void step(GRID &grid, set<COORDINATES> &already_flashed){
    incrementGridValues(grid);

    flash(grid, already_flashed);

    for(auto flashed_coord : already_flashed){
            grid[flashed_coord] = 0;
    }
}

int main() {
    GRID grid = readFile("input.txt");
    int part1=0; 
    int part2=1; // optional, we can just std::cout function result

    int total = 0;
    for(int i=0; i<1000; i++){
        set<COORDINATES> already_flashed;
        step(grid, already_flashed);
        total+=already_flashed.size();
        if(i==99){
            part1 = total;
        }
        if(already_flashed.size() == grid.size()){
            part2 = i+1;
            break;
        }
    }

    // Part 1
    cout<<part1<<endl;// 1739

    // Part 2
    cout<<part2<<endl;// 324

    return 0;
}