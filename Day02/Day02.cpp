#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <vector>

using namespace std;

vector<pair<string, int>> readFile(string filename){
    vector<pair<string, int>> coordinates;
    string line;
    ifstream myfile (filename);

    if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            // forward 6
            const regex r("(\\w*) (-?\\d*)");
            smatch result;

            if (regex_search(line, result, r)) {
                // result = ["forward 6", "forward", "6"]
                if(result[1] == "up"){
                    coordinates.push_back(pair<string, int>(result[1], -stoi(result[2])));
                }
                else{
                    coordinates.push_back(pair<string, int>(result[1], stoi(result[2])));
                }
                
            }
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return coordinates;
}

int main() {
    vector<pair<string, int>> coordinates = readFile("input.txt");
    // coordinates = < ("forward", 6), ("up", -1), ("down", 9)... >
    map<string, int> final_coordinates = {
                                    {"horizontal", 0},
                                    {"depth", 0},
                                    {"aim", 0}
                                    };

    // Part 1
    for (auto it : coordinates) {
        if(it.first == "forward"){
            final_coordinates["horizontal"] += it.second;
        }
        else{
            final_coordinates["depth"] += it.second;
        }
    }
    // {'horizontal': 1965, 'depth': 1182}
    cout << final_coordinates["depth"] * final_coordinates["horizontal"] << endl; // 2322630

    // Reset "horizontal" & "depth" values
    // before executing part 2 since we are using the previous Map
    final_coordinates["horizontal"] = 0;
    final_coordinates["depth"] = 0;

    // Part 2
    for (auto it : coordinates) {
        if(it.first == "forward"){
            final_coordinates["horizontal"] += it.second;
            final_coordinates["depth"] += final_coordinates["aim"] * it.second;
        }
        else{
            final_coordinates["aim"] += it.second;
        }
    }
    // {'horizontal': 1965, 'depth': 1071386, 'aim': 1182}
    cout << final_coordinates["depth"] * final_coordinates["horizontal"] << endl; // 2105273490

    return 0;
}
