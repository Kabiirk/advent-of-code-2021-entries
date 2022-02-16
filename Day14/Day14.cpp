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
                req_data.rules.insert( pair<string, string>(to_match, to_append) );
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return req_data;
}

// Utility function
void printInsertionPairs(map<string, vector<string>> post_insertion_pairs){
    for(auto item : post_insertion_pairs){
        cout<<item.first<<" : ";
        printVector(item.second);
    }
}

// utility function (used in both Part 1 & 2)
uint64_t calcMinMaxFrequencyDifference(map<char, uint64_t> frequency_dict){
    uint64_t max_value = 0;
    for(auto it = frequency_dict.begin(); it != frequency_dict.end(); ++it){
        if(it->second > max_value){
            max_value = it->second;
        }
    }

    uint64_t min_value = max_value;
    for(auto it = frequency_dict.begin(); it != frequency_dict.end(); ++it){
        if(it->second < min_value){
            min_value = it->second;
        }
    }

    return max_value-min_value;
}

// Utility function (Only used for Part 1 Brute Force)
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
    first_pattern = temp_pattern;
    }

    return first_pattern;
}

// Utility function (Only used for Part 1 Brute Force)
map<char, ULLI> string2Frequency(string pattern){
    map<char, ULLI> frequency_dict;
    for(char k : pattern)
    {
        frequency_dict[k]++;
    }

    return frequency_dict;
}

// Utility function (Only used for Part 2)
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

// Utility function (Only used for Part 2)
void incrementpolymers(string polymer, map<string, uint64_t> &polymers){
    int n = polymer.size();
    for(int i = 0; i<n-1; i++){
        auto pair_to_increment = std::string(1,polymer[i]) + polymer[i+1];
        polymers[pair_to_increment]++;
    }
}

// Brute Force solution that only works for Part 1 & won't work (Execution time out) for Part 2
int bruteForceMethod(map<string, string> rules, string polymer, int iterations){
    string final_pattern = extendPolymer(rules, polymer, iterations);
    map<char, ULLI> frequency_dict = string2Frequency(final_pattern);
    return calcMinMaxFrequencyDifference(frequency_dict);
}

// Faster solution that works for both Part 1 & Part 2
uint64_t applySteps(string polymer, map<string, vector<string>> &templates, map<string, uint64_t>& polymers, int steps){
    for(int step=0; step<steps; step++){
        map<string, uint64_t> step_polymers(polymers);
        // pol = pair<"HK" : integer>
        vector<pair<string, uint64_t>> temp_pol;
        for(auto temp1 : step_polymers){
            if(temp1.second > 0){
                temp_pol.push_back(temp1);
            }
        }
        for(auto pol : temp_pol){
            vector< pair< string, vector<string> > > temp_templates;
            for(auto t : templates){
                if(t.first == pol.first){
                    temp_templates.push_back(t);
                }
            }
            pair< string, vector<string> > temp_template = temp_templates[0];
            polymers[temp_template.second[0]] += pol.second;
            polymers[temp_template.second[1]] += pol.second;
            polymers[pol.first] -= pol.second;
        }
    }
    map<char, uint64_t> singles;
    for(auto pol3 : polymers){
        string key = pol3.first;
        uint64_t val = pol3.second;

        // bool sub_key1_is_in = singles.find(key[0])!=singles.end();
        // bool sub_key2_is_in = singles.find(key[1])!=singles.end();
        // if(!sub_key1_is_in){
        //     singles[key[0]] = 0;
        // }
        singles[key[0]]+=val;
        // if(!sub_key2_is_in){
        //     singles[key[1]] = 0;
        // }
        singles[key[1]]+=val;
        if(key[0] == key[1]){
            singles[key[0]]+=1;
        }
    }
    singles[polymer[0]]+=1;
    singles[polymer[polymer.size()-1]]+=1;

    return calcMinMaxFrequencyDifference(singles)/2;
}

int main() {
    RequiredData req_data = readFile("input.txt");
    string polymer = req_data.polymer;
    map<string, string> rules = req_data.rules;
    map<string, vector<string>> templates;
    map<string, uint64_t> polymers;

    // Populating relevant data for the faster solution
    populatePairInsertions(rules, templates);
    for(auto item : templates){
        polymers[item.first] = 0;
        polymers[item.second[0]] = 0;
        polymers[item.second[1]] = 0;
    }
    incrementpolymers(polymer, polymers);

    // Part 1
    // cout<<bruteForceMethod(rules, polymer, 10)<<endl;
    cout<<applySteps(polymer, templates, polymers, 10)<<endl;// 3555

    // Part 2
    // Brute-force approach was slow and timed out
    // 30 because 10 expansions on the polymer have already been done with the same rules
    cout<<applySteps(polymer, templates, polymers, 30)<<endl;// 4439442043739

    return 0;
}