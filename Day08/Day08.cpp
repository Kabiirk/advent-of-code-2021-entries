#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../utils/utils.h"

using namespace std;

vector<vector<vector<string>>> readFile(string filename){
    /*
    Desired shape of entries :
    <
        <
            <signal words>, 
            <output words>
        >,
        
        <
            <signal words>, 
            <output words>
        >,
        ..
        ..
    >

    e.g. : Line entry like
    "gfdbc begdcf bfedg acgfed cd fcd febgda cfgab cadbgef ebdc | ebcd gdefab ebdc ebafdcg"
    would be stored as :
    <
        <
            <"gfdbc" "begdcf" "bfedg" "acgfed" "cd" "fcd" "febgda" "cfgab" "cadbgef" "ebdc">,
            <"ebcd" "gdefab" "ebdc" "ebafdcg">
        >,
    >
    */
    string line;
    ifstream myfile (filename);
    vector<string> signal_pattern, output;
    vector<vector<vector<string>>> entries;

    if (myfile.is_open()){
        while ( getline(myfile, line) ){
            vector<vector<string>> entry;
            const regex r("(\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) (\\w+) \\| (\\w+) (\\w+) (\\w+) (\\w+)");
            smatch result;

            if (regex_search(line, result, r)) {
                // result = ["gfdbc begdcf bfedg acgfed cd fcd febgda cfgab cadbgef ebdc | ebcd gdefab ebdc ebafdcg", "forward", "6"]
                for(int i = 1; i<=10; i++){
                    signal_pattern.push_back(result[i]);
                }
                for(int j = 11; j<=14; j++){
                    output.push_back(result[j]);
                }
                // printVector(signal_pattern);
                // printVector(output);
                entry.push_back(signal_pattern);
                entry.push_back(output);

                // clear vector for parsing & filling next entry
                vector<string>().swap(signal_pattern);
                vector<string>().swap(output);
            }
            entries.push_back(entry);
        }
    }
    else cout << "Unable to open file";

    return entries;
}

int main() {
    vector<vector<vector<string>>> entries = readFile("input.txt");
    
    return 0;
}