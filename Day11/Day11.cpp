#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../utils/utils.h"

using namespace std;

map<pair<int, int>, int> readFile(string filename){
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
    map<pair<int, int>, int> grid;

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
void printGrid(map<pair<int, int>, int> grid){
    for (map<pair<int, int>, int>::const_iterator itr = grid.begin(); itr != grid.end(); ++itr) {
        cout << "(" <<itr->first.first<<","<<itr->first.second<<")" << ":" << itr->second<<" ";
    }
    cout<<endl;
}

int main() {
    map<pair<int, int>, int> grid = readFile("input.txt");
    printGrid(grid);

    // Part 1//1739
    // Part 2//324

    return 0;
}