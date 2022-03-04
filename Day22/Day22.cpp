#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <tuple>
#include <algorithm>
#include <map>
#include <set>
#include "../utils/utils.h"

// Some good references :
// https://stackoverflow.com/questions/66135217/how-to-subdivide-set-of-overlapping-aabb-into-non-overlapping-set-of-aabbs

using namespace std;

using CUBE_TUP = tuple<pair<int, int>, pair<int, int>, pair<int, int>>;

struct Cube{
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int z_min;
    int z_max;
    bool to_do;

    Cube(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max, bool to_do) : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max), z_min(z_min), z_max(z_max), to_do(to_do){

    }

    CUBE_TUP return3DTuple(){
        return make_tuple( make_pair(this->x_min, this->x_max),
                           make_pair(this->y_min, this->y_max),
                           make_pair(this->z_min, this->z_max)
                        );
    }
};

// utility function specifically for this problem
set<Cube> mapKeyToSet(map<Cube, int> dict){
    set<Cube> s;
    // m = pair<Cube, int>
    for(auto m : dict){
        s.insert(m.first);
    }
    return s;
}

vector<Cube> readFile(string filename){
    string line;
    ifstream myfile (filename);

    vector<Cube> instructions;

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            // cout<<line<<endl;
            const regex r("(on|off) x=(-?\\d*)..(-?\\d*),y=(-?\\d*)..(-?\\d*),z=(-?\\d*)..(-?\\d*)");  
            smatch result;

            // result = ["on x=-7..43,y=-47..3,z=-43..2", "on", "-7", "43", "-47", "3", "-43", "2"]
            if (regex_search(line, result, r)){
                Cube ins( stoi(result[2]),
                          stoi(result[3]),
                          stoi(result[4]),
                          stoi(result[5]),
                          stoi(result[6]),
                          stoi(result[7]),
                          result[1]=="on" ? true : false );

                instructions.push_back(ins);
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return instructions;
}

set<pair<int, int>> overlaps(){

}

map<Cube, int> count(vector<Cube> steps){
    map<Cube, int> counts;

    for(auto i : steps){
        // switch is a keyword in c++
        bool sw = i.to_do;
        CUBE_TUP bounds = i.return3DTuple();
        map<Cube, int> updates;
        set<Cube> keys = mapKeyToSet(counts);
        for(auto cube : keys){
            // overlapping = set<(-2, 12), (-14, 6), (-4, 6)>
            set<pair<int, int>> overlapping = overlaps()
        }


    }
    return counts;
}

int main() {
    vector<Cube> steps = readFile("input.txt");
    map<Cube, int> counts;

    // Part 1// 611378
    // Part 2// 1214313344725528

    return 0;
}
