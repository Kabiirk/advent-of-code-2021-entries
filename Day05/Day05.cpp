#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

vector<vector<int>> readFile(string filename){
    /*
    Desired shape for vent_lines :
    <
        <x1, y1, x2, y2>;
    >
    */
    vector<vector<int>> vent_lines;
    string line;
    ifstream myfile (filename);

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            const regex r("(-?\\d*),(-?\\d*) -> (-?\\d*),(-?\\d*)");
            smatch result;

            if (regex_search(line, result, r)) {
                // result = ["542,676 -> 542,819", "542", "676", "542", "819"]
                //cout<<"("<<result[1]<<", "<<result[2]<<")"<<"("<<result[3]<<", "<<result[4]<<")"<<endl;
                vector<int> current_entry = { stoi(result[1]), stoi(result[2]), stoi(result[3]), stoi(result[4]) };
                vent_lines.push_back(current_entry);
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return vent_lines;
}

int main() {
    vector<vector<int>> vent_lines = readFile("input.txt");
    int max_dimension;
    return 0;
}
