#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>
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
                // result = ["gfdbc begdcf bfedg acgfed cd fcd febgda cfgab cadbgef ebdc | ebcd gdefab ebdc ebafdcg", "gfdbc", "begdcf", "bfedg", "acgfed", "cd", "fcd", "febgda", "cfgab", "cadbgef", "ebdc", "ebcd", "gdefab", "ebdc", "ebafdcg"]
                for(int i = 1; i<=10; i++){
                    signal_pattern.push_back(result[i]);
                }
                for(int j = 11; j<=14; j++){
                    output.push_back(result[j]);
                }
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

int partTwo(vector<vector<vector<string>>> entries){
    int total_count = 0;
    for(auto entry : entries){
        vector<string> signal_input = entry[0];
        vector<string> output = entry[1];
        map<int, string> digit_map;

        // for unique numbers 1, 4, 7, 8
        for(auto digit : signal_input){
            int len = digit.length();
            if(len == 2){
                digit_map[1] = digit;
            }
            else if(len == 4){
                digit_map[4] = digit;
            }
            else if(len == 3){
                digit_map[7] = digit;
            }
            else if(len == 7){
                digit_map[8] = digit;
            }
        }

        // For rest of the unknown digits
        // for 0, 6, 9
        for(auto digit : signal_input){
            int len = digit.length();
            if(len == 6){
                set<string> digit_set = stringToSet(digit);
                // 4 is part of 9
                if (isSubset(digit_set, stringToSet(digit_map[4]))){
                    digit_map[9] = digit;
                }
                // 1 is part of 0
                else if (isSubset(digit_set, stringToSet(digit_map[1]))){
                    digit_map[0] = digit;
                }
                else{
                    digit_map[6] = digit;
                }
            }
        }
        
        // for 2, 3, 5
        for(auto digit : signal_input){
            int len = digit.length();
            if(len == 5){
                set<string> digit_set = stringToSet(digit);
                // 5 is part of 6
                if (isSubset(stringToSet(digit_map[6]), digit_set)){
                    digit_map[5] = digit;
                }
                // 1 is part of 3
                else if (isSubset(digit_set, stringToSet(digit_map[1]))){
                    digit_map[3] = digit;
                }
                else{
                    digit_map[2] = digit;
                }
            }
        }

        // printMap(digit_map);

        // Mapping Output to respective number
        vector<string> number; // for e.g.: number = { "2", "3", "6", "9" }
        string temp_join_number = ""; // for e.g.: temp_join_number = "2369"
        for(auto digit : output){
            for(map<int, string>::iterator iter = digit_map.begin(); iter != digit_map.end(); ++iter){
                set<string> digit_set = stringToSet(digit);
                if(digit_set == stringToSet(iter->second)){
                    number.push_back(to_string(iter->first));
                }
            }
        }

        for(auto num:number){
            temp_join_number+=num;
        }
        total_count+= stoi(temp_join_number);
    }

    return total_count;
}

int main() {
    vector<vector<vector<string>>> entries = readFile("input.txt");

    // Part 1
    int unique_digit_count = 0;
    for(auto entry : entries){
        for(auto output : entry[1]){
            int len = output.length();
            if(len == 2 || len == 4 || len == 3 || len == 7){
                unique_digit_count++;
            }
        }
    }
    cout<<unique_digit_count<<endl;// 512

    // Part 2
    cout<<partTwo(entries)<<endl;// 1091165

    return 0;
}