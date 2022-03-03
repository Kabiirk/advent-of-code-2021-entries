#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <tuple>
#include <algorithm>
#include "../utils/utils.h"

using namespace std;

using CUBE = tuple<int, int, int>;

struct Instruction{
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int z_min;
    int z_max;
    string to_do;

    Instruction(int x_min, int x_max, int y_min, int y_max, int z_min, int z_max, string to_do) : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max), z_min(z_min), z_max(z_max), to_do(to_do){ }
};

vector<Instruction> readFile(string filename){
    string line;
    ifstream myfile (filename);

    vector<Instruction> instructions;

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            // cout<<line<<endl;
            const regex r("(on|off) x=(-?\\d*)..(-?\\d*),y=(-?\\d*)..(-?\\d*),z=(-?\\d*)..(-?\\d*)");  
            smatch result;

            // result = ["on x=-7..43,y=-47..3,z=-43..2", "on", "-7", "43", "-47", "3", "-43", "2"]
            if (regex_search(line, result, r)){
                Instruction ins(stoi(result[2]),
                                    stoi(result[3]),
                                    stoi(result[4]),
                                    stoi(result[5]),
                                    stoi(result[6]),
                                    stoi(result[7]),
                                    result[1]);

                instructions.push_back(ins);
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return instructions;
}

int main() {
    vector<Instruction> instructions = readFile("input.txt");

    return 0;
}
