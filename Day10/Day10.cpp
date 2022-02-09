#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "../utils/utils.h"

using namespace std;

vector<string> readFile(string filename){
    string line;
    ifstream myfile (filename);
    vector<string> sub_system;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            sub_system.push_back(line);
        }
    }
    else cout << "Unable to open file";

    return sub_system;
}

int main() {
    vector<string> sub_system = readFile("input.txt");
    map<char, char> pairs = { {'(',')'}, {'[',']'}, {'{','}'}, {'<','>'} };
    map<char, int> points = { {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137} };

    // Part 1// 387363
    // Part 2// 4330777059

    return 0;
}