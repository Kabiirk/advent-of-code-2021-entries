#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

string readFile(string filename){
    // Read File
    string file_output;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        string line;
        while ( getline(myfile, line) )
        {
            file_output = line;
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return file_output;
}

string convert2Binary(string expression){
    map<char, string> table = {
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'A', "1010"},
        {'B', "1011"},
        {'C', "1100"},
        {'D', "1101"},
        {'E', "1110"},
        {'F', "1111"}
    };

    string binary_string;
    for(const char c : expression){
        binary_string += table[c];
    }
    
    return binary_string;
}

int convert2Decimal(string expression){
    int i = 0;
    for (const char c : expression){
        i = i * 2 + (c - '0');
    }
  return i;
}

int main() {
    string hex_stream = readFile("input.txt");

    cout<<hex_stream<<endl;

    return 0;
}