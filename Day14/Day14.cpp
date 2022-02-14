#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "../utils/utils.h"

typedef unsigned long long int ULLI;

using namespace std;

struct RequiredData {
    string polymer;
    map<string, string> rules;
};

RequiredData readFile(string filename){
    string line;
    string to_append;
    string to_match;
    RequiredData req_data;

    // Read File
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            if(line.length() > 10){
                req_data.polymer = line;
            }
            else if(line.length() == 0){
                // Blank line
                continue;
            }
            else{
                to_append = line.back();
                to_match = line.substr(0, 2);
                // cout << to_match << " ==> " << to_append << endl;
                req_data.rules.insert( pair<string, string>(to_match, to_append) );
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return req_data;
}

string extendPolymer( map<string, string> rules, string pattern, int iterations){
    string first_pattern = pattern;
    for(int i = 0; i<iterations; i++){
        string temp_pattern;
        for(int j = 0; j<first_pattern.length(); j++){
            temp_pattern += first_pattern[j];
            if(j+1 < first_pattern.length() ){
                auto c3 = std::string(1,first_pattern[j]) + first_pattern[j+1];
                temp_pattern += rules[c3];
            }
        }
    cout<< i << " iteration Done"<<endl;
    first_pattern = temp_pattern;
    }

    return first_pattern;
}

map<char, ULLI> string2Frequency(string pattern){
    map<char, ULLI> frequency_dict;
    for(char k : pattern)
    {
        frequency_dict[k]++;
    }

    return frequency_dict;
}

ULLI calcMinMaxFrequencyDifference(map<char, ULLI> frequency_dict){
    int max_value = 0;
    for(auto it = frequency_dict.cbegin(); it != frequency_dict.cend(); ++it){
        if(it->second > max_value){
            max_value = it->second;
        }
    }

    int min_value = max_value;
    for(auto it = frequency_dict.cbegin(); it != frequency_dict.cend(); ++it){
        if(it->second < min_value){
            min_value = it->second;
        }
    }

    return max_value-min_value;
}

void printInsertionPairs(map<string, vector<string>> post_insertion_pairs){
    for(auto item : post_insertion_pairs){
        cout<<item.first<<" : ";
        printVector(item.second);
    }
}

void populatePairInsertions(map<string, string> rules, map<string, vector<string>> &post_insertion_pairs){
    for(auto item : rules){
        // item= pair<HK, F>
        vector<string> insertions;
        auto insert1 = std::string(1,item.first[0]) + item.second;
        auto insert2 = item.second + std::string(1,item.first[1]);
        insertions.push_back(insert1);
        insertions.push_back(insert2);
        post_insertion_pairs[item.first] = insertions;
    }
}

map<string, int> applySteps(string polymer, map<string, vector<string>> templates, map<string, int> polymers, int steps){
    for(int step=0; step<steps; step++){
        map<string, int> step_polymers(polymers);
        // pol = pair<"HK" : integer>
        for(auto pol : step_polymers){
            if(pol.second > 0){
                vector<pair<string, vector<string>>> temp_templates;
                for(auto t : templates){
                    if(t.first == pol.first){
                        temp_templates.push_back(t);
                    }
                }
                // temp_template = pair<"HK" : < "HF", "FK" >>
                pair<string, vector<string>> temp_template = temp_templates[0];
                polymers[temp_template.second[0]]+=pol.second;
                polymers[temp_template.second[1]]+=pol.second;
                polymers[pol.first] -= pol.second;
            }
        }
    }
}

int main() {
    RequiredData req_data = readFile("input.txt");
    string polymer = req_data.polymer;
    map<string, string> rules = req_data.rules;
    map<string, vector<string>> templates;
    map<string, int> polymers;

    populatePairInsertions(rules, templates);
    // printInsertionPairs(post_insertion_pairs);
    for(auto item : templates){
        polymers[item.first] = 0;
        polymers[item.second[0]] = 0;
        polymers[item.second[1]] = 0;
    }
    applySteps(polymer, templates, polymers, 40);


    // Part 1
    // string final_pattern = extendPolymer(rules, polymer, 10);
    // map<char, ULLI> frequency_dict = string2Frequency(final_pattern);
    // cout << calcMinMaxFrequencyDifference(frequency_dict) << endl; // 3555

    // Part 2
    // string final_pattern2 = extendPolymer(rules, pattern, 40);
    // map<char, ULLI> frequency_dict2 = string2Frequency(final_pattern2);
    // cout<< calcMinMaxFrequencyDifference(frequency_dict2) << endl; // 4439442043739

    return 0;
}