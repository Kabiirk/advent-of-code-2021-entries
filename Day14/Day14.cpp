#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

typedef unsigned long long int ULLI;

using namespace std;

void printMap( map<string, string> dictionary ){
    for(auto it = dictionary.cbegin(); it != dictionary.cend(); ++it){
        cout << it->first << " " << it->second << "\n";
    }
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

int main() {
    string line, pattern;
    string to_append;
    string to_match;
    map<string, string> rules;

    // Read File
    ifstream myfile ("input.txt");
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            if(line.length() > 10){
                pattern = line;
            }
            else if(line.length() == 0){
                // Blank line
                continue;
            }
            else{
                to_append = line.back();
                to_match = line.substr(0, 2);
                // cout << to_match << " ==> " << to_append << endl;
                rules.insert( pair<string, string>(to_match, to_append) );
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    // Part 1
    string final_pattern = extendPolymer(rules, pattern, 10);
    map<char, ULLI> frequency_dict = string2Frequency(final_pattern);
    cout << calcMinMaxFrequencyDifference(frequency_dict) << endl; // 3555

    // Part 2
    string final_pattern2 = extendPolymer(rules, pattern, 40);
    cout<<final_pattern2<<endl;
    map<char, ULLI> frequency_dict2 = string2Frequency(final_pattern2);
    cout<< calcMinMaxFrequencyDifference(frequency_dict2) << endl; // 4439442043739

    return 0;
}