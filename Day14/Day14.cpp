#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

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

    for(auto it = rules.cbegin(); it != rules.cend(); ++it)
    {
        cout << it->first << " " << it->second << "\n";
    }

    return 0;
}