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

int maxDimension(vector<vector<int>> vent_lines){
    int max_dim = 0;

    for(auto line : vent_lines){
        for( auto col : line){
            if(col  > max_dim){
                max_dim = col;
            }
        }
    }

    return max_dim;
}

void drawLine(vector<vector<int>> field, vector<int> line){
    int x1 = line[0];
    int y1 = line[1];
    int x2 = line[2];
    int y2 = line[3];

    if(y1 == y2){
        for(int i = min(x1, x2); i<=max(x1, x2); i++){
            field[y1][i]++;
        }
    }
    else if(x1 == x2){
        for(int j = min(y1, y2); j<=max(y1, y2); j++){
            field[j][x1]++;
        }
    }
}

int countIntersections(vector<vector<int>> field){
    int intersects = 0;
    
    for(auto row : field){
        for(auto col : row){
            if(col>=2){
                intersects++;
            }
        }
    }

    return intersects;
}

int main() {
    vector<vector<int>> vent_lines = readFile("input.txt");
    int max_size = maxDimension(vent_lines);

    // Part 1
    vector<vector<int>> field(max_size,
                                std::vector<int>(max_size, 0));

    for(auto line : vent_lines){
        drawLine(field, line);
    }
    cout<<"executed "<<endl;
    int res = countIntersections(field);
    cout<<res;

    return 0;
}
