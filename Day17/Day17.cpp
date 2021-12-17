#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex> // for regex_search()
#include <algorithm> // for max_element()

typedef int ULLI;

using namespace std;

vector<ULLI> readFile(string filename){
    vector<ULLI> file_output;
    ifstream myfile (filename);
    if (myfile.is_open())
    {
        string line;
        while ( getline(myfile, line) )
        {
            // target area: x=135..155, y=-102..-78
            const regex r("target area: x=(-?\\d*)..(-?\\d*), y=(-?\\d*)..(-?\\d*)");  
            smatch result;

            if (regex_search(line, result, r)) {
                for (int i=1; i<result.size(); i++) {
                    // cout << stoi(result[i]) << endl;
                    file_output.push_back(stoi(result[i]));
                }
            }

            // This works but is cringe
            // file_output.push_back((ULLI)stoi(line.substr(15,18)));
            // file_output.push_back((ULLI)stoi(line.substr(20,23)));
            // file_output.push_back(-(ULLI)stoi(line.substr(28,31)));
            // file_output.push_back(-(ULLI)stoi(line.substr(34,36)));
        }
        myfile.close();
    }
    else cout << "Unable to open file";

    return file_output;
}

ULLI max(ULLI a, ULLI b){
    if(a > b){
        return a;
    }
    return b;
}

bool check_velocity_valid(ULLI dx,ULLI dy,vector<ULLI> target){
    ULLI tminx = target[0];
    ULLI tmaxx = target[1];
    ULLI tminy = target[2];
    ULLI tmaxy = target[3];
    
    ULLI pos_x = 0, pos_y = 0;
    while(pos_x <= tmaxx && pos_y >= tminy){
        pos_x = pos_x+dx;
        pos_y = pos_y+dy;
        dx = max(0, dx-1);
        dy = dy-1;
        if( (tminx <= pos_x && pos_x <= tmaxx) && (tminy <= pos_y && pos_y <= tmaxy) ){
            return true;
        }
    }
    return false;
}

ULLI highest_y(ULLI y){
    return (y+1) * y / 2;
}

int main() {
    // Put target Range in vector
    vector<ULLI> target_range = readFile("input.txt");
    vector<ULLI> velocities;

    for(ULLI dx = 0; dx < 1000; dx++){
        for(ULLI dy = -999; dy < 1000; dy++){
            if( check_velocity_valid(dx, dy, target_range) ){
                velocities.push_back(dy);
            }
        }
    }

    // Part 1
    ULLI max = *max_element(velocities.begin(), velocities.end());
    cout<< highest_y(max) << endl; // 5151

    // Part 2
    cout<< velocities.size() << endl; // 968


    return 0;
}
