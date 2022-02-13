#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <regex>
#include "../utils/utils.h"

using namespace std;

using DOTS = set<pair<int, int>>;
using INSTRUCTION = vector<pair<string, int>>;

struct RequiredData{
    DOTS dot_set;
    INSTRUCTION instructions_vec;
};

RequiredData readFile(string filename){
    string line;
    ifstream myfile (filename);
    RequiredData req_data;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            // Coordinates
            if(isdigit(line[0])){
                const regex r("(-?\\d*),(-?\\d*)");
                smatch result2;
                // result2 = ["994,18", "994", "18"]
                if (regex_search(line, result2, r)){
                    req_data.dot_set.insert(make_pair( stoi(result2[1]), stoi(result2[2]) ) );
                }
            }
            // Fold Instructions
            else if(line[0]=='f'){
                const regex r("fold along (\\w)=(-?\\d*)");
                smatch result;
                // result = ["fold along x=655", "x", "655"]
                if (regex_search(line, result, r)){
                    req_data.instructions_vec.push_back(make_pair(result[1], stoi(result[2])));
                }
            }
            
            // const regex r("(\\w+)-(\\w+)");
            // smatch result;

            // if (regex_search(line, result, r)){

            // }
        }
    }
    else cout << "Unable to open file";

    return req_data;
}

int main() {
    RequiredData req_data =  readFile("input.txt");
    DOTS dots = req_data.dot_set;
    INSTRUCTION instructions = req_data.instructions_vec;
    // printSetPair(dots);
    // printVecPair(instructions);
    // Part 1 763
    // Part 2
    // ###  #  #  ##  #    ###   ##  ###   ## 
    // #  # #  # #  # #    #  # #  # #  # #  #
    // #  # #### #  # #    #  # #    #  # #  #
    // ###  #  # #### #    ###  #    ###  ####
    // # #  #  # #  # #    # #  #  # # #  #  #
    // #  # #  # #  # #### #  #  ##  #  # #  #

    return 0;
}