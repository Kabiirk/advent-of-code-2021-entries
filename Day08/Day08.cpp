#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../utils/utils.h"

using namespace std;

void readFile(string filename){
    string line;
    ifstream myfile (filename);
    vector<string> entries;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            const regex r("(\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) | (\\w+) (\\w+) (\\w+) (\\w+)");
            smatch result;

            if (regex_search(line, result, r)) {
                // result = ["forward 6", "forward", "6"]
                for(auto i : result){
                    cout<<i<<"->";
                }
                cout<<endl;
            }
        }
    }
    else cout << "Unable to open file";
}

int main() {
    readFile("input.txt");
    
    return 0;
}