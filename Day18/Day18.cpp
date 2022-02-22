#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../utils/utils.h"

using namespace std;

vector<string> readFile(string filename){
    vector<string> file_output;
    string line;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            file_output.push_back(line);
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return file_output;
}

int main() {
    vector<string> blowfish_numbers = readFile("input.txt");

    return 0;
}