#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <tuple>
#include <map>
#include <set>
#include <cmath>
#include "../utils/utils.h"

// Some good references :
// https://stackoverflow.com/questions/66135217/how-to-subdivide-set-of-overlapping-aabb-into-non-overlapping-set-of-aabbs
// Iterating over a tuple : https://stackoverflow.com/questions/26902633/how-to-iterate-over-a-stdtuple-in-c-11

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
        return make_tuple( make_pair(x_min,x_max),
                           make_pair(y_min,y_max),
                           make_pair(z_min,z_max)
                        );
    }
};

struct ReqData{
    vector<Cube> reboot_steps;
    vector<Cube> steps;
};

ReqData readFile(string filename, int reboot_limit=0){
    string line;
    ifstream myfile (filename);

    ReqData instructions;

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            const regex r("(on|off) x=(-?\\d*)..(-?\\d*),y=(-?\\d*)..(-?\\d*),z=(-?\\d*)..(-?\\d*)");  
            smatch result;

            // result = ["on x=-7..43,y=-47..3,z=-43..2", "on", "-7", "43", "-47", "3", "-43", "2"]
            if (regex_search(line, result, r)){
                int x_min = stoi(result[2]);
                int x_max = stoi(result[3]);
                int y_min = stoi(result[4]);
                int y_max = stoi(result[5]);
                int z_min = stoi(result[6]);
                int z_max = stoi(result[7]);
                bool is_on = result[1]=="on";
                Cube ins( x_min, x_max, y_min, y_max, z_min, z_max, is_on );
                // Checks for Part 1 sequence of steps
                if( -reboot_limit <= x_min && x_min <= reboot_limit &&
                    -reboot_limit <= x_max && x_max <= reboot_limit &&
                    -reboot_limit <= y_min && y_min <= reboot_limit &&
                    -reboot_limit <= y_max && y_max <= reboot_limit &&
                    -reboot_limit <= z_min && z_min <= reboot_limit &&
                    -reboot_limit <= z_max && z_max <= reboot_limit){

                    instructions.reboot_steps.push_back(ins);
                    instructions.steps.push_back(ins);
                }
                else{
                    instructions.steps.push_back(ins);
                }
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return instructions;
}

/*
Overlapping (Tuple) :
        ((23824, 35850), (61103, 65201), (33363, 34344))

steps (List) :
        [
            (True, ((-39, 5), (-35, 13), (-14, 36))),
            (True, ((-39, 12), (-43, 6), (-4, 42))),
            (True, ((-18, 35), (-24, 21), (-12, 34))),
            (True, ((-2, 48), (-14, 38), (-9, 44))),
            (True, ((-14, 40), (-37, 13), (-47, 4))),
            (True, ((-34, 18), (-5, 43), (-46, 5))),
            (True, ((-37, 13), (-37, 12), (-43, 6))),
            ..
        ]

counts (Dict) :
        {
            ((-39, 5), (-35, 13), (-14, 36)): 1,
            ((-39, 5), (-35, 6), (-4, 36)): -1,
            ((-39, 12), (-43, 6), (-4, 42)): 1,
            ((-18, 5), (-24, 6), (-4, 34)): 1,
            ((-18, 12), (-24, 6), (-4, 34)): -1,
            ((-18, 5), (-24, 13), (-12, 34)): -1,
            ((-18, 35), (-24, 21), (-12, 34)): 1,
            ((-2, 12), (-14, 6), (-4, 34)): 0, ((-2, 35),
            (-14, 21), (-9, 34)): -1, ((-2, 12), (-14, 6),
            (-4, 42)): -1, ((-2, 5), (-14, 6), (-4, 34)): 0,
            ((-2, 5), (-14, 6), (-4, 36)): 0,
            ((-2, 5), (-14, 13), (-9, 34)): 1,
            ((-2, 5), (-14, 13), (-9, 36)): -1,
            ((-2, 48), (-14, 38), (-9, 44)): 1,
            ((-2, 5), (-14, 13), (-9, 4)): 0,
            ...
        }

keys (set) :
        {
            ((-18, 12), (-24, 6), (-4, 6)),
            ((-18, 5), (-24, 6), (-4, 34)),
            ((-5, 13), (-19, 12), (-8, 4)),
            ...
        }

updates (map) :
        {
            ((-18, 12), (-24, 6), (-4, 6)): -1,
            ((-12, 5), (-4, 9), (-11, -3)): 0,
            ((-5, 5), (-19, 6), (-4, -3)): 0,
            ((-14, -2), (-19, 9), (-14, -3)): 0,
            ...
        }
*/

// Utility functions specifically for this problem
set<CUBE_TUP> mapKeyToSet(map<CUBE_TUP, int> dict){
    set<CUBE_TUP> s;
    // m = pair<CUBE_TUP, int>
    for(auto m : dict){
        s.insert(m.first);
    }
    return s;
}

pair<int, int> indexTuple(CUBE_TUP tup, int index){
    if(index == 0){
        return get<0>(tup);
    }
    else if(index == 1){
        return get<1>(tup);
    }
    else{
        return get<2>(tup);
    }
}

void printCubeTup(CUBE_TUP v){
    cout<<"( ";
    cout<<"("<<get<0>(v).first<<","<<get<0>(v).second<<"),";
    cout<<"("<<get<1>(v).first<<","<<get<1>(v).second<<"),";
    cout<<"("<<get<2>(v).first<<","<<get<2>(v).second<<"),";
    cout<<" )"<<endl;
}

// For both Part 1 & 2
int64_t cubeVol(CUBE_TUP b1){
    pair<int, int> x = indexTuple(b1, 0);
    pair<int, int> y = indexTuple(b1, 1);
    pair<int, int> z = indexTuple(b1, 2);

    return (int64_t)(abs(x.second - x.first)+1) * (abs(y.second - y.first)+1) * (abs(z.second - z.first)+1);
}

pair<CUBE_TUP, int> overlaps(CUBE_TUP b1, CUBE_TUP b2){
    // ans = ((-12, 5), (-4, 6), (-4, -3))
    // n1, n2 => pair<int, int>
    pair<int, int> ans[3];
    for(int i = 0; i<3; i++){
        pair<int, int> n1 = indexTuple(b1, i);
        pair<int, int> n2 = indexTuple(b2, i);
        if( (n1.second < n2.first) || (n2.second < n1.first) ){
            CUBE_TUP temp = { {0,1}, {2,3}, {4,5} };
            return make_pair(temp, 0);
        }
        ans[i] = make_pair( max(n1.first, n2.first), min(n1.second, n2.second) );
        // pair<int, int> bounds = make_pair( max(n1.first, n2.first), min(n1.second, n2.second) );
        // ans.push_back(bounds);
    }

    return make_pair(make_tuple( ans[0], ans[1], ans[2] ), 3);
}

map<CUBE_TUP, int> count(vector<Cube> steps){
    map<CUBE_TUP, int> counts;

    // i => object instance of Cube struct 
    for(auto i : steps){
        bool sw = i.to_do;
        CUBE_TUP bounds = i.return3DTuple();
        map<CUBE_TUP, int64_t> updates;
        set<CUBE_TUP> keys = mapKeyToSet(counts);
        // cube => ((-18, 12), (-24, 6), (-4, 6))
        // cube = <CUBE_TUP>
        for(auto cube : keys){
            pair<CUBE_TUP, int> overlapping = overlaps(bounds, cube);
            if( overlapping.second==0 ){
                continue;
            }
            updates[overlapping.first] -= counts[cube];
        }

        if(sw){
            updates[bounds] += 1;
        }

        for(auto c : updates){
            counts[c.first] += c.second;
        }
    }

    return counts;
}

int main() {
    // ~wrangle()
    ReqData req_data = readFile("input.txt", 50);
    vector<Cube> reboot_steps = req_data.reboot_steps;
    vector<Cube> steps = req_data.steps;

    // Part 1
    map<CUBE_TUP, int> counts1 = count(reboot_steps);
    int64_t p1 = 0;
    for(auto cube : counts1){
        p1 += cubeVol(cube.first)*cube.second;
    }
    cout<<p1<<endl;// 611378

    // Part 2
    map<CUBE_TUP, int> counts2 = count(steps);
    int64_t p2 = 0;
    for(auto cube : counts2){
        p2 += cubeVol(cube.first)*cube.second;
    }
    cout<<p2<<endl;// 1214313344725528

    return 0;
}
